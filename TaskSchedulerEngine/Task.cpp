#include "Task.h"
Task::Task(const std::string& taskId, int pr, int dl, int execTime)
    : id(taskId),
    priority(pr),
    deadline(dl),
    executionTime(execTime),
    state(TaskState::WAITING),
    startTime(-1),
    endTime(-1),
    deadlineMissed(false) {
}


const std::string& Task::getId() const {
    return id;
}

int Task::getPriority() const {
    return priority;
}

int Task::getDeadline() const {
    return deadline;
}

int Task::getExecutionTime() const {
    return executionTime;
}

TaskState Task::getState() const {
    return state;
}

void Task::setState(TaskState newState) {
    state = newState;
}

int Task::getStartTime() const {
    return startTime;
}

int Task::getEndTime() const {
    return endTime;
}

void Task::setStartTime(int time) {
    startTime = time;
}

void Task::setEndTime(int time) {
    endTime = time;
}

bool Task::hasMissedDeadline() const {
    return deadlineMissed;
}

void Task::markDeadlineMissed() {
    deadlineMissed = true;
}
