#include <iostream>
#include "TaskGraph.h"

int main() {
    TaskGraph graph;

    graph.addDependency("T1", "T2");
    graph.addDependency("T1", "T3");
    graph.addDependency("T2", "T4");
    graph.addDependency("T3", "T4");

    auto order = graph.topologicalSort();

    if (order.empty()) {
        std::cout << "Cycle detected. No valid execution order.\n";
        return 0;
    }

    std::cout << "Execution Order:\n";
    for (const auto& task : order) {
        std::cout << task << " ";
    }
    std::cout << std::endl;

    return 0;
}
