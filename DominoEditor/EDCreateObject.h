#pragma once
#include "IEventData.h"
#include "PhysicsDefs.h"
#include "GameDefs.h"

struct ObjectCreationData
{
	int nameID;
	std::string name;
	GameDefs::RenderCompCreationData* renderCompData = new GameDefs::RenderCompCreationData();
	PhysicsDefs::ICreationData* physCompData = 0;
	Object* createdObject = 0;
};

class EDCreateObject :
	public IEventData
{
public:
	EDCreateObject(ObjectCreationData* data) 
	{ 
		m_objCreationData = data;
		m_eventType = EventDefs::CREATE_OBJECT;
	}

	~EDCreateObject()
	{
		delete m_objCreationData;
		m_objCreationData = 0;
	}

	ObjectCreationData* GetData()
	{
		return m_objCreationData;
	}

private:
	ObjectCreationData* m_objCreationData;
};

