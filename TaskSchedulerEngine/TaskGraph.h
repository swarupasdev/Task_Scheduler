#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class TaskGraph {
private:
    std::unordered_map<std::string, std::vector<std::string>> adjList;
    std::unordered_map<std::string, int> indegree;

public:
    void addTask(const std::string& taskId);
    void addDependency(const std::string& from, const std::string& to);
    bool hasCycle() const;

    std::vector<std::string> topologicalSort() const;

    const std::unordered_map<std::string, std::vector<std::string>>& getAdjList() const;
    const std::unordered_map<std::string, int>& getIndegreeMap() const;
};
