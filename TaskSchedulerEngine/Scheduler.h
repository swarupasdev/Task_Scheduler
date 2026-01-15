#pragma once
#include <unordered_map>
#include <queue>
#include <memory>
#include "Task.h"
#include "TaskGraph.h"

class Scheduler {
private:
    std::unordered_map<std::string, std::shared_ptr<Task>> tasks;
    TaskGraph graph;

    struct TaskCompare {
        bool operator()(const std::shared_ptr<Task>& a,
            const std::shared_ptr<Task>& b) const;
    };

    std::priority_queue<
        std::shared_ptr<Task>,
        std::vector<std::shared_ptr<Task>>,
        TaskCompare
    > readyQueue;

public:
    void addTask(const std::shared_ptr<Task>& task);
    void addDependency(const std::string& from, const std::string& to);

    std::vector<std::string> getScheduledOrder();
    void run();

};
