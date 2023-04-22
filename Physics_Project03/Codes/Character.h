#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "GameObject.h"
#include "EngineStruct.h"

namespace Engine
{
	class CMesh;
	class iCharacterController;
	class CInputDevice;
}

// Static Object class
class Character : public Engine::CGameObject
{
private:
	Engine::CMesh*					m_pMesh;
	Engine::CInputDevice*			m_pInputDevice;
	Engine::iCharacterController*	m_pController;

	_float							m_fSpeed;
	glm::vec3						m_vWalkDir;


private:
	explicit Character();
	virtual ~Character();

public:
	Engine::iCharacterController* GetController()					{ return m_pController; }
	virtual glm::vec3 GetPosition();
	void SetController(Engine::iCharacterController* pController);
	void Reset();
private:
	void KeyCheck(const _float& dt);

public:
	virtual void Update(const _float& dt);
	virtual void Render();
private:
	virtual void Destroy();
	RESULT Ready(_uint sTag, _uint lTag, _uint oTag, Engine::CLayer* pLayer, std::string meshID,
		glm::vec3 vPos, glm::vec3 vRot, glm::vec3 vScale);
public:
	static Character* Create(_uint sTag, _uint lTag, _uint oTag, Engine::CLayer* pLayer, std::string meshID,
		glm::vec3 vPos, glm::vec3 vRot, glm::vec3 vScale);
};

#endif //_CHARACTER_H_