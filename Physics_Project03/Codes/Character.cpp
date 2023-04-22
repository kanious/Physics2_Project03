#include "Character.h"
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
#include "iCharacterController.h"
#include "Function.h"


USING(Engine)
USING(glm)
USING(std)

Character::Character()
	: m_pMesh(nullptr), m_fSpeed(1.f), m_vWalkDir(vec3(0.f))
{
	m_bDebug = false;
	m_pInputDevice = CInputDevice::GetInstance(); m_pInputDevice->AddRefCnt();
}

Character::~Character()
{
}

glm::vec3 Character::GetPosition()
{
	if (nullptr == m_pController)
		return vec3(0.f);

	mat4x4 matWorld(1.f);
	m_pController->GetWorldTransform(matWorld);
	return matWorld[3];
}

void Character::SetController(Engine::iCharacterController* pController)
{
	if (nullptr == pController)
		return;
	
	m_pController = pController;
	m_pController->Warp(vec3(8.f, 10.f, 0.f));
}

void Character::Reset()
{
	if (nullptr == m_pController)
		return;

	m_pController->Warp(vec3(8.f, 10.f, 0.f));
}

void Character::KeyCheck(const _float& dt)
{
	if (nullptr == m_pInputDevice || nullptr == m_pTransform || nullptr == m_pController)
		return;

	if (m_pInputDevice->IsKeyDown(GLFW_KEY_W))
		m_vWalkDir.z += m_fSpeed * dt;
	else if (m_pInputDevice->IsKeyDown(GLFW_KEY_S))
		m_vWalkDir.z -= m_fSpeed * dt;
	else
		m_vWalkDir.z = 0.f;

	if (m_pInputDevice->IsKeyDown(GLFW_KEY_A))
		m_vWalkDir.x += m_fSpeed * dt;
	else if (m_pInputDevice->IsKeyDown(GLFW_KEY_D))
		m_vWalkDir.x -= m_fSpeed * dt;
	else
		m_vWalkDir.x = 0.f;

	m_pController->SetWalkDirection(m_vWalkDir);

	if (m_pInputDevice->IsKeyDown(GLFW_KEY_SPACE))
		m_pController->Jump(vec3(0.f));
}

// Basic Update Function
void Character::Update(const _float& dt)
{
	if (m_bEnable)
	{
		if (m_bSelected)
			KeyCheck(dt);

		if (nullptr != m_pController)
		{
			mat4x4 matWorld(1.f);
			m_pController->GetWorldTransform(matWorld);
			matWorld = scale(matWorld, vec3(0.5f, 2.f, 0.5f));
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
void Character::Render()
{
	CGameObject::Render();
}

// Call instead of destructor to manage class internal data
void Character::Destroy()
{
	SafeDestroy(m_pInputDevice);

	CGameObject::Destroy();
}

// Initialize
RESULT Character::Ready(_uint sTag, _uint lTag, _uint oTag, CLayer* pLayer, string meshID, vec3 vPos, vec3 vRot, vec3 vScale)
{
	SetupGameObject(sTag, lTag, oTag);
	m_pLayer = pLayer;
	m_meshName = meshID;

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
Character* Character::Create(_uint sTag, _uint lTag, _uint oTag, CLayer* pLayer, string meshID, vec3 vPos, vec3 vRot, vec3 vScale)
{
	Character* pInstance = new Character();
	if (PK_NOERROR != pInstance->Ready(sTag, lTag, oTag, pLayer, meshID, vPos, vRot, vScale))
	{
		pInstance->Destroy();
		pInstance = nullptr;
	}

	return pInstance;
}
