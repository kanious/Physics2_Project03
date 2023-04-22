#include "pch.h"
#include "../Headers/CharacterController.h"
#include "../Headers/OpenGLDefines.h"
#include "../Headers/Conversion.h"
#include "../Headers/iRigidBody.h"

#include <BulletCollision/CollisionDispatch/btGhostObject.h>

USING(Engine)
USING(std)
USING(glm)

CCharacterController::CCharacterController()
	: m_GhostObject(nullptr), m_Controller(nullptr)
{
}

CCharacterController::~CCharacterController()
{
}

void CCharacterController::Destroy()
{
}

void CCharacterController::SetWalkDirection(const glm::vec3 dir)
{
	btVector3 btDir;
	CastBulletVector3(dir, &btDir);
	//m_Controller->setWalkDirection(btDir);
	m_Controller->setLinearVelocity(btDir);
}

void CCharacterController::SetVelocityForTimeInterval(const glm::vec3& velocity, _float timeInterval)
{
	btVector3 btVelocity;
	CastBulletVector3(velocity, &btVelocity);
	m_Controller->setVelocityForTimeInterval(btVelocity, btScalar(timeInterval));
}

void CCharacterController::Warp(const glm::vec3& position)
{
	btVector3 btPos;
	CastBulletVector3(position, &btPos);
	m_Controller->warp(btPos);
}

_bool CCharacterController::CanJump() const
{
	return m_Controller->canJump();
}

void CCharacterController::Jump(const glm::vec3& dir)
{
	btVector3 btDir;
	CastBulletVector3(dir, &btDir);
	m_Controller->jump(btDir);
}

_bool CCharacterController::OnGround() const
{
	return m_Controller->onGround();
}

void CCharacterController::GetWorldTransform(glm::mat4x4& matrix) const
{
	if (nullptr == m_GhostObject)
		return;

	const btTransform& transform = m_GhostObject->getWorldTransform();
	transform.getOpenGLMatrix(&matrix[0][0]);
}

RESULT CCharacterController::Ready(btPairCachingGhostObject* ghostObject,
	btConvexShape* shape, btScalar height, const btVector3& up)
{
	m_GhostObject = ghostObject;
	m_GhostObject->setActivationState(DISABLE_DEACTIVATION);

	m_Controller = new btKinematicCharacterController(m_GhostObject, shape, height, up);
	m_Controller->setUseGhostSweepTest(false);
	m_Controller->setMaxPenetrationDepth(0);

	return PK_NOERROR;
}

CCharacterController* CCharacterController::Create(btPairCachingGhostObject* ghostObject,
	btConvexShape* shape, btScalar height, const btVector3& up)
{
	CCharacterController* pInstance = new CCharacterController();
	if (PK_NOERROR != pInstance->Ready(ghostObject, shape, height, up))
	{
		pInstance->Destroy();
		pInstance = nullptr;
	}

	return pInstance;
}
