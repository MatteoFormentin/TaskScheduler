#include "Arduino.h"
#include "TaskScheduler.h"
#include "Task.h"

TaskScheduler::TaskScheduler(int initial_size = 2)
{
    task_array = new Task *[initial_size]; //* needed because the array cell is a pointer to Task object (without * every cell would be an object, which is nosense)
    task_array_lenght = initial_size;
    task_counter = 0;
}

//Return number of active task
int TaskScheduler::addNewTask(String id, void (*callbackTask)(), int interval_millis = 0) //if zero task will run at every loop cycle
{
    //Expand (if needed) task array
    if (task_array[task_array_lenght - 1] != NULL)
    {
        Task **temp = new Task *[task_array_lenght + 2];
        for (int i = 0; i < task_array_lenght; i++)
        {
            temp[i] = task_array[i];
        }
        delete[] task_array;
        task_array_lenght = task_array_lenght + 2;
        task_array = temp;
    }

    task_array[task_counter] = new Task(id, callbackTask, interval_millis);
    task_counter++;
    return task_counter;
}

boolean TaskScheduler::removeTask(String id)
{
    int task_deleted_counter = 0;
    for (int i = 0; i < task_array_lenght; i++)
    {
        if (task_array[i]->getId() == id)
        {
            delete task_array[i];
            task_array[i] = NULL;
            task_deleted_counter++;
        }
    }

    if (task_deleted_counter > 0)
    {
        //Compact Array
        Task **temp = new Task *[task_array_lenght - task_deleted_counter];
        int j = 0;
        for (int i = 0; i < task_array_lenght; i++)
        {
            if (task_array[i] != NULL)
            {
                temp[j] = task_array[i];
                j++;
            }
        }
        delete[] task_array;
        task_array = temp;
    }
    task_array_lenght--;
    task_counter--;
    return true;
}

void TaskScheduler::runSchedule()
{
    for (int i = 0; i < task_counter; i++)
    {
        uint32_t time = millis();
        if (time - task_array[i]->getLastMillis() >= task_array[i]->getInterval())
        {
            task_array[i]->runCallback();
            task_array[i]->setLastMillis(time);
        }
    }
}