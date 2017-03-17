#pragma once
#include "IEventData.h"

#include <glm\glm.hpp>
#include <vector>

class EDCreateRenderComp :
	public IEventData
{
public:
	EDCreateRenderComp(GameDefs::RenderCompCreationData* data)
	{ 
		m_renderCompCreationData = data;
		m_eventType = EventDefs::CREATE_RENDER_COMPONENT;
	};

	GameDefs::RenderCompCreationData* GetData()
	{
		return m_renderCompCreationData;
	}

	~EDCreateRenderComp()
	{
		delete m_renderCompCreationData;
		m_renderCompCreationData = 0;
	}

private:
	GameDefs::RenderCompCreationData* m_renderCompCreationData = 0;
};

