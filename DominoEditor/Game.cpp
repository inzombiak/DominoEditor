#define _USE_MATH_DEFINES
#include <cmath>

#include "Game.h"
#include "Debug.h"
#include "PhysicsDefs.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "EventManager.h"
#include "Object.h"
#include "EDSelectObjectClick.h"
#include "EDApplyForce.h"
#include "EDGetPhysicsData.h"
#include "EDCreateConstraint.h"

Game::Game()
{

}

Game::~Game()
{
	if (m_renderManager)
		delete m_renderManager;
	if (m_physicsManager)
		delete m_physicsManager;
	if (m_objectManager)
		delete m_objectManager;
	if (EventManager::GetInstance())
		EventManager::DestroyInstance();

}

void Game::Init()
{
	InitSim();
}

void Game::Draw()
{
	if (!m_keyMap[GameDefs::GameKey::Alt])
		m_renderManager->UpdateCameraPosition(m_keyMap);
	m_renderManager->Draw();
}

void Game::InitSim()
{
	m_gameState = Initializing;

	m_physicsManager = new PhysicsManager();
	m_renderManager = new RenderManager();
	m_objectManager = new ObjectManager();

	if (m_physicsManager)
		m_physicsManager->Init();
	else
		printf("SIM INIT ERROR");
	if (m_renderManager)
		m_renderManager->Init();
	else
		printf("SIM INIT ERROR");
	if (m_objectManager)
		m_objectManager->Init();
	else
		printf("SIM INIT ERROR");

	EventManager::GetInstance()->AddEventListener(EventDefs::SELECT_OBJECT_CLICK, std::bind(&Game::SelectObjectWithClick, this, std::placeholders::_1));
	EventManager::GetInstance()->AddEventListener(EventDefs::APPLY_FORCE, std::bind(&Game::ApplyForce, this, std::placeholders::_1));
	m_physicsManager->SetDebugDrawer(m_renderManager->GetDebugDrawer());
	Test();
	m_gameState = Running;

}

void Game::Reset()
{
	if (m_renderManager)
		delete m_renderManager;
	if (m_physicsManager)
		delete m_physicsManager;
	if (m_objectManager)
		delete m_objectManager;

	InitSim();
}

void TestCompound()
{
	ObjectCreationData* obj1Data = new ObjectCreationData();
	obj1Data->name = "obj1";

	auto getPhysCompData = new EDGetPhysicsData(std::string("Domino"));
	EventManager::GetInstance()->QueueEvent(EventDefs::GET_PHYSICS_DATA, getPhysCompData, true);

	if (!getPhysCompData->WasDataFound())
		return;

	obj1Data->renderCompData->color.push_back(glm::vec3(1.0f, 0.5f, 1.f));
	obj1Data->renderCompData->drawType = GL_TRIANGLES;
	auto boxData = dynamic_cast<PhysicsDefs::BoxCreationData*>(getPhysCompData->GetData());
	glm::vec3 pos(0, 0, 0);
	if (boxData)
	{
		boxData->mass = 2;

		boxData->boxDimensions[0] = 6;
		boxData->boxDimensions[1] = 1;
		boxData->boxDimensions[2] = 1;

		obj1Data->renderCompData->vertices = CreateBox(pos, boxData->boxDimensions[0] * 2, boxData->boxDimensions[1] * 2, boxData->boxDimensions[2] * 2);
	}

	btTransform trans;
	trans.setIdentity();
	
	PhysicsDefs::CompoundCreationData* compData = new PhysicsDefs::CompoundCreationData();

	compData->rigidBodies.push_back(boxData->clone());
	compData->shapePositions.push_back(trans);

	trans.setIdentity();
	trans.setRotation(btQuaternion(0, 0, M_PI_2));
	trans.setOrigin(btVector3(-3, -6.5, 0));
	compData->rigidBodies.push_back(boxData->clone());
	compData->shapePositions.push_back(trans);

	trans.setIdentity();
	trans.setRotation(btQuaternion(0, 0, M_PI_2));
	trans.setOrigin(btVector3(3, -6.5, 0));
	compData->rigidBodies.push_back(boxData->clone());
	compData->shapePositions.push_back(trans);

	obj1Data->physCompData = compData;
	compData->friction = 0.5;

	compData->msPosition[0] = 0;
	compData->msPosition[1] = 7;
	compData->msPosition[2] = 0;

	compData->rotationAngles[0] = 0;
	compData->rotationAngles[1] = 0;
	compData->rotationAngles[2] = 0;

	EDCreateObject* eventData = new EDCreateObject(obj1Data);
	EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_OBJECT, eventData, true);
}

