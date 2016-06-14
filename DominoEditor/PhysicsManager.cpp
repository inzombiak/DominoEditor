#define _USE_MATH_DEFINES

#include "Object.h"
#include "PhysicsManager.h"
#include "GameDefs.h"
#include "PhysicsDefs.h"
#include "EventManager.h"
#include "EDCreatePhysComp.h"
#include "EDGetPhysicsData.h"
#include "EDCreateConstraint.h"

#include "RigidPhysBody.h"

#include <iostream>
#include<cmath>

PhysicsManager::PhysicsManager()
{
	m_collisionShapeCreationFunctions["box"] = &PhysicsManager::CreateBoxCollisionShape;
	m_collisionShapeCreationFunctions["sphere"] = &PhysicsManager::CreateSphereCollisionShape;
	m_collisionShapeCreationFunctions["trianglemesh"] = &PhysicsManager::CreateTriangleMeshCollisionShape;
	m_vehicle = 0;
}

PhysicsManager::~PhysicsManager()
{
	Clear();

}


void PhysicsManager::Init()
{
	m_physicsWorld.Init();
	std::string filepath = "Resources/BulletConstructionInfos.xml";

	tinyxml2::XMLDocument CIXML;
	if (CIXML.LoadFile(filepath.c_str()) == tinyxml2::XMLError::XML_SUCCESS)
		LoadCIFromXMLDocument(&CIXML);

	EventManager::GetInstance()->AddEventListener(EventDefs::CREATE_PHYSICS_COMPONENT, std::bind(&PhysicsManager::CreatePhysicsComponent, this, std::placeholders::_1));
	EventManager::GetInstance()->AddEventListener(EventDefs::GET_PHYSICS_DATA, std::bind(&PhysicsManager::GetPhysCompCreationData, this, std::placeholders::_1));
	EventManager::GetInstance()->AddEventListener(EventDefs::CREATE_CONSTRAINT, std::bind(&PhysicsManager::CreateConstraint, this, std::placeholders::_1));

	//EventManager::GetInstance()->AddEventListener(EventDefs::APPLY_FORCE, std::bind(&PhysicsManager::ApplyForce, this, std::placeholders::_1));

	//btCollisionShape* carBoxShape = new btBoxShape(btVector3(1.f, 0.5f, 2.f));
	//m_collisionShapes.push_back(carBoxShape);
	//btCompoundShape* carCompoundShape = new btCompoundShape();
	//m_collisionShapes.push_back(carCompoundShape);
	//btTransform chassisLS;
	//chassisLS.setIdentity();
	//chassisLS.setOrigin(btVector3(0.0f, 1, 0.f));
	//carCompoundShape->addChildShape(chassisLS, carBoxShape);
	//btTransform tr;
	//tr.setIdentity();
	//tr.setOrigin(btVector3(0,20,25));
	//btDefaultMotionState* pMotionState = new btDefaultMotionState(tr);
	//float mass = 350;
	//btVector3 intertia;
	//carBoxShape->calculateLocalInertia(mass, intertia);
	//btRigidBody::btRigidBodyConstructionInfo* carRigidBodyCI = new btRigidBody::btRigidBodyConstructionInfo(mass, pMotionState, carCompoundShape, intertia);
	//m_preloadedInfo["car"] = carRigidBodyCI;
	//m_RBCIMap[HashPhysCreationData(&RBCIToPhyCompData(carRigidBodyCI))] = carRigidBodyCI;

}

