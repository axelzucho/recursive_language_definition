#include <iostream>
#include "Language.h"

int main() {
    Language language("../example.txt");
    language.recursive_step();
    language.recursive_step();
    language.recursive_step();
    int a = 0;
    return 0;
}