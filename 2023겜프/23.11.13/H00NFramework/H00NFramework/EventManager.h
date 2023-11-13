#pragma once

class Object;

struct Event
{
	EventType eventType;
	ObjectGroup objType;
	Object* obj;
};

class EventManager
{
	SINGLE(EventManager)

public:
	void Update();
	void DeleteObject(Object* obj);

private:
	void Excute(const Event& evt);

private:
	std::vector<Object*> deadObjects;
	std::vector<Event> events;
};