void PhysicsManager::LoadCIFromXMLDocument(tinyxml2::XMLDocument* doc)
{
	tinyxml2::XMLNode* pRoot = doc->FirstChild();
	tinyxml2::XMLElement* pObject = pRoot->FirstChildElement("Object");
	std::string objectName, objectCollisionShapeType;
	float mass, friction, rollingFriction;
	btRigidBody::btRigidBodyConstructionInfo* RBCI;
	btCollisionShape* collisionShape = NULL;
	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
	float x, y, z, w;
	btVector3 position(0, 0, 0), inertia(0, 0, 0);
	btQuaternion rotation(0,0,0,0);
	while (pObject != nullptr)
	{
		objectName = pObject->Attribute("name");
		tinyxml2::XMLElement* pShape = pObject->FirstChildElement("Shape");

		if (!pShape)
			continue;
		btCollisionShape* collisionShape = (this->*m_collisionShapeCreationFunctions[pShape->Attribute("type")])(pShape);
		m_collisionShapes.push_back(collisionShape);

		tinyxml2::XMLElement* pMotionState = pObject->FirstChildElement("MotionState");
		if (pMotionState)
		{
			tinyxml2::XMLElement* pMotionStateRotation = pMotionState->FirstChildElement("Rotation");
			tinyxml2::XMLElement* pMotionStatePosition = pMotionState->FirstChildElement("Position");
			if (pMotionStateRotation && pMotionStatePosition)
			{
				pMotionStateRotation->QueryFloatAttribute("x", &x);
				pMotionStateRotation->QueryFloatAttribute("y", &y);
				pMotionStateRotation->QueryFloatAttribute("z", &z);
				pMotionStateRotation->QueryFloatAttribute("w", &w);
				rotation.setX(x);
				rotation.setY(y);
				rotation.setZ(z);
				rotation.setW(w);

				pMotionStatePosition->QueryFloatAttribute("x", &x);
				pMotionStatePosition->QueryFloatAttribute("y", &y);
				pMotionStatePosition->QueryFloatAttribute("z", &z);
				position.setX(x);
				position.setY(y);
				position.setZ(z);
						  
				motionState = new btDefaultMotionState(btTransform(rotation, position));
			}
		}
		else
			motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));;
		
		tinyxml2::XMLElement* pMass = pObject->FirstChildElement("Mass");
		if (pMass && pMass->DoubleAttribute("value") > 0)
		{
			mass = pMass->DoubleAttribute("value");
			collisionShape->calculateLocalInertia(mass, inertia);
		}
		else
		{
			mass = 0;
			inertia = btVector3(0, 0, 0);
		}

		RBCI = new btRigidBody::btRigidBodyConstructionInfo(mass, motionState, collisionShape, inertia);

		tinyxml2::XMLElement* pFriction = pObject->FirstChildElement("Friction");
		if (pFriction)
		{
			pFriction->QueryFloatAttribute("value", &friction);
			RBCI->m_friction = friction;
		}

		tinyxml2::XMLElement* pRollingFriction = pObject->FirstChildElement("RollingFriction");
		if (pRollingFriction)
		{
			pRollingFriction->QueryFloatAttribute("value", &rollingFriction);
			RBCI->m_friction = rollingFriction;
		}

		m_preloadedInfo[objectName] = RBCI;

		pObject = pObject->NextSiblingElement();
	}
}

void PhysicsManager::Clear()
{
	for (unsigned int i = 0; i < m_physicsComponents.size(); ++i)
	{
		if (m_physicsComponents[i])
		{
			delete m_physicsComponents[i];
			m_physicsComponents[i] = 0;
		}
	}

	for (unsigned int i = 0; i < m_collisionShapes.size(); ++i)
	{
		delete m_collisionShapes[i];
		m_collisionShapes[i] = 0;
	}
	m_collisionShapes.clear();

	for (auto it = m_RBCIMap.begin(); it != m_RBCIMap.end(); ++it)
	{
		delete it->second;
		it->second = 0;
	}
	m_RBCIMap.clear();
	m_preloadedInfo.clear();

	if (m_vehicle);
		delete m_vehicle;
	
	m_vehicle = 0;
}

