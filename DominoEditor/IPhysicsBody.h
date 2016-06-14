#pragma once

#include "btBulletDynamicsCommon.h"

class Object;
class IPhysicsBody
{
public:
	IPhysicsBody();
	~IPhysicsBody();

	virtual void SetOwner(Object* owner) = 0;
	virtual void ApplyForce(btVector3& hitPoint, btVector3& direction, float amount) = 0;
	virtual bool IsActive() = 0;
	virtual btTransform GetTransformMatrix() = 0;
	virtual btTransform GetCenterOfMass() = 0;
	virtual void ConstructFromRBCI(const btRigidBody::btRigidBodyConstructionInfo& RBCI) = 0;
};

