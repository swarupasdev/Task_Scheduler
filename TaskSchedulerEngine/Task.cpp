#include "Task.h"

Task::Task(const std::string& taskId, int pr, int dl, int execTime)
    : id(taskId),
    priority(pr),
    deadline(dl),
    executionTime(execTime),
    state(TaskState::WAITING) {
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
