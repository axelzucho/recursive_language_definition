//
// Created by axelzucho on 9/03/19.
//

#include "RecursiveStepRule.h"

#define LANGUAGE_FINISHED 0
#define ADDED_INDEX 1

#include <map>

RecursiveStepRule::RecursiveStepRule(string rule) {
    all_adding_chars.clear();
    steps.clear();
    string_num = 0;

    int current_id = -1;
    map<char,int> indices;
    int current_index = 0;

    for(const auto& it:rule){
        if(it >= 'u' && it <= 'z'){
            string_num++;
            if(indices.find(it) == indices.end()){
                indices.insert(make_pair(it, current_index++));
            }
            steps.push_back(indices[it]);
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
    for(unsigned long i = indices.size() - 1; i >= 0; --i){
       if(indices[i] < language_length - 1){
           indices[i]++;
           return ADDED_INDEX;
       } else if (i != 0){
           indices[i] = 0;
       } else {
           return LANGUAGE_FINISHED;
       }
    }
    return LANGUAGE_FINISHED;
}

void RecursiveStepRule::add_strings_to_language(set<string> &language_string, unsigned long language_size, vector<string>& strings_to_add) {
    vector<unsigned long> current_indices(string_num, 0);
    vector<string> current_language_strings;

    do {
        current_language_strings.clear();
        for(const auto it:current_indices){
            auto language_iter = language_string.begin();
            if(it >= language_size){
                current_language_strings.emplace_back("");
            } else {
                advance(language_iter, it);
                if(*language_iter == NULL_STRING){
                    current_language_strings.emplace_back("");
                } else {
                    current_language_strings.push_back(*language_iter);
                }
            }
        }
        strings_to_add.push_back(execute_rule(current_language_strings));
    } while(increment_index(current_indices, language_size) != LANGUAGE_FINISHED);
}


