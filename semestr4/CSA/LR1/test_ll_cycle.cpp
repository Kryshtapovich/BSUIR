#include <iostream>
#include "ll_cycle.h"

int main(void) {
    // DO NOT EDIT ANY OF THE FOLLOWING CODE

    int i;
    node nodes[25]; //enough to run our tests
    for(i=0; i < sizeof(nodes)/sizeof(node); i++) {
        nodes[i].next = 0;
        nodes[i].value = 0;
    }
    bool is_correct;

    nodes[0].next = &nodes[1];
    nodes[1].next = &nodes[2];
    nodes[2].next = &nodes[3];
    is_correct = !ll_has_cycle(&nodes[0]);
    std::cout << "Тест 1. Циклов нет. Резултат ll_has_cycle: " << std::boolalpha << ll_has_cycle(&nodes[0]) << std::endl;

    nodes[4].next = &nodes[5];
    nodes[5].next = &nodes[6];
    nodes[6].next = &nodes[7];
    nodes[7].next = &nodes[8];
    nodes[8].next = &nodes[9];
    nodes[9].next = &nodes[10];
    nodes[10].next = &nodes[4];
    is_correct = is_correct && ll_has_cycle(&nodes[4]);
    std::cout << "Тест 2. Циклы есть. Резултат ll_has_cycle: " << std::boolalpha << ll_has_cycle(&nodes[4]) << std::endl;

    nodes[11].next = &nodes[12];
    nodes[12].next = &nodes[13];
    nodes[13].next = &nodes[14];
    nodes[14].next = &nodes[15];
    nodes[15].next = &nodes[16];
    nodes[16].next = &nodes[17];
    nodes[17].next = &nodes[14];
    is_correct = is_correct && ll_has_cycle(&nodes[11]);
    std::cout << "Тест 3. Циклы есть. Резултат ll_has_cycle: " << std::boolalpha << ll_has_cycle(&nodes[11]) << std::endl;

    nodes[18].next = &nodes[18];
    is_correct = is_correct && ll_has_cycle(&nodes[18]);
    std::cout << "Тест 4. Циклы есть. Резултат ll_has_cycle: " << std::boolalpha << ll_has_cycle(&nodes[18]) << std::endl;

    nodes[19].next = &nodes[20];
    nodes[20].next = &nodes[21];
    nodes[21].next = &nodes[22];
    nodes[22].next = &nodes[23];
    is_correct = is_correct && !ll_has_cycle(&nodes[19]);
    std::cout << "Тест 5. Циклов нет. Резултат ll_has_cycle: " << std::boolalpha << ll_has_cycle(&nodes[19]) << std::endl;

    is_correct = is_correct && !ll_has_cycle(NULL);
    std::cout << "Тест 6. Циклов нет. Резултат ll_has_cycle: " << std::boolalpha << ll_has_cycle(NULL) << std::endl;

    std::cout << (is_correct ? "Успех\n": "Провал\n");
    return is_correct ? 0 : 1;
}