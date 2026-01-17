# Task Scheduler Engine (C++)

## Overview
A non-preemptive task scheduling engine implemented in C++ that simulates
CPU-style execution with support for task priorities, deadlines, and
dependency resolution using Directed Acyclic Graphs (DAG).

## Features
- Priority-based task scheduling
- Dependency handling via DAG and topological logic
- Deadline monitoring
- Time-based execution simulation
- Idle CPU handling
- Execution summary reporting

## Architecture
- Task: Represents a schedulable unit with priority, deadline, and execution time
- TaskGraph: Manages dependencies and validates DAG constraints
- Scheduler: Core engine that selects and executes tasks over simulated time

## Technologies Used
- C++17
- STL (priority_queue, unordered_map, vector, queue)
- Object-Oriented Design

## How to Run
1. Open the project in Visual Studio
2. Build the solution
3. Run the executable

## Sample Output
Time 0 -> Task T2 started
Time 2 -> Task T2 completed


## Future Enhancements
- JSON-based task input
- Preemptive scheduling
- Multithreaded execution
- Gantt chart visualization