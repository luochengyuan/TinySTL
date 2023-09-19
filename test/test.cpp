#include"../STL/allocator.h"
#include<iostream>
#include"../mySTL/allocator.h"
using namespace MYSTL;

int main(){
    allocator<int> allocator;
    auto p=allocator.allocate();
    allocator.construct(p,3);
    allocator.destroy(p);
    std::cout<<*p;
    allocator.deallocate(p);
    return 0;
}