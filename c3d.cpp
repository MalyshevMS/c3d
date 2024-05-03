#include "c3d.hh"
#include <iostream>

using namespace std;
using namespace c3d;

int main() {
    Volume vol(10, 10, 10);
    Box box1(vol, 0, 0, 0, 1, 1, 1, "box1");
    box1.display();
}