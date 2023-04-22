#ifndef _ICHARACTERCONTROLLER_H_
#define _ICHARACTERCONTROLLER_H_

#include "Base.h"
#include "glm\vec3.hpp"
#include "glm\mat4x4.hpp"

NAMESPACE_BEGIN(Engine)

class ENGINE_API iCharacterController : public CBase
{
protected:
	explicit iCharacterController() {}
	virtual ~iCharacterController() {}
	virtual void Destroy() = 0;

public:
	virtual void SetWalkDirection(const glm::vec3 dir) = 0;
	virtual void SetVelocityForTimeInterval(const glm::vec3& velocity, _float timeInterval) = 0;
	virtual void Warp(const glm::vec3& position) = 0;
	virtual _bool CanJump() const = 0;
	virtual void Jump(const glm::vec3& dir) = 0;
	virtual _bool OnGround() const = 0;
	virtual void GetWorldTransform(glm::mat4x4& matrix) const = 0;
};

NAMESPACE_END

#endif //_ICHARACTERCONTROLLER_H_