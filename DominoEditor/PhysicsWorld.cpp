#include "PhysicsWorld.h"
#include "btBulletDynamicsCommon.h"
#include "IPhysicsBody.h"

PhysicsWorld::~PhysicsWorld()
{
	Clear();
}

void PhysicsWorld::Init()
{
	m_broadphase = new btDbvtBroadphase();

	m_collisionConfig = new btDefaultCollisionConfiguration();
	m_collisionDispatcher = new btCollisionDispatcher(m_collisionConfig);

	//We also need a "solver". This is what causes the objects to interact properly, taking into account gravity, game logic supplied forces, collisions, and hinge constraints. 
	//It does a good job as long as you don't push it to extremes, and is one of the bottlenecks in any high performance simulation. 
	//There are parallel versions available for some threading models. 
	m_solver = new btSequentialImpulseConstraintSolver;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_collisionDispatcher, m_broadphase, m_solver, m_collisionConfig);
	m_dynamicsWorld->setGravity(btVector3(0, -400, 0));

}

void PhysicsWorld::Clear()
{
	int test = m_dynamicsWorld->getNumCollisionObjects();
	int i;
	for (i = m_dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
		if (!obj)
			break;
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{

			while (body->getNumConstraintRefs() > 0)
			{
				btTypedConstraint* constraint = body->getConstraintRef(0);
				if (!constraint)
					break;
				m_dynamicsWorld->removeConstraint(constraint);
				delete constraint;
			}
			delete body->getMotionState();
			body->setMotionState(0);
			m_dynamicsWorld->removeRigidBody(body);
		}
		else
		{
			m_dynamicsWorld->removeCollisionObject(obj);
		}
		delete obj;
	}

	m_rigidBodies.clear();

	delete m_dynamicsWorld;
	delete m_solver;
	delete m_collisionDispatcher;
	delete m_collisionConfig;
	delete m_broadphase;

	m_broadphase = 0;
	m_collisionConfig = 0;
	m_collisionDispatcher = 0;
	m_solver = 0;
	m_dynamicsWorld = 0;

}

void PhysicsWorld::Step(float dt, int maxSubStep, double timeStep)
{
	if (m_dynamicsWorld)
	{
		m_dynamicsWorld->stepSimulation(dt, maxSubStep, timeStep);
		m_dynamicsWorld->debugDrawWorld();
	}
}

void PhysicsWorld::AddBody(IPhysicsBody* body)
{
	RigidPhysBody* castBody = dynamic_cast<RigidPhysBody*>(body);
	if (!castBody)
		return;
	m_dynamicsWorld->addRigidBody(castBody->m_btBody);
	m_rigidBodies.push_back(castBody->m_btBody);

}

void PhysicsWorld::AddConstraint(btTypedConstraint* constraint, bool collisionBetweenLinks)
{
	if (!constraint)
		return;

	m_dynamicsWorld->addConstraint(constraint, collisionBetweenLinks);
}

void PhysicsWorld::RemoveBody(IPhysicsBody*  body)
{
	RigidPhysBody* castBody = dynamic_cast<RigidPhysBody*>(body);
	if (!castBody)
		return;
	m_dynamicsWorld->removeRigidBody(castBody->m_btBody);
}

void PhysicsWorld::AddAction(btActionInterface* action)
{
	m_dynamicsWorld->addVehicle(action);
	action->debugDraw(m_dynamicsWorld->getDebugDrawer());
}

void PhysicsWorld::SetDebugDraw(btIDebugDraw* btDD)
{
	if (!m_dynamicsWorld)
		return;

	m_dynamicsWorld->setDebugDrawer(btDD);
}

void PhysicsWorld::Grab(btVector3& start, btVector3& end, btCollisionWorld::ClosestRayResultCallback& result)
{
		m_dynamicsWorld->rayTest(start, end, result);
}