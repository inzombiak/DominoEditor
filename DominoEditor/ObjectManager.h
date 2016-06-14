#pragma once

#include "Object.h"

#include "EDCreateObject.h"
#include <vector>

class PhysicsComponent;
class RenderComponent;
class EDCreateObject;

class ObjectManager
{
public:
	~ObjectManager();
	void Init();
	void Step();
	void Clear();
	void CreateObject(IEventData* data);
	Object* GetMain()
	{
		return m_mainObject;
	}
private:
	Object* m_mainObject;
	std::vector<Object*> m_objects;
};