void PhysicsManager::Step(float dt, int maxSubStep, double timeStep, std::map<GameDefs::GameKey, bool>& keys)
{
	m_physicsWorld.Step(dt, maxSubStep, timeStep);

	//if (keys[GameDefs::GameKey::Up])
	//	currentEngineForce = maxEngineForce;
	//if (keys[GameDefs::GameKey::Down])
	//	currentEngineForce = -maxEngineForce;
	//if (!keys[GameDefs::GameKey::Up] && !keys[GameDefs::GameKey::Down])
	//	currentEngineForce = 0;
	//	
	//if (keys[GameDefs::GameKey::Right])
	//{
	//	currentSteering += steeringIncrement;
	//	if (currentSteering > maxSteering)
	//		currentSteering = maxSteering;
	//}
	//if (keys[GameDefs::GameKey::Left])
	//{
	//	currentSteering -= steeringIncrement;
	//	if (currentSteering < -maxSteering)
	//		currentSteering = -maxSteering;
	//}
	//if (!keys[GameDefs::GameKey::Left] && !keys[GameDefs::GameKey::Right])
	//	currentSteering = 0;

	//if (m_vehicle)
	//{
	//	for (int i = 0; i < m_vehicle->getNumWheels(); ++i)
	//	{
	//		if (m_vehicle->getWheelInfo(i).m_bIsFrontWheel)
	//		{
	//			m_vehicle->setSteeringValue(currentSteering, i);
	//			//m_vehicle->setBrake(CalculateBrakeForce(m_vehicle->getWheelInfo(i)), i);
	//		}
	//		else
	//		{
	//			m_vehicle->setBrake(CalculateBrakeForce(m_vehicle->getWheelInfo(i)), i);
	//			m_vehicle->applyEngineForce(currentEngineForce, i);
	//			
	//		}
	//	}
	//}
	
	for (unsigned int i = 0; i < m_physicsComponents.size(); ++i)
		if (m_physicsComponents[i])
			m_physicsComponents[i]->Update();
}

void PhysicsManager::DeletePhysicsCompoenent(PhysicsComponent* component)
{
	if (component)
	{
		m_physicsWorld.RemoveBody(component->GetBody());
		component = 0;
		delete component;
	}
		
}

btCollisionWorld::ClosestRayResultCallback  PhysicsManager::Grab(glm::vec3 start, glm::vec3 end)
{
	btVector3 rayStart(start.x, start.y, start.z);
	btVector3 rayEnd(end.x, end.y, end.z);

	btCollisionWorld::ClosestRayResultCallback result(rayStart, rayEnd);

	m_physicsWorld.Grab(rayStart, rayEnd, result);

	return result;
}

//btRigidBody::btRigidBodyConstructionInfo* PhysicsManager::ObjectSettingsTobtCI(GameDefs::ObjectSettings* settings)
//{
//	float mass;
//	btRigidBody::btRigidBodyConstructionInfo* RBCI;
//	btCollisionShape* collisionShape = NULL;
//	btDefaultMotionState* motionState;
//	btVector3 position(settings->msPosition[0], settings->msPosition[1], settings->msPosition[2]), inertia(0, 0, 0);
//	btQuaternion rotation(settings->msQuaternion[0], settings->msQuaternion[1], settings->msQuaternion[2], settings->msQuaternion[3]);
//
//	if (settings->shapeType == GameDefs::Box)
//		collisionShape = new btBoxShape(btVector3(settings->boxDimensions[0], settings->boxDimensions[1], settings->boxDimensions[2]));
//	else
//		collisionShape = new btSphereShape(settings->sphereRadius);
//
//	motionState = new btDefaultMotionState(btTransform(rotation, position));
//
//	mass = settings->mass;
//	if (mass > 0)
//		collisionShape->calculateLocalInertia(mass, inertia);
//	else
//		mass = 0;
//
//	RBCI = new btRigidBody::btRigidBodyConstructionInfo(mass, motionState, collisionShape, inertia);
//	
//	RBCI->m_friction = settings->friction;
//	RBCI->m_rollingFriction = settings->rollingFriction;
//
//	m_collisionShapes.push_back(collisionShape);
//	m_rigidBodyInfo[settings->objectName] = RBCI;
//
//	return RBCI;
//}

void PhysicsManager::ApplyForce(PhysicsComponent* component, glm::vec3& hitPoint, glm::vec3& direction, float amount)
{
//	hitPoint = glm::vec3(0, 3, 0);
	//direction = glm::vec3(0, 0, 1);
	component->ApplyForce(hitPoint, direction, amount);
}


