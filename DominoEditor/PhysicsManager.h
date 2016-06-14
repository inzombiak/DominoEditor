#pragma once

#include <vector>
#include <map>
#include "PhysicsWorld.h"
#include "PhysicsComponent.h"
#include "HelperFunctions.h"
#include "GameDefs.h"
#include "PhysicsDefs.h"
#include <array>

#include "tinyxml2.h"
#include "btBulletDynamicsCommon.h"

class EDCreatePhysComp;
class IEventData;
class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();
	void Init();
	void Clear();
	void Step(float dt, int maxSubStep, double timeStep, std::map<GameDefs::GameKey, bool>& keys);
	void SetDebugDrawer(btIDebugDraw* btDD)
	{
		m_physicsWorld.SetDebugDraw(btDD);
	}

	void ApplyForce(PhysicsComponent* component, glm::vec3& hitPoint, glm::vec3& direction, float amount);
	btCollisionWorld::ClosestRayResultCallback Grab(glm::vec3 start, glm::vec3 end);
	void DeletePhysicsCompoenent(PhysicsComponent* componenet);

private:
	typedef btCollisionShape* (PhysicsManager::*CollisionShapeCreationFunction)(tinyxml2::XMLElement*);
	typedef std::map<std::string, CollisionShapeCreationFunction> CollisionShapeCreationFunctionMap;

	void CreatePhysicsComponent(IEventData* data);
	void CreateConstraint(IEventData* data);

	void CreateRigidBody(PhysicsDefs::IRigidBodyCreationData* RBCD, std::size_t hashID);
	void CreateCompoundBody(PhysicsDefs::CompoundCreationData* compData, std::size_t hashID);

	btCollisionShape* CreateSphereCollisionShape(tinyxml2::XMLElement* objectNode);
	btCollisionShape* CreateBoxCollisionShape(tinyxml2::XMLElement* objectNode);
	btCollisionShape* CreateTriangleMeshCollisionShape(tinyxml2::XMLElement* objectNode);
	
	PhysicsDefs::ICreationData* RBCIToPhyCompData(btRigidBody::btRigidBodyConstructionInfo*);
	PhysicsDefs::ICreationData* GetComponentConstructionData(unsigned int id);

	PhysicsDefs::BoxCreationData* CreateBoxCreationData(btRigidBody::btRigidBodyConstructionInfo* rbci);
	PhysicsDefs::SphereCreationData* CreateSphereCreationData(btRigidBody::btRigidBodyConstructionInfo* rbci);

	void GetPhysCompCreationData(IEventData* data);
	void LoadCIFromXMLDocument(tinyxml2::XMLDocument* document);
	std::size_t HashPhysCreationData(PhysicsDefs::ICreationData* data);
	btScalar CalculateBrakeForce(btWheelInfo& wheelInfo);

	float currentSteering = 0, steeringIncrement = 0.04f, maxSteering = 0.3f;
	float currentEngineForce = 0.f, maxEngineForce = 100.f;
	float breakingForce = 0.f;

	PhysicsWorld m_physicsWorld;
	btTriangleMesh m_testTriangleMesh;
	btRaycastVehicle* m_vehicle;
	std::vector<PhysicsComponent*> m_physicsComponents;
	std::vector<btCollisionShape*> m_collisionShapes;
	std::map<std::string, btRigidBody::btRigidBodyConstructionInfo*> m_preloadedInfo;
	std::map<std::size_t, btRigidBody::btRigidBodyConstructionInfo*> m_RBCIMap;
	CollisionShapeCreationFunctionMap m_collisionShapeCreationFunctions;
};

