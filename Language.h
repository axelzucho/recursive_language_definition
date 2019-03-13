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

// Class where the language is going to be stored and manipulated.
class Language {
private:
    // Number of recursive steps to apply the rules to generate the language.
    int number_of_steps;

    // Vector containing all rules in the language generation.
    vector<RecursiveStepRule> recursive_steps;

    // Set containing all languages generated.
    set<string> language_generated;

    // Vector containing all new additions in the last recursive step.
    vector<string> new_additions;

public:
    // Constructor: Parses the text in the file into rules, number of steps and baseline.
    explicit Language(const string& path);

    // Executes one recursive step.
    void recursive_step();

    // Executes all recursive steps in the language.
    void all_steps();

    // Prints the new strings generated in the step.
    void print_step(int step);
};


#endif //RECURSIVE_LANGUAGES_LANGUAGE_H
