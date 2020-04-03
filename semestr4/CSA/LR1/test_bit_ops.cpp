#include <iostream>
#include "bit_ops.h"

inline void print_result(unsigned a, unsigned expected) {
    if(a!=expected) {
	std::cout << "Ожидается 0x" << expected << std::endl;
    } else {
	std::cout << "Правильно" << std::endl;
    }
}

void test_get_bit(unsigned x,
        unsigned n,
        unsigned expected) {
    unsigned a = get_bit(x, n);
    std::cout << "get_bit(0x" << std::hex << x << ", " << std::dec
             << n << std::hex << "): 0x" << a << ", ";
    print_result(a, expected);
}
void test_set_bit(unsigned x,
        unsigned n,
        unsigned v,
        unsigned expected) {
    unsigned o = x;
    set_bit(&x, n, v);
    std::cout << "set_bit(0x" << std::hex << o << ", " << std::dec
             << n << ", " << v << std::hex << "): 0x" << x << ", ";
    print_result(x, expected);
}
void test_flip_bit(unsigned x,
        unsigned n,
        unsigned expected) {
    unsigned o = x;
    flip_bit(&x, n);
    std::cout << "flip_bit(0x" << std::hex << o << ", " << std::dec
             << n << std::hex << "): 0x" << x << ", ";
    print_result(x, expected);
}
int main(int argc, const char * argv[]) {
    std::cout << std::hex;
    std::cout << "\nТестирование get_bit()\n\n";
    test_get_bit(0b1001110,0,0);
    test_get_bit(0b1001110,1,1);
    test_get_bit(0b1001110,5,0);
    test_get_bit(0b11011,3,1);
    test_get_bit(0b11011,2,0);
    test_get_bit(0b11011,9,0);
    test_get_bit(0b1001110,0,0);
    std::cout << "\nТестирование set_bit()\n\n";
    test_set_bit(0b1001110,2,0,0b1001010);
    test_set_bit(0b1101101,0,0,0b1101100);
    test_set_bit(0b1001110,2,1,0b1001110);
    test_set_bit(0b1101101,0,1,0b1101101);
    test_set_bit(0b1001110,9,0,0b1001110);
    test_set_bit(0b1101101,4,0,0b1101101);
    test_set_bit(0b1001110,9,1,0b1001001110);
    test_set_bit(0b1101101,7,1,0b11101101);
    std::cout << "\nТестирование flip_bit()\n\n";
    test_flip_bit(0b1001110,0,0b1001111);
    test_flip_bit(0b1001110,1,0b1001100);
    test_flip_bit(0b1001110,2,0b1001010);
    test_flip_bit(0b1001110,5,0b1101110);
    test_flip_bit(0b1001110,9,0b1001001110);
    std::cout << std::endl;
    return 0;
}