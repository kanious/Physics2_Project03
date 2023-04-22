#ifndef _IVEHICLE_H_
#define _IVEHICLE_H_

#include "Base.h"
#include "glm\vec3.hpp"
#include "glm\mat4x4.hpp"

NAMESPACE_BEGIN(Engine)

class ENGINE_API iVehicle : public CBase
{
protected:
	explicit iVehicle() {}
	virtual ~iVehicle() {}
	virtual void Destroy() = 0;

public:
	virtual void AddWheel(const glm::vec3& point, const glm::vec3& dir, const glm::vec3& axle, _float suspensionLength, _float radius, _bool isFrointWheel) = 0;
	virtual void ApplyEngineForce(_float force, _int wheelIdx) = 0;
	virtual void SetSteering(_float value, _int wheelIdx) = 0;
	virtual void SetBrake(_float value, _int wheelIdx) = 0;
	virtual void GetChassisTransform(glm::mat4x4& matrix) const = 0;
	virtual void GetWheelTransform(glm::mat4x4& matrix, _int wheelIdx) const = 0;
};

NAMESPACE_END

#endif //_IVEHICLE_H_