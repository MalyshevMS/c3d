#include <iostream>
#include "c3d.hh"

using namespace std;

int main() {
    int i = 0;
    int y = 0;
    int size_y = 1;

    if (in_range(i, range_raw(y, (size_y + y)), ((size_y + y) - y)) == true) {
        print <string> ("true");
    } else {
        print <string> ("false");
    }
}