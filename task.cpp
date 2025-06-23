#include <iostream>
#include "header.hpp"

class Point {
    int x;
public:
    Point(int x, int y) : x(x) {
        std::cout << "point made: " << x << std::endl;
    }
    ~Point() {
        std::cout << "point deleted: " << x << std::endl;
    }
    void print() const {
        std::cout << "point: " << x << std::endl;
    }
};

int main() {
  // uniq
  
    //Создание
    auto point1 = make_uniq<Point>(1, 2);
    point1->print();
    
    // Перемещение
    auto point2 = std::move(point1);
    if (!point1.get()) {
        std::cout << "point1 empty" << std::endl;
    }
    point2->print();
  
// share
  
    auto spoint1 = make_share<Point>(3, 4);
    spoint1->print();
    std::cout << "Use count: " << spoint1.use_count() << std::endl;
    
    auto spoint2 = spoint1;
    spoint2->print();
    std::cout << "Use count: " << spoint1.use_count() << std::endl;
    
    auto spoint3 = std::move(sp2);
    spoint3->print();
    std::cout << "Use count (spoint1): " << spoint1.use_count() << std::endl;
    std::cout << "Use count (spoint2): " << (spoint2.get() ? spoint2.use_count() : 0) << std::endl;
    
    return 0;
    
}
