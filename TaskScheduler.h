#ifndef TASKSCHEDULE_h
#define TASKSCHEDULE_h

#include "Arduino.h"
#include "Task.h"

class TaskScheduler
{
private:
  Task **task_array; //It's a pointer to an array of pointer (equals to java Task[] array)
  int task_counter;
  int task_array_lenght;

public:
  TaskScheduler(int initial_size = 2);
  int addNewTask(String id, void (*callbackTask)(), int interval_millis);
  bool removeTask(String id);
  void runSchedule();
};

#endif