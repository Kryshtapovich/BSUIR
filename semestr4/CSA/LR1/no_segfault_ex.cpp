#include <iostream>
int main() {
    int a[5] = {1, 2, 3, 4, 5};
    unsigned total = 0;
    for (int j = 0;j < sizeof(a)/sizeof(int) ; j++) {
        total += a[j];
    }
    std::cout << "sum of array is " << total << std::endl;
}