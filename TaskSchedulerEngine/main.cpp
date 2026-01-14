#include <iostream>
#include <memory>
#include "Scheduler.h"

int main() {
    Scheduler scheduler;

    scheduler.addTask(std::make_shared<Task>("T1", 3, 10, 4));
    scheduler.addTask(std::make_shared<Task>("T2", 5, 8, 2));
    scheduler.addTask(std::make_shared<Task>("T3", 1, 12, 1));
    scheduler.addTask(std::make_shared<Task>("T4", 4, 6, 3));

    scheduler.addDependency("T1", "T3");
    scheduler.addDependency("T2", "T3");
    scheduler.addDependency("T3", "T4");

    auto order = scheduler.getScheduledOrder();

    std::cout << "Priority-Aware Execution Order:\n";
    for (const auto& id : order) {
        std::cout << id << " ";
    }
    std::cout << std::endl;

    return 0;
}
