#ifndef TASK_h
#define TASK_h

#include "Arduino.h"

class Task
{
  private:
    void (*callbackTask)();
    uint32_t interval_millis;
    uint32_t last_millis;
    String id;

  public:
    Task(String id, void (*callbackTask)(), int interval_millis);
    uint32_t getInterval();
    uint32_t getLastMillis();
    String getId();

    void setInterval(uint32_t interval_millis);
    void setLastMillis(uint32_t last_millis);
    void runCallback();
};

#endif