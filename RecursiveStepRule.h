//
// Created by axelzucho on 9/03/19.
//

#ifndef RECURSIVE_LANGUAGES_RECURSIVESTEPRULE_H
#define RECURSIVE_LANGUAGES_RECURSIVESTEPRULE_H

#include <vector>
#include <string>
#include <set>

#define NULL_STRING "#!NULL!#"

using namespace std;

class RecursiveStepRule {
private:
    // Stores all the steps in the rule. The steps are represented by ints as follows:
    // a) positive int: Indicates the index of the string that should be appended to the newly generated string from
    //                  the vector being passed as argument in the function "execute_rule".
    // b) negative int: Indicates the index (should be converted back to positive when accessing it) of the char to be
    //                  added to the newly generated string from the "all_adding_chars" vector.
    vector<int> steps;

    // Stores all the new chars to add (all chars that will not be considered strings.
    vector<char> all_adding_chars;

    // Amount of existing language strings to append to the new generated string.
    int string_num;
public:
    // Constructor: Parses the string into a rule.
    explicit RecursiveStepRule(string rule);

    // Calculates the new strings to generate for this rule (computing all current language combinations),
    // and stores them in the strings_to_add vector.
    void compute_new_strings(set<string> &language_string, unsigned long language_size, vector<string> &strings_to_add);

    // Executes the rule for the given strings and returns the newly generated string.
    string execute_rule(vector<string> language_strings);
};


#endif //RECURSIVE_LANGUAGES_RECURSIVESTEPRULE_H
