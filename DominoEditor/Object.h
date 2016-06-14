#pragma once

#include "glm\glm.hpp"
#include "glm\gtc\quaternion.hpp"
#include <string>

class RenderComponent;
class PhysicsComponent;

class Object
{
public:
	Object(std::string name, unsigned int id) : m_name(name), m_id(id)
	{
	};
	void SetRenderComponent(RenderComponent* renderComp);
	void SetPhysicsComponent(PhysicsComponent* physicsComp);
	PhysicsComponent* GetPhysicsComponent()
	{
		return m_physicsComponent;
	}
	void SetPosition(glm::vec3& pos);
	glm::vec3 GetPosition() const;

	void SetRotation(glm::quat& rotation);
	glm::quat GetRotation() const;

	void SetOpenGLMatrix(glm::mat4& openGLMAt);
	glm::mat4 GetOpenGLMatrix() const;
	std::string GetName() const
	{
		return m_name;
	}
	int GetID() const
	{
		return m_id;
	}

private:
	unsigned int m_id;
	glm::vec3 m_position;
	glm::quat m_rotation;
	glm::mat4 m_openGLMat;
	std::string m_name;
	RenderComponent* m_renderComponent;
	PhysicsComponent* m_physicsComponent;
};