void PhysicsManager::CreatePhysicsComponent(IEventData* data)
{
	EDCreatePhysComp* physData = dynamic_cast<EDCreatePhysComp*>(data);
	if (!physData)
		return;

	auto settings = physData->GetData();

	std::size_t hashedSettings = HashPhysCreationData(settings);

	IPhysicsBody* body;
	auto existingRBCI = m_RBCIMap.find(hashedSettings);

	if (existingRBCI != m_RBCIMap.end())
	{
		PhysicsComponent* component = new PhysicsComponent(m_physicsComponents.size(), hashedSettings);
		body = new RigidPhysBody();
		body->ConstructFromRBCI(*existingRBCI->second);
		component->SetBody(body);
		component->SetOwner(settings->owner);
		m_physicsWorld.AddBody(body);
		m_physicsComponents.push_back(component);

		return;
	}

	if (settings->GetBody() == PhysicsDefs::PhysicsBodyType::CompoundBody)
	{
		auto compoundSettings= dynamic_cast<PhysicsDefs::CompoundCreationData*>(settings);
		CreateCompoundBody(compoundSettings, hashedSettings);
	}
	else
	{
		auto rbSettings = dynamic_cast<PhysicsDefs::IRigidBodyCreationData*>(settings);
		CreateRigidBody(rbSettings, hashedSettings);
	}

	data->SetDelete(true);

	/*if (objectName.compare("car") == 0)
	{
		rigidBody->setActivationState(DISABLE_DEACTIVATION);

		btRaycastVehicle::btVehicleTuning tuning;
		float	wheelRadius = 0.5f;
		float	wheelWidth = 0.4f;
		float	wheelFriction = .1f;
		float	suspensionStiffness = 20.f;
		float	suspensionDamping = 2.3f;
		float	suspensionCompression = 4.4f;
		float	rollInfluence = .1f;

		tuning.m_maxSuspensionTravelCm = 500.0f;
		tuning.m_suspensionCompression = 4.4f;
		tuning.m_suspensionDamping = 2.3f;
		tuning.m_frictionSlip = 1000.0f;
		tuning.m_suspensionStiffness = 20.0f;

		auto vehicleRaycaster = new btDefaultVehicleRaycaster(m_physicsWorld.GetWorld());
		m_vehicle = new btRaycastVehicle(tuning, rigidBody, vehicleRaycaster);
		m_vehicle->setCoordinateSystem(0, 1, 2);

		btVector3 wheelDirectionCS0(0, -1, 0);
		btVector3 wheelAxleCS(-1, 0, 0);
		btScalar suspensionRestLength = 0.6f;
		btScalar connectionHeight = 1.2f;

		btVector3 connectionPointCS0(1 - (0.3*wheelWidth), connectionHeight, 2 - wheelRadius);
		bool isFrontWheel = true;
		m_vehicle->addWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, isFrontWheel);
		connectionPointCS0 = btVector3(-1 + (0.3*wheelWidth), connectionHeight, 2 - wheelRadius);

		m_vehicle->addWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, isFrontWheel);
		connectionPointCS0 = btVector3(-1 + (0.3*wheelWidth), connectionHeight, -2 + wheelRadius);

		isFrontWheel = false;
		m_vehicle->addWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, isFrontWheel);
		connectionPointCS0 = btVector3(1 - (0.3*wheelWidth), connectionHeight, -2 + wheelRadius);
		m_vehicle->addWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, isFrontWheel);

		for (int i = 0; i < m_vehicle->getNumWheels(); ++i)
		{
			btWheelInfo& wheel = m_vehicle->getWheelInfo(i);
			wheel.m_suspensionStiffness = suspensionStiffness;
			wheel.m_wheelsDampingRelaxation = suspensionDamping;
			wheel.m_wheelsDampingCompression = suspensionCompression;
			wheel.m_frictionSlip = wheelFriction;
			wheel.m_rollInfluence = rollInfluence;
		}
		for (int i = 0; i < m_vehicle->getNumWheels(); ++i)
		{
			//m_vehicle->applyEngineForce(-0.1f, i);
			auto wheelInfo = m_vehicle->getWheelInfo(i);
			//printf("WheelInfo: %lf, %lf, %lf \n", wheelInfo.m_worldTransform.getOrigin().getY(), wheelInfo.m_chassisConnectionPointCS.getY(), wheelInfo.m_wheelsRadius);
		}
		m_physicsWorld.AddAction(m_vehicle);
	}*/

}

