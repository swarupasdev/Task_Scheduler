#include "Scheduler.h"
#include <iostream>

bool Scheduler::TaskCompare::operator()(
    const std::shared_ptr<Task>& a,
    const std::shared_ptr<Task>& b) const {

    if (a->getPriority() == b->getPriority()) {
        return a->getDeadline() > b->getDeadline();
    }
    return a->getPriority() < b->getPriority();
}

void Scheduler::addTask(const std::shared_ptr<Task>& task) {
    tasks[task->getId()] = task;
    graph.addTask(task->getId());
}

void Scheduler::addDependency(const std::string& from, const std::string& to) {
    graph.addDependency(from, to);
}

void Scheduler::run() {
    int currentTime = 0;

    auto indeg = graph.getIndegreeMap();
    auto adj = graph.getAdjList();

    // Initialize ready queue
    for (auto& pair : tasks) {
        if (indeg[pair.first] == 0) {
            pair.second->setState(TaskState::READY);
            readyQueue.push(pair.second);
        }
    }

    while (!readyQueue.empty()) {
        auto task = readyQueue.top();
        readyQueue.pop();

        task->setState(TaskState::RUNNING);
        task->setStartTime(currentTime);

        std::cout << "Time " << currentTime
            << " -> Task " << task->getId()
            << " started\n";

        currentTime += task->getExecutionTime();

        task->setEndTime(currentTime);
        task->setState(TaskState::COMPLETED);

        if (currentTime > task->getDeadline()) {
            std::cout << "Task " << task->getId()
                << " missed its deadline\n";
        }

        std::cout << "Time " << currentTime
            << " -> Task " << task->getId()
            << " completed\n";

        for (const auto& neighbor : adj.at(task->getId())) {
            indeg[neighbor]--;
            if (indeg[neighbor] == 0) {
                auto nextTask = tasks[neighbor];
                nextTask->setState(TaskState::READY);
                readyQueue.push(nextTask);
            }
        }
    }
}

std::vector<std::string> Scheduler::getScheduledOrder() {
    std::vector<std::string> result;

    auto indeg = graph.getIndegreeMap();
    auto adj = graph.getAdjList();

    for (auto& pair : tasks) {
        if (indeg[pair.first] == 0) {
            pair.second->setState(TaskState::READY);
            readyQueue.push(pair.second);
        }
    }

    while (!readyQueue.empty()) {
        auto current = readyQueue.top();
        readyQueue.pop();

        current->setState(TaskState::RUNNING);
        result.push_back(current->getId());
        current->setState(TaskState::COMPLETED);

        for (const auto& neighbor : adj.at(current->getId())) {
            indeg[neighbor]--;
            if (indeg[neighbor] == 0) {
                auto nextTask = tasks[neighbor];
                nextTask->setState(TaskState::READY);
                readyQueue.push(nextTask);
            }
        }
    }

    return result;
}
