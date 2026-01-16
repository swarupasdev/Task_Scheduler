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
    int completedTasks = 0;
    int totalTasks = static_cast<int>(tasks.size());

    auto indeg = graph.getIndegreeMap();
    auto adj = graph.getAdjList();

    // Initialize ready queue
    for (auto& pair : tasks) {
        if (indeg[pair.first] == 0) {
            pair.second->setState(TaskState::READY);
            readyQueue.push(pair.second);
        }
    }

    while (completedTasks < totalTasks) {

        // IDLE CPU HANDLING
        if (readyQueue.empty()) {
            std::cout << "Time " << currentTime << " -> CPU Idle\n";
            currentTime++;
            continue;
        }

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
        completedTasks++;

        if (currentTime > task->getDeadline()) {
            task->markDeadlineMissed();
            std::cout << "Task " << task->getId()
                << " MISSED deadline\n";
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

    // FINAL SUMMARY
    std::cout << "\nExecution Summary:\n";
    for (const auto& pair : tasks) {
        auto t = pair.second;
        std::cout << "Task " << t->getId()
            << " | Start: " << t->getStartTime()
            << " | End: " << t->getEndTime();

        if (t->hasMissedDeadline()) {
            std::cout << " | Deadline Missed";
        }
        std::cout << "\n";
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
