#include "pch.h"
#include "../Headers/CapsuleShape.h"

USING(Engine)
USING(std)
USING(glm)

CCapsuleShape::CCapsuleShape()
    : m_fRadius(0.f), m_fHeight(0.f)
{
}

CCapsuleShape::~CCapsuleShape()
{
}

void CCapsuleShape::Destroy()
{
}

RESULT CCapsuleShape::Ready(eShapeType type, _float radius, _float height)
{
    m_shapeType = type;
    m_fRadius = radius;
    m_fHeight = height;

    return PK_NOERROR;
}

CCapsuleShape* CCapsuleShape::Create(eShapeType type, _float radius, _float height)
{
    CCapsuleShape* pInstance = new CCapsuleShape();
    if (PK_NOERROR != pInstance->Ready(type, radius, height))
    {
        pInstance->Destroy();
        pInstance = nullptr;
    }

    return pInstance;
}
