#include "Object.h"

#include "RenderComponent.h"
#include "PhysicsComponent.h"

void Object::SetRenderComponent(RenderComponent* renderComp)
{
	if (!renderComp)
		return;

	m_renderComponent = renderComp;
}

void Object::SetPhysicsComponent(PhysicsComponent* physicsComp)
{
	if (!physicsComp)
		return;

	m_physicsComponent = physicsComp;
}

void Object::SetPosition(glm::vec3& pos)
{
	m_position = pos;
}
glm::vec3 Object::GetPosition() const
{
	return m_position;
}

void Object::SetRotation(glm::quat& rot)
{
	m_rotation = rot;
}
glm::quat Object::GetRotation() const
{
	return m_rotation;
}

void Object::SetOpenGLMatrix(glm::mat4& openGLMatrix)
{
	m_openGLMat = openGLMatrix;
}
glm::mat4 Object::GetOpenGLMatrix() const
{
	return m_openGLMat;
}

