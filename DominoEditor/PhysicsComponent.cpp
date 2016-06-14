#include "PhysicsComponent.h"
#include "Object.h"

#include "IPhysicsBody.h"

void PhysicsComponent::SetOwner(Object* owner)
{
	m_owner = owner;
	owner->SetPhysicsComponent(this);
	m_body->SetOwner(m_owner);
}
PhysicsComponent::~PhysicsComponent()
{

}

void PhysicsComponent::SetBody(IPhysicsBody* body)
{
	m_body = body;
}
void PhysicsComponent::ApplyForce(glm::vec3& hitPoint, glm::vec3& direction, float amount)
{
	if (!m_body)
		return;
	
	m_body->ApplyForce(btVector3(hitPoint.x, hitPoint.y, hitPoint.z), btVector3(direction.x, direction.y, direction.z), amount);
}

void PhysicsComponent::Update()
{
	/*
	WE CAN USE getOpenGLMatrix to get the full model matrix
	*/
	if (!m_owner)
		return;

	btTransform trans = m_body->GetTransformMatrix();

	//glm::vec3 pos((float)trans.getOrigin().getX(), (float)trans.getOrigin().getY(), (float) trans.getOrigin().getZ());
	//m_owner->SetPosition(pos);

	//btQuaternion rotation = trans.getRotation();
	//glm::quat rotationQuat(rotation.getW(), rotation.getX(), rotation.getY(), rotation.getZ());
	//m_owner->SetRotation(rotationQuat);

	glm::mat4 glMat;

	trans.getOpenGLMatrix(glm::value_ptr(glMat));
	m_owner->SetOpenGLMatrix(glMat);
}

const char* PhysicsComponent::COMPONENT_NAME = "PHYSICS_COMPONENT";