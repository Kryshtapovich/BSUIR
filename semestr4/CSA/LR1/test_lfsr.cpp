#include <iostream>
#include <string>
#include <cstring>
#include "lfsr.h"

int main() {
    int8_t *numbers = (int8_t*) malloc(sizeof(int8_t) * 65535);
    if (numbers == NULL) {
        std::cout << "Не получилось аллоцировать память!" << std::endl;
        exit(1);
    }

    memset(numbers, 0, sizeof(int8_t) * 65535);
    uint16_t reg = 0x1;
    uint32_t count = 0;
    int i;

    do {
        count++;
        numbers[reg] = 1;
        if (count < 24) {
            std::cout << "Мое число: " << reg << std::endl;
        } else if (count == 24) {
            std::cout << " ... и так далее, и тому подобное ... \n";
        }
        for (i = 0; i < 32; i++)
            lfsr_calculate(&reg);
    } while (numbers[reg] != 1);

    std::cout << "Получилось " << count << " чисел до выхода\n"; 

    if (count == 65535) {
        std::cout << "Поздравляем! Оно работает!\n";
    } else {
        std::cout << "Что-то не так?\n";
    }

    free(numbers);

    return 0;
}