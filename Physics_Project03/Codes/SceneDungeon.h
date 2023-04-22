#ifndef _SCENEDUNGEON_H_
#define _SCENEDUNGEON_H_

#include "Scene.h"
#include "glm\vec3.hpp"
#include "iShape.h"
#include "CollisionHandler.h"

namespace Engine
{
	class CInputDevice;
	class CLayer;
	class CSkyBox;
	class iPhysicsFactory;
	class iPhysicsWorld;
	class CRigidBody;
	class iVehicle;
	class iCharacterController;
}
class UIManager;
class DefaultCamera;
class BGObject;

// A game scene class that inherits from the engine's CScene class
class SceneDungeon : public Engine::CScene
{
private:
	Engine::CInputDevice*			m_pInputDevice;
	Engine::CLayer*					m_pCharacterLayer;
	Engine::CSkyBox*				m_pSkyBox;
	UIManager*						m_pUIManager;
	DefaultCamera*					m_pDefaultCamera;

	glm::vec3						m_vCameraSavedPos;
	glm::vec3						m_vCameraSavedRot;
	glm::vec3						m_vCameraSavedTarget;

	Engine::iPhysicsFactory*		m_pPFactory;
	Engine::iPhysicsWorld*			m_pPWorld;

	std::vector<BGObject*>			m_vecSpheres;
	std::vector<Engine::CGameObject*> m_vecTargets;
	_uint							m_iCurTargetIdx;

	Engine::iVehicle*				m_Vehicle;
	Engine::iCharacterController*	m_Controller;


private:
	explicit SceneDungeon();
	virtual ~SceneDungeon();
	virtual void Destroy();
public:
	virtual void Update(const _float& dt);
	virtual void Render();
	
public:
	glm::vec3 GetCameraPos();
	void CollisionCallback();
	std::string GetCurrentTargetName();
private:
	void KeyCheck();
	void SetDefaultCameraSavedPosition(glm::vec3 vPos, glm::vec3 vRot, glm::vec3 target);
	void ResetDefaultCameraPos();

private:
	RESULT Ready(std::string dataPath);
	RESULT ReadyLayerAndGameObject();
	BGObject* AddNewObject(Engine::CLayer* pLayer, std::string meshId, glm::vec3 vPos,
		glm::vec3 vRot, glm::vec3 vScale, _bool isStatic, Engine::eShapeType shapeType);
	void LoadObjects();
	void AddVehicle();
	void AddCharacterController();
	std::string GetMeshIdByNumber(_int num);
	
public:
	static SceneDungeon* Create(std::string dataPath);

};

#endif //_SCENEDUNGEON_H_