#include <iostream>
#include "Task.h"

int main() {
    Task t1("T1", 5, 10, 3);

    std::cout << "Task ID: " << t1.getId() << std::endl;
    std::cout << "Priority: " << t1.getPriority() << std::endl;
    std::cout << "Deadline: " << t1.getDeadline() << std::endl;
    std::cout << "Execution Time: " << t1.getExecutionTime() << std::endl;

    return 0;
}
