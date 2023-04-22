#ifndef _CHARACTERCONTROLLER_H_
#define _CHARACTERCONTROLLER_H_

#include "iCharacterController.h"

#include <BulletDynamics/Character/btKinematicCharacterController.h>

NAMESPACE_BEGIN(Engine)

class CRigidBodyDesc;
class iShape;
class ENGINE_API CCharacterController : public iCharacterController
{
private:
	btPairCachingGhostObject*			m_GhostObject;
	btKinematicCharacterController*		m_Controller;

private:
	explicit CCharacterController();
	virtual ~CCharacterController();
	virtual void Destroy();

public:
	virtual void SetWalkDirection(const glm::vec3 dir);
	virtual void SetVelocityForTimeInterval(const glm::vec3& velocity, _float timeInterval);
	virtual void Warp(const glm::vec3& position);
	virtual _bool CanJump() const;
	virtual void Jump(const glm::vec3& dir);
	virtual _bool OnGround() const;
	virtual void GetWorldTransform(glm::mat4x4& matrix) const;

public:
	btPairCachingGhostObject* GetGhostObject() { return m_GhostObject; }
	btKinematicCharacterController* GetController() { return m_Controller; }

private:
	RESULT Ready(btPairCachingGhostObject* ghostObject, btConvexShape* shape,
		btScalar height, const btVector3& up);
public:
	static CCharacterController* Create(btPairCachingGhostObject* ghostObject, btConvexShape* shape,
		btScalar height, const btVector3& up);
};

NAMESPACE_END

#endif //_CHARACTERCONTROLLER_H_