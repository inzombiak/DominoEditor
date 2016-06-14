#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <map>

#include "IEventData.h"
#include "HelperFunctions.h"
#include "GameDefs.h"

class RenderManager;
class PhysicsManager;
class ObjectManager;
class Object;
class Game
{
public:
	Game();
	~Game();
	void Init();
	void Draw();
	void Step(double timePassed);
	void UpdateCameraRotation(float xRotate, float yRotate);
	void SetKey(GameDefs::GameKey key, bool value);
	void SetScreenSize(int screenWidth, int screenHeight)
	{
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
	}

private:
	
	struct Ray
	{
		glm::vec3 start;
		glm::vec3 end;
	};

	void Test();
	void InitSim();
	void Reset();
	void DeleteSelectedObject();
	void SelectObjectWithClick(IEventData* data);
	void ApplyForce(IEventData* data);
	Ray CalculateRay(float startX, float startY, float distance);
	enum GameState
	{
		Initializing,
		Running,
		Closing,
		Reseting,
	};

	int m_screenWidth, m_screenHeight;
	float m_timeStep = 1.f / 240.f;
	int m_numberOfSubSteps = 10;
	GameState m_gameState;
	RenderManager* m_renderManager;
	PhysicsManager* m_physicsManager;
	ObjectManager* m_objectManager;
	Object* m_selectedObject;
	std::map<GameDefs::GameKey, bool> m_keyMap;
};

