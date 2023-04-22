#ifndef _VEHICLEOBJECT_H_
#define _VEHICLEOBJECT_H_

#include "GameObject.h"
#include "EngineStruct.h"

namespace Engine
{
	class CMesh;
	class iRigidBody;
	class iVehicle;
	class CInputDevice;
}

// Static Object class
class VehicleObject : public Engine::CGameObject
{
private:
	Engine::CMesh*					m_pMesh;
	Engine::CInputDevice*			m_pInputDevice;
	Engine::iRigidBody*				m_pRigidBody;
	Engine::iVehicle*				m_pVehicle;

	_bool							m_bIsWheel;
	_int							m_iIndex;

	_float							m_fSpeed;
	_float							m_fRotSpeed;

	_float							m_fEngineForce;
	_float							m_fSteering;
	_float							m_fBrakeForce;
	_float							m_fSteeringLimit;


private:
	explicit VehicleObject();
	virtual ~VehicleObject();

public:
	Engine::iRigidBody* GetRigidBody() { return m_pRigidBody; }
	Engine::iVehicle* GetVehicle()	{ return m_pVehicle; }
	virtual glm::vec3 GetPosition();
	void SetRigidBody(Engine::iRigidBody* pBody);
	void SetVehicle(Engine::iVehicle* pVehicle);
	void SetEngineForce(_float value);
	void SetSteering(_float value);
	void SetBrake(_float value);
private:
	void KeyCheck(const _float& dt);

public:
	virtual void Update(const _float& dt);
	virtual void Render();
private:
	virtual void Destroy();
	RESULT Ready(_uint sTag, _uint lTag, _uint oTag, Engine::CLayer* pLayer, std::string meshID,
		glm::vec3 vPos, glm::vec3 vRot, glm::vec3 vScale, _bool isWheel, _int index = 0);
public:
	static VehicleObject* Create(_uint sTag, _uint lTag, _uint oTag, Engine::CLayer* pLayer, std::string meshID,
		glm::vec3 vPos, glm::vec3 vRot, glm::vec3 vScale, _bool isWheel, _int index = 0);
};

#endif //_VEHICLEOBJECT_H_