void PhysicsManager::CreateRigidBody(PhysicsDefs::IRigidBodyCreationData* RBCD, std::size_t hashID)
{
	float mass = 0, friction, rollingFriction;
	btRigidBody::btRigidBodyConstructionInfo* RBCI;
	btCollisionShape* collisionShape = NULL;
	btDefaultMotionState* motionState;
	btVector3 position, inertia(0.f,0.f,0.f);
	btQuaternion rotation;
	if (RBCD->GetShape() == PhysicsDefs::Box)
	{
		PhysicsDefs::BoxCreationData* boxSettings = dynamic_cast<PhysicsDefs::BoxCreationData*>(RBCD);
		collisionShape = new btBoxShape(btVector3(boxSettings->boxDimensions[0], boxSettings->boxDimensions[1], boxSettings->boxDimensions[2]));
	}
	else
	{
		PhysicsDefs::SphereCreationData* sphereSettings = dynamic_cast<PhysicsDefs::SphereCreationData*>(RBCD);
		collisionShape = new btSphereShape(sphereSettings->sphereRadius);
	}


	position = btVector3(RBCD->msPosition[0], RBCD->msPosition[1], RBCD->msPosition[2]);
	rotation = btQuaternion(RBCD->rotationAngles[1] * M_PI / 180, RBCD->rotationAngles[0] * M_PI / 180, RBCD->rotationAngles[2] * M_PI / 180);
	motionState = new btDefaultMotionState(btTransform(rotation, position));
	mass = RBCD->mass;
	if (mass > 0)
		collisionShape->calculateLocalInertia(mass, inertia);
	else
		mass = 0;

	RBCI = new btRigidBody::btRigidBodyConstructionInfo(mass, motionState, collisionShape, inertia);

	RBCI->m_friction = RBCD->friction;
	RBCI->m_rollingFriction = RBCD->rollingFriction;

	auto body = new RigidPhysBody();
	body->ConstructFromRBCI(*RBCI);

	m_collisionShapes.push_back(collisionShape);

	PhysicsComponent* component = new PhysicsComponent(m_physicsComponents.size(), hashID);

	component->SetBody(body);
	component->SetOwner(RBCD->owner);
	m_physicsWorld.AddBody(body);
	m_physicsComponents.push_back(component);

	m_RBCIMap[hashID] = RBCI;
}

void PhysicsManager::CreateCompoundBody(PhysicsDefs::CompoundCreationData* compData, std::size_t hashID)
{
	if (!compData || compData->rigidBodies.size() != compData->shapePositions.size())
		return;
	
	float mass = 0, friction, rollingFriction;
	btCompoundShape* compShape = new btCompoundShape();
	btCollisionShape* collShape;

	for (int i = 0; i < compData->rigidBodies.size(); ++i)
	{
		mass += compData->rigidBodies[i]->mass;
		if (compData->rigidBodies[i]->GetShape() == PhysicsDefs::Box)
		{
			PhysicsDefs::BoxCreationData* boxSettings = dynamic_cast<PhysicsDefs::BoxCreationData*>(compData->rigidBodies[i]);
			collShape = new btBoxShape(btVector3(boxSettings->boxDimensions[0], boxSettings->boxDimensions[1], boxSettings->boxDimensions[2]));
		}
		else
		{
			PhysicsDefs::SphereCreationData* sphereSettings = dynamic_cast<PhysicsDefs::SphereCreationData*>(compData->rigidBodies[i]);
			collShape = new btSphereShape(sphereSettings->sphereRadius);
		}
		compShape->addChildShape(compData->shapePositions[i], collShape);
	}

	btRigidBody::btRigidBodyConstructionInfo* RBCI;
	btDefaultMotionState* motionState;
	btVector3 position, inertia(0.f, 0.f, 0.f);
	btQuaternion rotation;

	position = btVector3(compData->msPosition[0], compData->msPosition[1], compData->msPosition[2]);
	rotation = btQuaternion(compData->rotationAngles[1] * M_PI / 180, compData->rotationAngles[0] * M_PI / 180, compData->rotationAngles[2] * M_PI / 180);
	motionState = new btDefaultMotionState(btTransform(rotation, position));

	if (mass > 0)
		compShape->calculateLocalInertia(mass, inertia);
	else
		mass = 0;

	RBCI = new btRigidBody::btRigidBodyConstructionInfo(mass, motionState, compShape, inertia);

	RBCI->m_friction = compData->friction;
	RBCI->m_rollingFriction = compData->rollingFriction;

	auto body = new RigidPhysBody();
	body->ConstructFromRBCI(*RBCI);

	m_collisionShapes.push_back(compShape);

	PhysicsComponent* component = new PhysicsComponent(m_physicsComponents.size(), hashID);

	component->SetBody(body);
	component->SetOwner(compData->owner);
	m_physicsWorld.AddBody(body);
	m_physicsComponents.push_back(component);

	m_RBCIMap[hashID] = RBCI;

}

