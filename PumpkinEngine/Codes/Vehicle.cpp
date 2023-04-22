#include "pch.h"
#include "../Headers/Vehicle.h"
#include "../Headers/OpenGLDefines.h"
#include "../Headers/Conversion.h"
#include "../Headers/iRigidBody.h"

USING(Engine)
USING(std)
USING(glm)

CVehicle::CVehicle()
	: m_Vehicle(nullptr)
{
}

CVehicle::~CVehicle()
{
}

void CVehicle::Destroy()
{
}

void CVehicle::AddWheel(const glm::vec3& point, const glm::vec3& dir, const glm::vec3& axle, _float suspensionLength, _float radius, _bool isFrontWheel)
{
	btVector3 btConnectionPoint;
	btVector3 btWheelDirection;
	btVector3 btWheelAxle;

	CastBulletVector3(point, &btConnectionPoint);
	CastBulletVector3(dir, &btWheelDirection);
	CastBulletVector3(axle, &btWheelAxle);

	btRaycastVehicle::btVehicleTuning tuning;
	if (nullptr != m_Vehicle)
		m_Vehicle->addWheel(btConnectionPoint, btWheelDirection, btWheelAxle, suspensionLength, radius, tuning, isFrontWheel);
}

void CVehicle::ApplyEngineForce(_float force, _int wheelIdx)
{
	if (nullptr != m_Vehicle)
		m_Vehicle->applyEngineForce(force, wheelIdx);
}

void CVehicle::SetSteering(_float value, _int wheelIdx)
{
	if (nullptr != m_Vehicle)
		m_Vehicle->setSteeringValue(value, wheelIdx);
}

void CVehicle::SetBrake(_float value, _int wheelIdx)
{
	if (nullptr != m_Vehicle)
		m_Vehicle->setBrake(value, wheelIdx);
}

void CVehicle::GetChassisTransform(glm::mat4x4& matrix) const
{
	if (nullptr == m_Vehicle)
		return;

	const btTransform& transform = m_Vehicle->getChassisWorldTransform();
	transform.getOpenGLMatrix(&matrix[0][0]);
}

void CVehicle::GetWheelTransform(glm::mat4x4& matrix, _int wheelIdx) const
{
	if (nullptr == m_Vehicle)
		return;

	const btTransform& transform = m_Vehicle->getWheelTransformWS(wheelIdx);
	transform.getOpenGLMatrix(&matrix[0][0]);
}

RESULT CVehicle::Ready(btRigidBody* chassis, btVehicleRaycaster* vehicleRaycaster)
{
	btRaycastVehicle::btVehicleTuning tuning;
	m_Vehicle = new btRaycastVehicle(tuning, chassis, vehicleRaycaster);

	chassis->setActivationState(DISABLE_DEACTIVATION);

	return PK_NOERROR;
}

CVehicle* CVehicle::Create(btRigidBody* chassis, btVehicleRaycaster* vehicleRaycaster)
{
	CVehicle* pInstance = new CVehicle();
	if (PK_NOERROR != pInstance->Ready(chassis, vehicleRaycaster))
	{
		pInstance->Destroy();
		pInstance = nullptr;
	}

	return pInstance;
}
