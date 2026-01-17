#pragma once
#include <string>

enum class TaskState {
    READY,
    WAITING,
    RUNNING,
    COMPLETED
};

inline const char* toString(TaskState state) {
    switch (state) {
    case TaskState::READY: return "READY";
    case TaskState::WAITING: return "WAITING";
    case TaskState::RUNNING: return "RUNNING";
    case TaskState::COMPLETED: return "COMPLETED";
    default: return "UNKNOWN";
    }
}

class Task {
private:
    std::string id;
    int priority;
    int deadline;
    int executionTime;
    
    TaskState state;

    int startTime;
    int endTime;

    bool deadlineMissed;

public:
    Task(const std::string& taskId, int pr, int dl, int execTime);

    const std::string& getId() const;
    int getPriority() const;
    int getDeadline() const;
    int getExecutionTime() const;
    TaskState getState() const;

    void setState(TaskState newState);

    int getStartTime() const;
    int getEndTime() const;

    void setStartTime(int time);
    void setEndTime(int time);

    bool hasMissedDeadline() const;
    void markDeadlineMissed();

};