void PhysicsManager::CreateConstraint(IEventData* data)
{
	EDCreateConstraint* constData = dynamic_cast<EDCreateConstraint*>(data);
	if (!constData)
		return;

	PhysicsDefs::ConstraintCreationData* settings = constData->GetData();

	RigidPhysBody* body1 = dynamic_cast<RigidPhysBody*>(settings->body1->GetPhysicsComponent()->GetBody());
	RigidPhysBody* body2 = dynamic_cast<RigidPhysBody*>(settings->body2->GetPhysicsComponent()->GetBody());

	auto rb1 = body1->m_btBody;
	auto rb2 = body2->m_btBody;

	// add some (arbitrary) data to build constraint frames
	btVector3 parentAxis(1.f, 0.f, 0.f);
	btVector3 childAxis(0.f, 0.f, 1.f);
	// build frame basis
	// 6DOF constraint uses Euler angles and to define limits
	// it is assumed that rotational order is :
	// Z - first, allowed limits are (-PI,PI);
	// new position of Y - second (allowed limits are (-PI/2 + epsilon, PI/2 - epsilon), where epsilon is a small positive number
	// used to prevent constraint from instability on poles;
	// new position of X, allowed limits are (-PI,PI);
	// So to simulate ODE Universal joint we should use parent axis as Z, child axis as Y and limit all other DOFs
	// Build the frame in world coordinate system first

	btVector3 zAxis = parentAxis.normalize();
	btVector3 yAxis = childAxis.normalize();
	btVector3 xAxis = yAxis.cross(zAxis); // we want right coordinate system
	btTransform frameInW;
	frameInW.setIdentity();
	frameInW.getBasis().setValue(
		xAxis[0], yAxis[0], zAxis[0],
		xAxis[1], yAxis[1], zAxis[1],
		xAxis[2], yAxis[2], zAxis[2]);
	frameInW.setOrigin(settings->anchor);

	// now get constraint frame in local coordinate systems
	btTransform frameInA = rb1->getCenterOfMassTransform().inverse() * frameInW;
	btTransform frameInB = rb2->getCenterOfMassTransform().inverse() * frameInW;

	btGeneric6DofConstraint* constraint = new btGeneric6DofConstraint(*rb1, *rb2, frameInA, frameInB, true);

	constraint->setAngularUpperLimit(settings->upperAngularLimit);
	constraint->setAngularLowerLimit(settings->lowerAngularLimit);
	constraint->setLinearUpperLimit(settings->upperLinearLimit);
	constraint->setLinearLowerLimit(settings->lowerLinearLimit);

	printf("Braking thres: %ld \n", constraint->getBreakingImpulseThreshold());

	constraint->setDbgDrawSize(btScalar(2.f));

	m_physicsWorld.AddConstraint(constraint, true);
}

PhysicsDefs::ICreationData* PhysicsManager::GetComponentConstructionData(unsigned int id)
{
	std::size_t rbciMapKey = m_physicsComponents[id]->GetRBCI_ID();

	return RBCIToPhyCompData(m_RBCIMap[rbciMapKey]);
}

