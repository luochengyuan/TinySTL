#include<iostream>
#include"../allocator.h"
using namespace MYSTL;
int main(){
    allocator<int> allocator;
    auto p=allocator.allocate();
    allocator.construct(p,6);
    allocator.deallocate(p);
    allocator.destroy(p);
    return 0;
}