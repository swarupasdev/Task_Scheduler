#include "TaskGraph.h"
#include <queue>

void TaskGraph::addTask(const std::string& taskId) {
    if (adjList.find(taskId) == adjList.end()) {
        adjList[taskId] = {};
        indegree[taskId] = 0;
    }
}

void TaskGraph::addDependency(const std::string& from, const std::string& to) {
    addTask(from);
    addTask(to);

    adjList[from].push_back(to);
    indegree[to]++;
}

bool TaskGraph::hasCycle() const {
    std::queue<std::string> q;
    std::unordered_map<std::string, int> indeg = indegree;

    for (const auto& pair : indeg) {
        if (pair.second == 0) {
            q.push(pair.first);
        }
    }

    int visitedCount = 0;

    while (!q.empty()) {
        std::string current = q.front();
        q.pop();
        visitedCount++;

        auto it = adjList.find(current);
        if (it != adjList.end()) {
            for (const std::string& neighbor : it->second) {
                indeg[neighbor]--;
                if (indeg[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
    }

    return visitedCount != adjList.size();
}

std::vector<std::string> TaskGraph::topologicalSort() const {
    std::queue<std::string> q;
    std::unordered_map<std::string, int> indeg = indegree;
    std::vector<std::string> order;

    for (const auto& pair : indeg) {
        if (pair.second == 0) {
            q.push(pair.first);
        }
    }

    while (!q.empty()) {
        std::string current = q.front();
        q.pop();
        order.push_back(current);

        auto it = adjList.find(current);
        if (it != adjList.end()) {
            for (const std::string& neighbor : it->second) {
                indeg[neighbor]--;
                if (indeg[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
    }

    if (order.size() != adjList.size()) {
        return {};  // cycle detected
    }

    return order;
}

const std::unordered_map<std::string, std::vector<std::string>>&
TaskGraph::getAdjList() const {
    return adjList;
}

const std::unordered_map<std::string, int>&
TaskGraph::getIndegreeMap() const {
    return indegree;
}