void PhysicsManager::GetPhysCompCreationData(IEventData* data)
{
	EDGetPhysicsData* getPhysDataED = dynamic_cast<EDGetPhysicsData*>(data);
	if (!getPhysDataED)
		return;

	auto rbciIt = m_preloadedInfo.find(getPhysDataED->GetName());
	if (rbciIt == m_preloadedInfo.end())
	{
		return;
	}

	auto rbci = rbciIt->second;
	
	getPhysDataED->SetData(RBCIToPhyCompData(rbci));
}

PhysicsDefs::ICreationData* PhysicsManager::RBCIToPhyCompData(btRigidBody::btRigidBodyConstructionInfo* rbci)
{

	PhysicsDefs::IRigidBodyCreationData* result; 

	if (rbci->m_collisionShape->getShapeType() == BOX_SHAPE_PROXYTYPE)
		result = CreateBoxCreationData(rbci);
	else
		result = CreateSphereCreationData(rbci);


	result->mass = rbci->m_mass;
	result->friction = rbci->m_friction;
	result->rollingFriction = rbci->m_rollingFriction;

	btTransform trans;
	rbci->m_motionState->getWorldTransform(trans);

	result->msPosition[0] = trans.getOrigin().getX();
	result->msPosition[1] = trans.getOrigin().getY();
	result->msPosition[2] = trans.getOrigin().getZ();

	btQuaternion quat = trans.getRotation();
	glm::quat glmQuat;
	glmQuat.x = quat.getX();
	glmQuat.y = quat.getY();
	glmQuat.z = quat.getZ();
	glmQuat.w = quat.getW();
	glm::vec3 rotationAxis = glm::eulerAngles(glmQuat);

	result->rotationAngles[0] = rotationAxis.x;
	result->rotationAngles[1] = rotationAxis.y;
	result->rotationAngles[2] = rotationAxis.z;

	return result;
}

std::size_t PhysicsManager::HashPhysCreationData(PhysicsDefs::ICreationData* data)
{
	std::size_t result;

	if (data->GetShape() == PhysicsDefs::PhysicsEntityTypes::Box)
	{
		PhysicsDefs::BoxCreationData* boxData = dynamic_cast<PhysicsDefs::BoxCreationData*>(data);
		result = (((std::hash<double>()(boxData->mass) ^ (std::hash<double>()(boxData->friction) >> 1) ^ ((std::hash<double>()(boxData->rollingFriction)) << 1)) >> 1) << 1);
		result ^= std::hash<int>()(data->GetShape());
		for (unsigned int i = 0; i < 3; ++i)
			result ^= std::hash<double>()(boxData->boxDimensions[i]);
	}
	else if (data->GetShape() == PhysicsDefs::PhysicsEntityTypes::Sphere)
	{
		PhysicsDefs::SphereCreationData* sphereData = dynamic_cast<PhysicsDefs::SphereCreationData*>(data);
		result = (((std::hash<double>()(sphereData->mass) ^ (std::hash<double>()(sphereData->friction) >> 1) ^ ((std::hash<double>()(sphereData->rollingFriction)) << 1)) >> 1) << 1);
		result ^= std::hash<int>()(sphereData->GetShape()); 
		result ^= std::hash<double>()(sphereData->sphereRadius);
	}
	else if (data->GetShape() == PhysicsDefs::PhysicsEntityTypes::Compound)
	{
		PhysicsDefs::CompoundCreationData* compData = dynamic_cast<PhysicsDefs::CompoundCreationData*>(data);
		result = (((std::hash<double>()(compData->mass) ^ (std::hash<double>()(compData->friction) >> 1) ^ ((std::hash<double>()(compData->rollingFriction)) << 1)) >> 1) << 1);
		result ^= std::hash<int>()(compData->GetShape());
		for (unsigned int i = 0; i < compData->rigidBodies.size(); ++i)
		{
			result ^= HashPhysCreationData(compData->rigidBodies[i]);
			result ^= (std::hash<double>()(compData->shapePositions[i].getOrigin()[0]) ^ std::hash<double>()(compData->shapePositions[i].getOrigin()[1])) << 1 ^ std::hash<double>()(compData->shapePositions[i].getOrigin()[2]);
			for (int j = 0; j < 3; ++j)
			{
				btVector3 row = compData->shapePositions[i].getBasis().getRow(j);
				result ^= ((std::hash<double>()(row[0]) << 1) ^ std::hash<double>()(row[1]) >> 1) ^ std::hash<double>()(row[2]);
			}
		}
	}

	return result;
}

