#include "ObjectManager.h"
#include "EDCreateObject.h"
#include "EDCreatePhysComp.h"
#include "EDCreateRenderComp.h"
#include "EventManager.h"
#include "GameDefs.h"

#include <functional>
#include <iostream>5

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
	printf("CREATING OBJ \n");
	EDCreateObject* objData = dynamic_cast<EDCreateObject*>(data); 
	if (objData == NULL)
		return;
	else
		printf("BAD EVENT \n");

	bool isSync = objData->GetIsSynchronous();

	Object* newObject = new Object(objData->GetData()->name, m_objects.size());
	if (newObject->GetName().compare("main") == 0)
		m_mainObject = newObject;
	std::cout << objData << std::endl;
	
	objData->GetData()->renderCompData->owner = newObject;
	if (objData->GetData()->physCompData)
	{
		objData->GetData()->physCompData->owner = newObject;
		EDCreatePhysComp* physEventData = new EDCreatePhysComp(objData->GetData()->physCompData);
		EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_PHYSICS_COMPONENT, physEventData, true);

	}
	else
		printf("10 CREATING OBJ: NO PHYS COMP \n");

	EDCreateRenderComp* renderEventData = new EDCreateRenderComp(objData->GetData()->renderCompData);
	
	
	EventManager::GetInstance()->QueueEvent(EventDefs::CREATE_RENDER_COMPONENT, renderEventData, true);
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

