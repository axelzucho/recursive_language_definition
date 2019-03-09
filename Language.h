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
    vector<RecursiveStepRule> recursive_steps;
    set<string> language_generated;

public:
    explicit Language(const string& path);
    void recursive_step();
};


#endif //RECURSIVE_LANGUAGES_LANGUAGE_H
