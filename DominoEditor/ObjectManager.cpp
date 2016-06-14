#include "ObjectManager.h"
#include "EDCreateObject.h"
#include "EDCreatePhysComp.h"
#include "EDCreateRenderComp.h"
#include "EventManager.h"
#include "GameDefs.h"

#include <functional>

ObjectManager::~ObjectManager()
{
	Clear();
}

void ObjectManager::Init()
{
	EventManager::GetInstance()->AddEventListener(EventDefs::CREATE_OBJECT, std::bind(&ObjectManager::CreateObject, this, std::placeholders::_1));
}

void ObjectManager::Step()
{

}

void ObjectManager::CreateObject(IEventData* data)
{
	EDCreateObject* objData = dynamic_cast<EDCreateObject*>(data); 
	if (!objData)
		return;

	bool isSync = objData->GetIsSynchronous();

	Object* newObject = new Object(objData->GetData()->name, m_objects.size());
	if (newObject->GetName().compare("main") == 0)
		m_mainObject = newObject;
	objData->GetData()->physCompData->owner = newObject;
	objData->GetData()->renderCompData->owner = newObject;
	EDCreatePhysComp* physEventData = new EDCreatePhysComp(objData->GetData()->physCompData);
	EDCreateRenderComp* renderEventData = new EDCreateRenderComp(objData->GetData()->renderCompData);
	
	EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_PHYSICS_COMPONENT, physEventData, isSync);
	EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_RENDER_COMPONENT, renderEventData, isSync);
	if (isSync)
		objData->GetData()->createdObject = newObject;

	m_objects.push_back(newObject);
}

void ObjectManager::Clear()
{
	for (unsigned int i = 0; i < m_objects.size(); ++i)
		delete m_objects[i];

	m_objects.clear();
}

