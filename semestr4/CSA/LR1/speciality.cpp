#include <iostream>

/* Изменяйте только эти 4 переменные */
constexpr int V0 = -1;
constexpr int V1 = 8;
constexpr int V2 = -1;
constexpr int V3 = -1;
//Минмальное количество различных значений равно 2

/*
 * Точка входа с++ программы. Что передается через аргументы?
 * Аргументы командной строки: argc - количество, argv - параметры 
 */
int main(int argc, char** argv) {
    /* 
     * Вывод сообщения на консоль
     * 
     */
    std::cout << "Специальности ФКСИС" << std::endl;
    std::cout << "===================" << std::endl;

    /* for loop */
    for (int a = 0; a < V0 + V2; a++)
    {
        std::cout << "Самая ";
    }
    std::cout << "Лучшая специальность:" << std::endl;

    /* switch statement */
    switch (V1 + V2 + V3)
    {
    case 0:
        std::cout << "Конечно же ";
    case 1:
        std::cout << "Вычислительные машины, системы и сети";
        break;
    case 2:
        std::cout << "Информатика и технологии программирования и ";
    case 3:
        std::cout << "Программное обеспечение информационных технологий";
        break;
    case 4:
        std::cout << "Электронные вычислительные средства";
        break;
    case 5:
        std::cout << "Информатика и технологии программирования";
        break;
    case 6:
        std::cout << "Только ";
    case 7:
        std::cout << "Информатика и технологии программирования";
        break;
    case 8:
        std::cout << "Программное обеспечение информационных технологий";
        break;
    case 9:
        std::cout << "Вычислительные машины, системы и сети";
        break;
    case 10:
        std::cout << "Вычислительные машины, системы и сети и ";
    case 11:
        std::cout << "Программное обеспечение информационных технологий";
        break;
    case 12:
        std::cout << "Информатика и технологии программирования";
    default:
        std::cout << "Я не знаю, я кошу от армии";
    }
    std::cout << std::endl;

    /* ternary operator */
    const std::string s = (!V3 || V3 == 6) ? "МТЗ" : "БАТЭ";

    /* if statement */
    if (V2 + V3 < 0) {
	std::cout << s << " чемпион!" << std::endl;
    } else {
	std::cout << "Вперед " << s << '!' << std::endl;
    }

    return 0;
}
