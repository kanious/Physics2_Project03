#ifndef _CAPSULESHAPE_H_
#define _CAPSULESHAPE_H_

#include "iShape.h"
#include "glm\vec3.hpp"

NAMESPACE_BEGIN(Engine)

class ENGINE_API CCapsuleShape : public iShape
{
private:
	_float		m_fRadius;
	_float		m_fHeight;

private:
	explicit CCapsuleShape();
	virtual ~CCapsuleShape();
	virtual void Destroy();

public:
	_float GetRadius()		{ return m_fRadius; }
	_float GetHeight()		{ return m_fHeight; }

private:
	RESULT Ready(eShapeType type, _float radius, _float height);
public:
	static CCapsuleShape* Create(eShapeType type, _float radius, _float height);
};

NAMESPACE_END

#endif //_CAPSULESHAPE_H_