void Game::Test()
{
	printf("Start test \n");

	if (m_physicsManager && m_objectManager && m_renderManager)
	{
		{//SPIRAL
			ObjectCreationData* spiralGroundData = new ObjectCreationData();
			spiralGroundData->name = "test";

			EDGetPhysicsData* getPhysCompData = new EDGetPhysicsData(std::string("Ground"));
			EventManager::GetInstance()->QueueEvent(EventDefs::GET_PHYSICS_DATA, getPhysCompData, true);

			if (getPhysCompData->WasDataFound())
				spiralGroundData->physCompData = getPhysCompData->GetData();
			else
				printf("NO DATA \n");
			spiralGroundData->renderCompData->color.push_back(glm::vec3(0.5f, 0.5f, 0.f));
			spiralGroundData->renderCompData->drawType = GL_TRIANGLES;
			glm::vec3 pos(0, 0, 0);
			PhysicsDefs::BoxCreationData* boxData = dynamic_cast<PhysicsDefs::BoxCreationData*>(spiralGroundData->physCompData);
			if (boxData)
				spiralGroundData->renderCompData->vertices = CreateBox(pos, boxData->boxDimensions[0] * 2, boxData->boxDimensions[1] * 2, boxData->boxDimensions[2] * 2);
			EDCreateObject* eventData = new EDCreateObject(spiralGroundData);
			EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_OBJECT, eventData, true);
		}
		
		//Obj1
		ObjectCreationData* obj1Data = new ObjectCreationData();
		obj1Data->name = "obj1";
		{
			EDGetPhysicsData* getPhysCompData = new EDGetPhysicsData(std::string("Domino"));
			EventManager::GetInstance()->QueueEvent(EventDefs::GET_PHYSICS_DATA, getPhysCompData, true);

			if (getPhysCompData->WasDataFound())
				obj1Data->physCompData = getPhysCompData->GetData();
			else
				printf("                  NO DATA2 \n");
			glm::vec3 pos(0, 0, 0);
			obj1Data->renderCompData->color.push_back(glm::vec3(1.0f, 0.5f, 1.f));
			obj1Data->renderCompData->drawType = GL_TRIANGLES;
			PhysicsDefs::BoxCreationData*  boxData2 = dynamic_cast<PhysicsDefs::BoxCreationData*>(obj1Data->physCompData);
			if (boxData2)
			{
				boxData2->mass = 0;
				boxData2->boxDimensions[0] = 0.5;
				boxData2->boxDimensions[1] = 1;

				boxData2->msPosition[1] = 16.f;

				obj1Data->renderCompData->vertices = CreateBox(pos, boxData2->boxDimensions[0] * 2, boxData2->boxDimensions[1] * 2, boxData2->boxDimensions[2] * 2);
			}

			auto obj1EventData = new EDCreateObject(obj1Data);
			obj1EventData->SetIsSynchrnous(true);
			EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_OBJECT, obj1EventData, true);
			printf("\n OBJ1 made \n");
		}
		//Obj2
		
		ObjectCreationData* obj2Data = new ObjectCreationData();
		obj2Data->name = "obj2";
		{
			EDGetPhysicsData* getPhysCompData = new EDGetPhysicsData(std::string("Domino"));
			EventManager::GetInstance()->QueueEvent(EventDefs::GET_PHYSICS_DATA, getPhysCompData, true);

			if (getPhysCompData->WasDataFound())
				obj2Data->physCompData = getPhysCompData->GetData();
			else
				printf("                  NO DATA3 \n");
			glm::vec3 pos(0, 0, 0);
			obj2Data->renderCompData->color.push_back(glm::vec3(0.0f, 0.5f, 1.f));
			obj2Data->renderCompData->drawType = GL_TRIANGLES;
			PhysicsDefs::BoxCreationData* boxData = dynamic_cast<PhysicsDefs::BoxCreationData*>(obj2Data->physCompData);
			if (boxData)
			{
				boxData->mass = 10;
				boxData->boxDimensions[0] = 0.75;
				boxData->boxDimensions[1] = 1;
				boxData->boxDimensions[2] = 0.2;

				boxData->msPosition[1] = 14.f;
				obj2Data->renderCompData->vertices = CreateBox(pos, boxData->boxDimensions[0] * 2, boxData->boxDimensions[1] * 2, boxData->boxDimensions[2] * 2);
			}

			auto obj2EventData = new EDCreateObject(obj2Data);
			obj2EventData->SetIsSynchrnous(true);
			EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_OBJECT, obj2EventData, true);
		}
		

		//6DoFConstraint
		auto obj1 = obj1Data->createdObject;
		auto obj2 = obj2Data->createdObject;

		if (!obj1 && !obj2)
			return;

		btVector3 anchor(0.f, 16, 0.f);
		PhysicsDefs::ConstraintCreationData* constraintData = new PhysicsDefs::ConstraintCreationData();
		constraintData->body1 = obj1;
		constraintData->body2 = obj2;
		constraintData->anchor = anchor;

		constraintData->lowerAngularLimit = btVector3(0.f + DBL_EPSILON, -M_PI_2 * 0.5 + DBL_EPSILON, -M_PI_2 * 0.5 + DBL_EPSILON);
		constraintData->upperAngularLimit = btVector3(0.f + DBL_EPSILON, M_PI_2 * 0.5 + DBL_EPSILON, M_PI_2 *0.5 + DBL_EPSILON);

		constraintData->lowerLinearLimit = btVector3(0., 0., 0.);
		constraintData->upperLinearLimit = btVector3(0., 0., 0.);
		
		EDCreateConstraint* constData = new EDCreateConstraint(constraintData);
		EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_CONSTRAINT, constData, true);
		//Obj2
		ObjectCreationData* obj3Data = new ObjectCreationData();
		obj1Data->name = "obj3";

		{
		
			EDGetPhysicsData* getPhysCompData = new EDGetPhysicsData(std::string("Domino"));
			EventManager::GetInstance()->QueueEvent(EventDefs::GET_PHYSICS_DATA, getPhysCompData, true);

			if (getPhysCompData->WasDataFound())
				obj3Data->physCompData = getPhysCompData->GetData();
			glm::vec3 pos(0, 0, 0);
			obj3Data->renderCompData->color.push_back(glm::vec3(1.f, 0.5f, 0.f));
			obj3Data->renderCompData->drawType = GL_TRIANGLES;
			PhysicsDefs::BoxCreationData* boxData = dynamic_cast<PhysicsDefs::BoxCreationData*>(obj3Data->physCompData);
			if (boxData)
			{
				boxData->mass = 4;
				boxData->boxDimensions[0] = 0.75;
				boxData->boxDimensions[1] = 1;
				boxData->boxDimensions[2] = 0.2;

				boxData->msPosition[1] = 12.f;
				obj3Data->renderCompData->vertices = CreateBox(pos, boxData->boxDimensions[0] * 2, boxData->boxDimensions[1] * 2, boxData->boxDimensions[2] * 2);
			}

			auto obj3EventData = new EDCreateObject(obj3Data);
			obj3EventData->SetIsSynchrnous(true);
			EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_OBJECT, obj3EventData, true);
		}
		////6DoFConstraint
		auto obj3 = obj3Data->createdObject;

		if (!obj2 && !obj3)
			return;

		anchor = btVector3(0.f, 13.f, 0.f);

		constraintData = new PhysicsDefs::ConstraintCreationData();

		constraintData->body1 = obj2;
		constraintData->body2 = obj3;
		constraintData->anchor = anchor;

		constraintData->lowerAngularLimit = btVector3(0.f + DBL_EPSILON, -M_PI_2 * 0.5 + DBL_EPSILON, -M_PI_2 * 0.5 + DBL_EPSILON);
		constraintData->upperAngularLimit = btVector3(0.f + DBL_EPSILON, M_PI_2 * 0.5 + DBL_EPSILON, M_PI_2 *0.5 + DBL_EPSILON);

		constraintData->lowerLinearLimit = btVector3(0., 0., 0.);
		constraintData->upperLinearLimit = btVector3(0., 0., 0.);

		constData = new EDCreateConstraint(constraintData);
		EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_CONSTRAINT, constData, true);

		TestCompound();

		/*
		// value of theta corresponding to end of last coil
		double thetaMax = 4 * 2 * M_PI;
		// How far to step away from center for each side.
		double awayStep = 40 / thetaMax;

		// distance between points to plot
		double chord = 6;
		double rotation = 0;
		int angle = 0;
		float radialDistance = 0.f;
		double x, z;
		ObjectCreationData* domino;

		
		for (double theta = chord / awayStep; theta <= thetaMax;)
		{
			// How far away from center
			double away = awayStep * theta;
			// Convert 'around' and 'away' to X and Y.
			x = away * cos(theta + rotation);
			z = away  * sin(theta + rotation);

			domino = new ObjectCreationData();
			getPhysCompData = new EDGetPhysicsData(std::string("Domino"));
			EventManager::GetInstance()->QueueEvent(EventDefs::GET_PHYSICS_DATA, getPhysCompData, true);

			if (getPhysCompData->WasDataFound())
				domino->physCompData = getPhysCompData->GetData();
			auto physData = domino->physCompData;

			printf("X: %lf, Z: %lf \n", x, z);
			boxData = dynamic_cast<PhysicsDefs::BoxCreationData*>(physData);

			if (boxData)
				domino->renderCompData->vertices = CreateBox(pos, boxData->boxDimensions[0] * 2, boxData->boxDimensions[1] * 2, boxData->boxDimensions[2] * 2);

			boxData->msPosition[0] = x;
			boxData->msPosition[1] = boxData->boxDimensions[1] - 2;
			boxData->msPosition[2] = z;

		//	glm::quat quatRot(glm::vec3(0, -theta - rotation - 50, 0));

			boxData->rotationAngles[1] = (-theta - rotation) * 180 / M_PI;
			
			domino->renderCompData->color.push_back(glm::vec3(1.f, 0.5f, 0.f));
			domino->renderCompData->drawType = GL_TRIANGLES;
			eventData = new EDCreateObject(domino);
			
			EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_OBJECT, eventData, false);

		
			 //to a first approximation, the points are on a circle
			 //so the angle between them is chord/radius
			theta += chord / away;
		}*/
		
		/*
		//SPLIT
		float splitGroundCenter = 100;
		ObjectCreationData* splitGroundData = new ObjectCreationData();
		splitGroundData->name = "splitGround";
		m_physicsManager->GetPhysCompCreationData("Ground", *(splitGroundData->physCompData));
		eventData = new EDCreateObject(splitGroundData);

		splitGroundData->physCompData->msPosition[0] = splitGroundCenter;
		splitGroundData->renderCompData->color.push_back(glm::vec3(0.5f, 0.5f, 0.f));
		splitGroundData->renderCompData->drawType = GL_TRIANGLES;
		splitGroundData->renderCompData->vertices = CreateBox(pos, splitGroundData->physCompData->boxDimensions[0]*2
		, splitGroundData->physCompData->boxDimensions[1]*2, splitGroundData->physCompData->boxDimensions[2]*2);
		EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_OBJECT, eventData);
		z = -80;

		domino = new ObjectCreationData();
		m_physicsManager->GetPhysCompCreationData("Domino", *(domino->physCompData));
		domino->name = "main";
		auto physData = domino->physCompData;

		physData->msPosition[0] = splitGroundCenter;
		physData->msPosition[1] = 0;
		physData->msPosition[2] = z;

		domino->renderCompData->color.push_back(glm::vec3(0.f, 0.f, 1.f));
		domino->renderCompData->drawType = GL_TRIANGLES;
		domino->renderCompData->vertices = CreateBox(pos, physData->boxDimensions[0], physData->boxDimensions[1], physData->boxDimensions[2]);

		eventData = new EDCreateObject(domino);
		EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_OBJECT, eventData);

		z += chord;

		for (int i = 1; i < 15; ++i)
		{
		domino = new ObjectCreationData();
		m_physicsManager->GetPhysCompCreationData("Domino", *(domino->physCompData));
		physData = domino->physCompData;

		physData->msPosition[0] = splitGroundCenter;
		physData->msPosition[1] = 0;
		physData->msPosition[2] = z;

		eventData = new EDCreateObject(domino);
		domino->renderCompData->color.push_back(glm::vec3(0.f, 0.f, 1.f));
		domino->renderCompData->drawType = GL_TRIANGLES;
		domino->renderCompData->vertices = CreateBox(pos, physData->boxDimensions[0]*2, physData->boxDimensions[1]*2, physData->boxDimensions[2]*2);
		EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_OBJECT, eventData);

		z += chord;
		}

		double x1 = splitGroundCenter + 40;
		double x2 = splitGroundCenter - 40;
		double z1 = z - chord;
		// value of theta corresponding to end of last coil
		thetaMax = 4 * 2 * M_PI;
		// How far to step away from center for each side.
		awayStep = 40 / thetaMax;
		rotation = 110;
		for (double theta = chord / awayStep; theta <= thetaMax;)
		{
		// How far away from center
		double away = awayStep * theta;
		// Convert 'around' and 'away' to X and Y.
		x = x1 + away * cos(theta + rotation);
		z = z1 + away * sin(theta + rotation);

		domino = new ObjectCreationData();
		m_physicsManager->GetPhysCompCreationData("Domino", *(domino->physCompData));
		auto physData = domino->physCompData;

		physData->msPosition[0] = x;
		physData->msPosition[1] = 0;
		physData->msPosition[2] = z;

		glm::quat quatRot(glm::vec3(0,  -theta - rotation - 50, 0));

		physData->msQuaternion[0] = quatRot.x;
		physData->msQuaternion[1] = quatRot.y;
		physData->msQuaternion[2] = quatRot.z;
		physData->msQuaternion[3] = quatRot.w;
		domino->renderCompData->color.push_back(glm::vec3(0.f, 0.f, 1.f));
		domino->renderCompData->drawType = GL_TRIANGLES;
		domino->renderCompData->vertices = CreateBox(pos, physData->boxDimensions[0] * 2, physData->boxDimensions[1] * 2, physData->boxDimensions[2] * 2);
		eventData = new EDCreateObject(domino);

		EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_OBJECT, eventData);


		// to a first approximation, the points are on a circle
		// so the angle between them is chord/radius
		theta += chord / away;
		}


		for (double theta = chord / awayStep; theta <= thetaMax;)
		{
		// How far away from center
		double away = awayStep * theta;
		// Convert 'around' and 'away' to X and Y.
		x = x2 - away * cos(theta + rotation);
		z = z1 + away * sin(theta + rotation);

		domino = new ObjectCreationData();
		m_physicsManager->GetPhysCompCreationData("Domino", *(domino->physCompData));
		auto physData = domino->physCompData;

		physData->msPosition[0] = x;
		physData->msPosition[1] = 0;
		physData->msPosition[2] = z;

		glm::quat quatRot(glm::vec3(0, theta + rotation + 50, 0));

		physData->msQuaternion[0] = quatRot.x;
		physData->msQuaternion[1] = quatRot.y;
		physData->msQuaternion[2] = quatRot.z;
		physData->msQuaternion[3] = quatRot.w;
		domino->renderCompData->color.push_back(glm::vec3(0.f, 0.f, 1.f));
		domino->renderCompData->drawType = GL_TRIANGLES;
		domino->renderCompData->vertices = CreateBox(pos, physData->boxDimensions[0] * 2, physData->boxDimensions[1] * 2, physData->boxDimensions[2] * 2);
		eventData = new EDCreateObject(domino);

		EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_OBJECT, eventData);


		// to a first approximation, the points are on a circle
		// so the angle between them is chord/radius
		theta += chord / away;
		}
		}*/
	}

	printf("End test \n");
}

