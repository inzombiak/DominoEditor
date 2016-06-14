#pragma once

#include "glm\glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "IComponent.h"

class btRigidBody;

class Object;
class IPhysicsBody;
class PhysicsComponent : public IComponent
{
public:
	PhysicsComponent(unsigned int id, std::size_t RBCIID) : m_RBCIMapID(RBCIID)
	{
		m_owner = 0;
		m_body = 0;
		m_id = id;
	}
	~PhysicsComponent();

	void SetBody(IPhysicsBody* body);
	IPhysicsBody* GetBody() const
	{
		return m_body;
	}
	const std::size_t GetRBCI_ID()
	{
		return m_RBCIMapID;
	}

	void SetOwner(Object* owner);
	const char* GetName() override
	{
		return COMPONENT_NAME;
	}
	void ApplyForce(glm::vec3& hitPoint, glm::vec3& direction, float amount);

	void Update();

private:
	const static char* COMPONENT_NAME;

	std::size_t m_RBCIMapID;
	IPhysicsBody* m_body;
};

