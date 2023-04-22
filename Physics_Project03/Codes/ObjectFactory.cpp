#include "ObjectFactory.h"
#include "GameObject.h"
#include "Layer.h"

#include "BGObject.h"
#include "DefaultCamera.h"
#include "VehicleObject.h"
#include "Character.h"


USING(Engine)
USING(glm)
USING(std)

// Create background object
BGObject* ObjectFactory::CreateBGObject(_uint sTag, _uint lTag, _uint oTag, CLayer* pLayer, string meshID,
    vec3 vPos, vec3 vRot, vec3 vScale)
{
    CGameObject* pGameObject = BGObject::Create(sTag, lTag, oTag, pLayer, meshID, vPos, vRot, vScale);

    if (nullptr != pGameObject)
        pLayer->AddGameObject(pGameObject);

    return dynamic_cast<BGObject*>(pGameObject);
}

VehicleObject* ObjectFactory::CreateVehicleObject(_uint sTag, _uint lTag, _uint oTag, CLayer* pLayer, string meshID,
    vec3 vPos, vec3 vRot, vec3 vScale, _bool isWheel, _int index)
{
    CGameObject* pGameObject = VehicleObject::Create(sTag, lTag, oTag, pLayer, meshID, vPos, vRot, vScale, isWheel, index);

    if (nullptr != pGameObject)
        pLayer->AddGameObject(pGameObject);

    return dynamic_cast<VehicleObject*>(pGameObject);
}

Character* ObjectFactory::CreateCharacter(_uint sTag, _uint lTag, _uint oTag, CLayer* pLayer, string meshID, vec3 vPos, vec3 vRot, vec3 vScale)
{
    CGameObject* pGameObject = Character::Create(sTag, lTag, oTag, pLayer, meshID, vPos, vRot, vScale);

    if (nullptr != pGameObject)
        pLayer->AddGameObject(pGameObject);

    return dynamic_cast<Character*>(pGameObject);
}

// Create camera
DefaultCamera* ObjectFactory::CreateCamera(_uint sTag, _uint lTag, _uint oTag, CLayer* pLayer,
    vec3 vPos, vec3 vRot, vec3 vScale, _float fov, _float fNear, _float fFar)
{
    CGameObject* pGameObject = DefaultCamera::Create(sTag, lTag, oTag, pLayer, vPos, vRot, vScale, fov, fNear, fFar);

    if (nullptr != pGameObject)
        pLayer->AddGameObject(pGameObject);

    return dynamic_cast<DefaultCamera*>(pGameObject);
}
 