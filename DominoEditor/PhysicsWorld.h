#pragma once

#include <vector>

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

#include "BulletDynamics\Dynamics\btRigidBody.h"
#include "RigidPhysBody.h"
class PhysicsWorld
{
public:
	~PhysicsWorld();
	void Init();
	void Clear();
	void AddBody(IPhysicsBody* body);
	void RemoveBody(IPhysicsBody* body);
	void AddAction(btActionInterface* action);
	void AddConstraint(btTypedConstraint* constraint, bool collisionBetweenLinks);
	void Step(float dt, int maxSubStep, double timeStep);
	void SetDebugDraw(btIDebugDraw* btDD);
	void Grab(btVector3& start, btVector3& end, btCollisionWorld::ClosestRayResultCallback& result);
	btDiscreteDynamicsWorld* GetWorld() const
	{
		return m_dynamicsWorld;
	}

private:
	btBroadphaseInterface* m_broadphase;
	btDefaultCollisionConfiguration* m_collisionConfig;
	btCollisionDispatcher* m_collisionDispatcher;
	btSequentialImpulseConstraintSolver* m_solver;
	btDiscreteDynamicsWorld* m_dynamicsWorld;

	std::vector<btRigidBody*> m_rigidBodies;
	std::vector<btActionInterface*> m_actionInterfaces;
};

