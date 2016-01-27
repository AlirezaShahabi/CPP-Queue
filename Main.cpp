

#include "Queue.h"
#include <string>

// tester function

int main() {
    
    Queue<double> q1;
    
    q1.push(0).push(1).push(2.78);
    q1.push(3.14).push(10).push(1362).push(1984);
    q1.pop().push(26.401).pop().push(0.7);
    std::cout << "number of elements: " << q1.size() << std::endl;
    std::cout << "Is Queue empty? " << q1.is_empty() << std::endl;
    print(q1, std::cout);
    
    Queue<double> q2(q1);
    q2.pop().pop().push(9.86);
    std::cout << "number of elements: " << q2.size() << std::endl;
    std::cout << "Is Queue empty? " << q2.is_empty() << std::endl;
    print(q2, std::cout);
    q2.front() = 1000;
    q2.back() = -1000;
    print(q2, std::cout);
    
    Queue<double> q3;
    std::cout << "number of elements: " << q3.size() << std::endl;
    std::cout << "Is Queue empty? " << q3.is_empty() << std::endl;
    q3 = q1;
    std::cout << "number of elements: " << q3.size() << std::endl;
    std::cout << "Is Queue empty? " << q3.is_empty() << std::endl;
    print(q3, std::cout);
    
    while (!q3.is_empty()) {q3.pop();}
    std::cout << "number of elements: " << q3.size() << std::endl;
    std::cout << "Is Queue empty? " << q3.is_empty() << std::endl;
    print(q3, std::cout);
        
    return 0;
}
