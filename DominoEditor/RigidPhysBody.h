#pragma once
#include "IPhysicsBody.h"
#include "PhysicsDefs.h"

class PhysicsWorld;
class PhysicsManager;
class RigidPhysBody :
	public IPhysicsBody
{
	friend class PhysicsWorld;
	friend class PhysicsManager;
public:
	RigidPhysBody();
	~RigidPhysBody();
	
	void SetOwner(Object* owner) override;
	void ApplyForce(btVector3& hitPoint, btVector3& direction, float amount)  override;
	bool IsActive() override
	{
		return m_btBody->isActive();
	}
	btTransform GetTransformMatrix()  override;
	btTransform GetCenterOfMass() override;
	void ConstructFromRBCI(const btRigidBody::btRigidBodyConstructionInfo& RBCI) override;

protected:
	btRigidBody* m_btBody;
};

