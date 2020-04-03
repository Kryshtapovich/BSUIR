#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char *argv[]) {
    std::string name;
    std::cout  << "Представьтесь, пожалуйста\n";
    std::cin >> name;
    std::cout << "Привет, " << name << "\nПросто хотел поздороваться!\nХорошего тебе дня.\n";

    return 0;
}