void Game::Step(double dt)
{
	if (m_gameState != Running)
		return;
	m_renderManager->ClearRender();
	EventManager::GetInstance()->ProcessEvents();
	if (m_keyMap[GameDefs::GameKey::Delete] && m_selectedObject)
		DeleteSelectedObject();
	m_physicsManager->Step(dt, m_numberOfSubSteps, m_timeStep, m_keyMap);
	m_objectManager->Step();
	m_renderManager->Step();

	Debug::PrintFPS();
	
}

void Game::DeleteSelectedObject()
{
	m_physicsManager->DeletePhysicsCompoenent(m_selectedObject->GetPhysicsComponent());
}
void Game::UpdateCameraRotation(float xRotate, float yRotate)
{
	if (m_keyMap[GameDefs::GameKey::Alt] || m_keyMap[GameDefs::GameKey::Ctrl])
		return;

	if (m_renderManager)
		m_renderManager->UpdateCameraRotation(xRotate, yRotate);
}

void Game::SetKey(GameDefs::GameKey key, bool value)
{
	m_keyMap[key] = value;
}

void Game::SelectObjectWithClick(IEventData* data)
{
	EDSelectObjectClick* selectObjectData = dynamic_cast<EDSelectObjectClick*>(data);
	if (!selectObjectData)
		return;

	float distance = 5.;
	float mouseX = selectObjectData->GetMouseX(), mouseY = selectObjectData->GetMouseY();

	Ray rayCast = CalculateRay(mouseX, mouseY, distance);

	auto result = m_physicsManager->Grab(rayCast.start, rayCast.end);

	if (!result.hasHit())
		return;

	Object* object = static_cast<Object*> (result.m_collisionObject->getUserPointer());
	//if (object && selectObjectData->RetrievePhysics())

	
}

