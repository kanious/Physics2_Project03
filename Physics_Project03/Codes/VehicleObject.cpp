#include "VehicleObject.h"
#include "ComponentMaster.h"
#include "Layer.h"

#include "Component.h"
#include "Transform.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoundingBox.h"
#include "OpenGLDefines.h"
#include "InputDevice.h"
#include "SoundMaster.h"
#include "Shader.h"
#include "Light.h"
#include "iRigidBody.h"
#include "iVehicle.h"
#include "Function.h"


USING(Engine)
USING(glm)
USING(std)

VehicleObject::VehicleObject()
	: m_pMesh(nullptr), m_bIsWheel(false), m_iIndex(0), m_fSpeed(15.f), m_fRotSpeed(1.f)
	, m_fEngineForce(0.f), m_fSteering(0.f), m_fBrakeForce(0.f), m_fSteeringLimit(radians(45.f))
{
	m_bDebug = false;
	m_pInputDevice = CInputDevice::GetInstance(); m_pInputDevice->AddRefCnt();
}

VehicleObject::~VehicleObject()
{
}

glm::vec3 VehicleObject::GetPosition()
{
	if (nullptr == m_pVehicle)
		return vec3(0.f);

	mat4x4 matWorld(1.f);
	m_pVehicle->GetChassisTransform(matWorld);
	return matWorld[3];
}

void VehicleObject::SetRigidBody(iRigidBody* pBody)
{
	m_pRigidBody = pBody;
	if (nullptr != m_pRigidBody)
		m_pRigidBody->SetTransform(m_pTransform);
}

void VehicleObject::SetVehicle(iVehicle* pVehicle)
{
	m_pVehicle = pVehicle;
}

void VehicleObject::SetEngineForce(_float value)
{
	for (int i = 0; i < 4; ++i)
		m_pVehicle->ApplyEngineForce(value, i);
}

void VehicleObject::SetSteering(_float value)
{
	for (int i = 0; i < 2; ++i)
		m_pVehicle->SetSteering(value, i);
}

void VehicleObject::SetBrake(_float value)
{
	for (int i = 0; i < 4; ++i)
		m_pVehicle->SetBrake(value, i);
}

void VehicleObject::KeyCheck(const _float& dt)
{
	if (nullptr == m_pInputDevice || nullptr == m_pTransform || nullptr == m_pVehicle)
		return;
	
	//--------------------------------------- Moving
	if (m_pInputDevice->IsKeyDown(GLFW_KEY_W))
		m_fEngineForce += m_fSpeed * dt;
	else if (m_pInputDevice->IsKeyDown(GLFW_KEY_S))
		m_fEngineForce -= m_fSpeed * dt;
	else
		m_fEngineForce = 0.f;

	SetEngineForce(m_fEngineForce);

	//--------------------------------------- Rotating
	if (m_pInputDevice->IsKeyDown(GLFW_KEY_A))
		m_fSteering += m_fRotSpeed * dt;
	else if (m_pInputDevice->IsKeyDown(GLFW_KEY_D))
		m_fSteering -= m_fRotSpeed * dt;
	else
		m_fSteering = 0.f;

	if (m_fSteering > m_fSteeringLimit)
		m_fSteering = m_fSteeringLimit;
	else if (m_fSteering < -m_fSteeringLimit)
		m_fSteering = -m_fSteeringLimit;

	SetSteering(m_fSteering);

	//--------------------------------------- Braking
	if (m_pInputDevice->IsKeyDown(GLFW_KEY_SPACE))
		m_fBrakeForce += m_fSpeed * dt;
	else
		m_fBrakeForce = 0.f;

	SetBrake(m_fBrakeForce);
}

// Basic Update Function
void VehicleObject::Update(const _float& dt)
{
	if (m_bEnable)
	{
		if (m_bSelected)
			KeyCheck(dt);

		if (nullptr != m_pVehicle)
		{
			mat4x4 matWorld(1.f);
			if (!m_bIsWheel)
				m_pVehicle->GetChassisTransform(matWorld);
			else
				m_pVehicle->GetWheelTransform(matWorld, m_iIndex);
			matWorld = scale(matWorld, vec3(0.01f));
			m_pTransform->SetWorldMatrix(matWorld);
		}

		if (nullptr != m_pMesh)
			m_pMesh->SetSelcted(m_bSelected);

		CGameObject::Update(dt);

		if (nullptr != m_pRenderer)
			m_pRenderer->AddRenderObj(this);
	}
}

// Basic Render Function
void VehicleObject::Render()
{
	CGameObject::Render();
}

// Call instead of destructor to manage class internal data
void VehicleObject::Destroy()
{
	SafeDestroy(m_pInputDevice);

	CGameObject::Destroy();
}

// Initialize
RESULT VehicleObject::Ready(_uint sTag, _uint lTag, _uint oTag, CLayer* pLayer, string meshID, vec3 vPos, vec3 vRot, vec3 vScale, _bool isWheel, _int index)
{
	SetupGameObject(sTag, lTag, oTag);
	m_pLayer = pLayer;
	m_meshName = meshID;
	m_bIsWheel = isWheel;
	m_iIndex = index;

	//Clone.Mesh
 	m_pMesh = CloneComponent<CMesh*>(meshID);
	if (nullptr != m_pMesh)
	{
		AttachComponent("Mesh", m_pMesh);
		m_pMesh->SetTransform(m_pTransform);
		m_pBoundingBox = m_pMesh->GetBoundingBox();
		if (nullptr != m_pBoundingBox)
			m_pBoundingBox->SetTransform(m_pTransform);
		m_pMesh->SetWireFrame(false);
		m_pMesh->SetDebugBox(false);
	}

	if (nullptr != m_pTransform)
	{
		m_pTransform->SetPosRotScale(vPos, vRot, vScale);

		quat qRot = quat(vec3(radians(vRot.x), radians(vRot.y), radians(vRot.z)));
		m_pTransform->SetQuaternion(qRot);
		m_pTransform->Update(0);

		m_pTransform->SetFixedWorldMatrixUsing(true);
	}

	return PK_NOERROR;
}

// Create an instance
VehicleObject* VehicleObject::Create(_uint sTag, _uint lTag, _uint oTag, CLayer* pLayer, string meshID, vec3 vPos, vec3 vRot, vec3 vScale, _bool isWheel, _int index)
{
	VehicleObject* pInstance = new VehicleObject();
	if (PK_NOERROR != pInstance->Ready(sTag, lTag, oTag, pLayer, meshID, vPos, vRot, vScale, isWheel, index))
	{
		pInstance->Destroy();
		pInstance = nullptr;
	}

	return pInstance;
}
