#include <iostream>

int main(int argc, char *argv[]) {
    int count = 0;
    int *p = &count;

    for (int i = 0; i < 10; i++) {
        (*p)++; // Что тут написано?
    }

    std::cout << "Спасибо за прохождение этого кода. Всего хорошего.";
    return 0;
}