void Game::ApplyForce(IEventData* data)
{


	EDApplyForce* forceData = dynamic_cast<EDApplyForce*>(data);
	if (!forceData)
		return;

	float distance = 100.;
	float mouseX = forceData->GetMouseX(), mouseY = forceData->GetMouseY();

	Ray rayCast = CalculateRay(mouseX, mouseY, distance);

	auto result = m_physicsManager->Grab(rayCast.start, rayCast.end);


	if (!result.hasHit())
		return;

	Object* object = static_cast<Object*> (result.m_collisionObject->getUserPointer());
	if (!object)
		return;

	m_physicsManager->ApplyForce(object->GetPhysicsComponent(), glm::vec3(result.m_hitPointWorld.getX(), result.m_hitPointWorld.getY(), result.m_hitPointWorld.getZ()),
		rayCast.end - rayCast.start, forceData->GetAmount());
	
}

Game::Ray Game::CalculateRay(float startX, float startY, float distance)
{
	Game::Ray result;

	glm::vec4 lRayStart_NDC(
		((float)startX / m_screenWidth - 0.5f) * 2.0f,
		((float)startY / m_screenHeight - 0.5f) * 2.0f,
		0,
		1.f
		);
	glm::vec4 lRayEnd_NDC(
		((float)startX / m_screenWidth - 0.5f) * 2.0f,
		((float)startY / m_screenHeight - 0.5f) * 2.0f,
		1.f,
		1.f
		);

	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 200.0f);
	glm::mat4 view = m_renderManager->GetViewMat4();
	glm::mat4 M = glm::inverse(projection * view);;
	glm::vec4 lRayStart_world = M * lRayStart_NDC;
	lRayStart_world /= lRayStart_world.w;
	glm::vec4 lRayEnd_world = M * lRayEnd_NDC;
	lRayEnd_world /= lRayEnd_world.w;

	glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
	lRayDir_world = glm::normalize(lRayDir_world);

	result.start = glm::vec3(lRayStart_world);
	result.end = result.start + distance * glm::normalize(lRayDir_world);

	return result;
}