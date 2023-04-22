#ifndef _VEHICLE_H_
#define _VEHICLE_H_

#include "iVehicle.h"

#include <BulletDynamics/Vehicle/btRaycastVehicle.h>
#include <BulletDynamics/Vehicle/btWheelInfo.h>

NAMESPACE_BEGIN(Engine)

class CRigidBodyDesc;
class iShape;
class ENGINE_API CVehicle : public iVehicle
{
private:
	btRaycastVehicle*	m_Vehicle;

private:
	explicit CVehicle();
	virtual ~CVehicle();
	virtual void Destroy();
	CVehicle& operator=(const CVehicle& other) { return *this; }

public:
	virtual void AddWheel(const glm::vec3& point, const glm::vec3& dir, const glm::vec3& axle, _float suspensionLength, _float radius, _bool isFrontWheel);
	virtual void ApplyEngineForce(_float force, _int wheelIdx);
	virtual void SetSteering(_float value, _int wheelIdx);
	virtual void SetBrake(_float value, _int wheelIdx);
	virtual void GetChassisTransform(glm::mat4x4& matrix) const;
	virtual void GetWheelTransform(glm::mat4x4& matrix, _int wheelIdx) const;

public:
	btRaycastVehicle* GetVehicle()	{ return m_Vehicle; }

private:
	RESULT Ready(btRigidBody* chassis, btVehicleRaycaster* vehicleRaycaster);
public:
	static CVehicle* Create(btRigidBody* chassis, btVehicleRaycaster* vehicleRaycaster);
};

NAMESPACE_END

#endif //_VEHICLE_H_