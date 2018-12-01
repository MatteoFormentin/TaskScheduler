#include "Task.h"
#include "Arduino.h"

Task::Task(String id, void (*callbackTask)(), int interval_millis)
{
    this->id = id;
    this->callbackTask = callbackTask;
    this->interval_millis = interval_millis;
}

uint32_t Task::getInterval()
{
    return interval_millis;
}

uint32_t Task::getLastMillis()
{
    return last_millis;
}

String Task::getId()
{
    return id;
}

void Task::setInterval(uint32_t interval_millis)
{
    this->interval_millis = interval_millis;
}

void Task::setLastMillis(uint32_t last_millis)
{
    this->last_millis = last_millis;
}

void Task::runCallback()
{
    callbackTask();
}