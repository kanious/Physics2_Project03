#include "pch.h"
#include "../Headers/PhysicsFactory.h"
#include "../Headers/PhysicsWorld.h"
#include "../Headers/Conversion.h"
#include "../Headers/RigidBody.h"
#include "../Headers/RigidBodyDesc.h"
#include "../Headers/Vehicle.h"
#include "../Headers/CharacterController.h"

#include <BulletCollision/CollisionDispatch/btGhostObject.h>

USING(Engine)
USING(std)

CPhysicsFactory::CPhysicsFactory()
	: iPhysicsFactory()
{
}

CPhysicsFactory::~CPhysicsFactory()
{
}

void CPhysicsFactory::Destroy()
{
}

iPhysicsWorld* CPhysicsFactory::CreateWorld(function<void(void)> callback)
{
	CPhysicsWorld* world = CPhysicsWorld::Create(callback);

	m_VehicleRaycaster = world->GetVehicleRaycaster();
	m_DynamicWorld = world->GetDynamicWorld();

	return world;
}

iRigidBody* CPhysicsFactory::CreateRigidBody(const CRigidBodyDesc& desc, iShape* shape)
{
	return CRigidBody::Create(desc, shape);
}

iVehicle* CPhysicsFactory::CreateVehicle(iRigidBody* chassis)
{
	btRigidBody* btChassis = CastBulletRigidBody(chassis);
	return CVehicle::Create(btChassis, m_VehicleRaycaster);
}

iCharacterController* CPhysicsFactory::CreateCharacterController(iShape* shape, _float height, const glm::vec3& up)
{
	btPairCachingGhostObject* ghost = new btPairCachingGhostObject();
	btConvexShape* btShape;
	btScalar btHeight;
	btVector3 btUp;

	btShape = CastBulletCapsuleShape(shape);
	CastBulletScalar(height, &btHeight);
	CastBulletVector3(up, &btUp);

	ghost->setCollisionShape(btShape);
	ghost->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	ghost->setWorldTransform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(8, 10, 0)));

	iCharacterController* iController = CCharacterController::Create(ghost, btShape, btHeight, btUp);
	return iController;
}

RESULT CPhysicsFactory::Ready()
{
	return PK_NOERROR;
}

CPhysicsFactory* CPhysicsFactory::Create()
{
	CPhysicsFactory* pInstance = new CPhysicsFactory();
	if (PK_NOERROR != pInstance->Ready())
	{
		pInstance->Destroy();
		pInstance = nullptr;
	}

	return pInstance;
}
