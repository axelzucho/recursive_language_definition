//
// Created by axelzucho on 8/03/19.
//

#ifndef RECURSIVE_LANGUAGES_LANGUAGE_H
#define RECURSIVE_LANGUAGES_LANGUAGE_H

#include <string>
#include <vector>
#include <set>
#include "RecursiveStepRule.h"

using namespace std;

class Language {
private:
    int number_of_steps;
    vector<RecursiveStepRule> recursive_steps;
    set<string> language_generated;
    vector<string> new_additions;

public:
    explicit Language(const string& path);
    void recursive_step();
    void all_steps();
    void print_step(int step);
};


#endif //RECURSIVE_LANGUAGES_LANGUAGE_H
