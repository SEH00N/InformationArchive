#include "pch.h"
#include "EventManager.h"
#include "Object.h"

void EventManager::Update()
{
	for (int i = 0; i < deadObjects.size(); i++)
		delete deadObjects[i];
	deadObjects.clear();

	for (int i = 0; i < events.size(); i++)
		Excute(events[i]);
	events.clear();
}

void EventManager::DeleteObject(Object* obj)
{
	Event evt;
	evt.eventType = EventType::DeleteObject;
	evt.objType = ObjectGroup::Monster;
	evt.obj = obj;

	events.push_back(evt);
}

void EventManager::Excute(const Event& evt)
{
	switch (evt.eventType)
	{
	case EventType::DeleteObject:
	{
		Object* deadObject = evt.obj;
		deadObject->SetDead();
		deadObjects.push_back(deadObject);
	}
		break;
	case EventType::CreateObject:
		break;
	case EventType::SceneChange:
		break;
	}
}
