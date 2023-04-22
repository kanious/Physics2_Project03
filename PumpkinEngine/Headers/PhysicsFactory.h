#ifndef _PHYSICSFACTORY_H_
#define _PHYSICSFACTORY_H_

#include "iPhysicsFactory.h"
#include <BulletDynamics/Vehicle/btVehicleRaycaster.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

NAMESPACE_BEGIN(Engine)

class ENGINE_API CPhysicsFactory : public iPhysicsFactory
{
private:
	btVehicleRaycaster*			m_VehicleRaycaster;
	btDiscreteDynamicsWorld*	m_DynamicWorld;

private:
	explicit CPhysicsFactory();
	virtual ~CPhysicsFactory();
	virtual void Destroy();

public:
	virtual iPhysicsWorld* CreateWorld(std::function<void(void)> callback);
	virtual iRigidBody* CreateRigidBody(const CRigidBodyDesc& desc, iShape* shape);
	virtual iVehicle* CreateVehicle(iRigidBody* chassis);
	virtual iCharacterController* CreateCharacterController(iShape* shape, _float height, const glm::vec3& up);

private:
	RESULT Ready();
public:
	static CPhysicsFactory* Create();
};

NAMESPACE_END

#endif //_PHYSICSFACTORY_H_