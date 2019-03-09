//
// Created by axelzucho on 9/03/19.
//

#ifndef RECURSIVE_LANGUAGES_RECURSIVESTEPRULE_H
#define RECURSIVE_LANGUAGES_RECURSIVESTEPRULE_H

#include <vector>
#include <string>
#include <set>

using namespace std;

class RecursiveStepRule {
private:
    vector<int> steps;
    vector<char> all_adding_chars;
    int string_num;
public:
    explicit RecursiveStepRule(string rule);
    void add_strings_to_language(set<string>& language_string);
    string execute_rule(vector<string> language_strings);
};


#endif //RECURSIVE_LANGUAGES_RECURSIVESTEPRULE_H
