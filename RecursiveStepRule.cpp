//
// Created by axelzucho on 9/03/19.
//

#include "RecursiveStepRule.h"

#define LANGUAGE_FINISHED 0
#define ADDED_INDEX 1

RecursiveStepRule::RecursiveStepRule(string rule) {
    all_adding_chars.clear();
    steps.clear();
    int current_id = -1;
    string_num = 0;
    for(const auto& it:rule){
        if(it >= 'u' && it <= 'z'){
            string_num++;
            steps.push_back(it - 'u');
        }
        else {
            all_adding_chars.push_back(it);
            steps.push_back(current_id--);
        }
    }
}

string RecursiveStepRule::execute_rule(vector<string> language_strings) {
    string result;
    for(const auto it:steps){
        // This means that we need to add a new char.
        if(it < 0){
           result += all_adding_chars[-it - 1];
        } else {
            result += language_strings[it];
        }
    }
    return result;
}

int increment_index(vector<unsigned long>& indices, unsigned long language_length){
    if(language_length <= 1) return LANGUAGE_FINISHED;
    for(unsigned long i = indices.size() -1; i >= 0; --i){
       if(indices[i] < language_length - 1){
           indices[i]++;
           return ADDED_INDEX;
       } else {
           indices[i] = 0;
       }
    }
    return LANGUAGE_FINISHED;
}

void RecursiveStepRule::add_strings_to_language(set<string> &language_string) {
    vector<unsigned long> current_indices(string_num, 0);
    vector<string> current_language_strings;
    unsigned long language_size = language_string.size();

    do {
        current_language_strings.clear();
        for(const auto it:current_indices){
            auto language_iter = language_string.begin();
            if(it >= language_size){
                current_language_strings.emplace_back("");
            } else {
                advance(language_iter, it);
                current_language_strings.push_back(*language_iter);
            }
        }
        language_string.insert(execute_rule(current_language_strings));
    } while(increment_index(current_indices, language_size) != LANGUAGE_FINISHED);

}