btScalar PhysicsManager::CalculateBrakeForce(btWheelInfo& wheelInfo)
{
	btRigidBody* groundObject = 0;
	groundObject = (btRigidBody*)(wheelInfo.m_raycastInfo.m_groundObject);
	
	if (groundObject == NULL)
		return 0;

	btScalar wheelFriciton = wheelInfo.m_frictionSlip;
	btScalar groundFriction = groundObject->getFriction();

	return wheelFriciton*groundFriction;
}

btCollisionShape* PhysicsManager::CreateSphereCollisionShape(tinyxml2::XMLElement* objectNode)
{
	btCollisionShape* sphereShape = new btSphereShape(objectNode->FloatAttribute("radius"));

	return sphereShape;
}

btCollisionShape* PhysicsManager::CreateBoxCollisionShape(tinyxml2::XMLElement* objectNode)
{
	float x, y, z;

	objectNode->QueryFloatAttribute("x", &x);
	objectNode->QueryFloatAttribute("y", &y);
	objectNode->QueryFloatAttribute("z", &z);

	btCollisionShape* boxShape = new btBoxShape(btVector3(x,y,z));
	return boxShape;
}

btCollisionShape* PhysicsManager::CreateTriangleMeshCollisionShape(tinyxml2::XMLElement* objectNode)
{
	std::vector<btVector3> vertices;
	int triangleVertices[3];
	tinyxml2::XMLElement* pVertex = objectNode->FirstChildElement("Vertex");
	while (pVertex)
	{
		vertices.push_back(btVector3(pVertex->FloatAttribute("x"), pVertex->FloatAttribute("y"), pVertex->FloatAttribute("z")));
		pVertex = pVertex->NextSiblingElement();
	}
	
	tinyxml2::XMLElement* pTriangle = objectNode->FirstChildElement("Triangle");
	while (pTriangle)
	{
		triangleVertices[0] = pTriangle->IntAttribute("v1");
		triangleVertices[1] = pTriangle->IntAttribute("v2");
		triangleVertices[2] = pTriangle->IntAttribute("v3");
		
		m_testTriangleMesh.addTriangle(vertices[triangleVertices[0]], vertices[triangleVertices[1]], vertices[triangleVertices[2]]);
		pTriangle = pTriangle->NextSiblingElement();
	}

	btBvhTriangleMeshShape* triangleMeshShape = new btBvhTriangleMeshShape(&m_testTriangleMesh, false);

	return triangleMeshShape;
}

PhysicsDefs::BoxCreationData* PhysicsManager::CreateBoxCreationData(btRigidBody::btRigidBodyConstructionInfo* rbci)
{
	PhysicsDefs::BoxCreationData* result = new PhysicsDefs::BoxCreationData();

	result->boxDimensions[0] = ((btBoxShape*)(rbci->m_collisionShape))->getHalfExtentsWithoutMargin().getX();
	result->boxDimensions[1] = ((btBoxShape*)(rbci->m_collisionShape))->getHalfExtentsWithoutMargin().getY();
	result->boxDimensions[2] = ((btBoxShape*)(rbci->m_collisionShape))->getHalfExtentsWithoutMargin().getZ();

	return result;
}

PhysicsDefs::SphereCreationData* PhysicsManager::CreateSphereCreationData(btRigidBody::btRigidBodyConstructionInfo* rbci)
{
	PhysicsDefs::SphereCreationData* result = new PhysicsDefs::SphereCreationData();

	result->sphereRadius = ((btSphereShape*)(rbci->m_collisionShape))->getRadius();

	return result;
}