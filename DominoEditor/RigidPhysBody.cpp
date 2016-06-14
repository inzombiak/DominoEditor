#include "RigidPhysBody.h"

#include "Object.h"

RigidPhysBody::RigidPhysBody()
{

}

RigidPhysBody::~RigidPhysBody()
{

}

void RigidPhysBody::SetOwner(Object* owner)
{
	if (!m_btBody)
		return;

	m_btBody->setUserPointer(owner);
}

void RigidPhysBody::ApplyForce(btVector3& hitPoint, btVector3& direction, float amount)
{
	m_btBody->activate(true);
	direction = direction.normalize();

	btVector3 centerOfMass = m_btBody->getCenterOfMassPosition();
	btVector3 force = direction * amount;
	//btVector3 btHitPoint = btVector3(0, 2.4, -0.75);

	m_btBody->applyImpulse(force, hitPoint - centerOfMass);
}

btTransform RigidPhysBody::GetTransformMatrix()
{
	btTransform result;

	m_btBody->getMotionState()->getWorldTransform(result);

	return result;
}

void RigidPhysBody::ConstructFromRBCI(const btRigidBody::btRigidBodyConstructionInfo& RBCI)
{
	m_btBody = new btRigidBody(RBCI);
	//m_btBody->sl
	m_btBody->setSleepingThresholds(5,m_btBody->getAngularSleepingThreshold());
	m_btBody->setDeactivationTime(0.1);
	m_btBody->setDamping(0.1, 0.1);
	float test = m_btBody->getLinearDamping();
	printf("Sleep tresh: %lf", test);
}

btTransform RigidPhysBody::GetCenterOfMass()
{
	return m_btBody->getCenterOfMassTransform();
}