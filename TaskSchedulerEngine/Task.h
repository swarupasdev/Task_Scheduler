#pragma once
#include <string>

enum class TaskState {
    READY,
    WAITING,
    RUNNING,
    COMPLETED
};

class Task {
private:
    std::string id;
    int priority;
    int deadline;
    int executionTime;
    TaskState state;

public:
    Task(const std::string& taskId, int pr, int dl, int execTime);

    const std::string& getId() const;
    int getPriority() const;
    int getDeadline() const;
    int getExecutionTime() const;
    TaskState getState() const;

    void setState(TaskState newState);
};
