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
    // Map used to translate the char representing a string to the index of that string.
    map<char,int> indices;
    int current_index = 0;

    // Iterating all chars representing steps.
    for(const auto& it:rule){
        // If the char considering should be a language string.
        if(it >= 'u' && it <= 'z'){
            string_num++;
            // Checks if the char was already assigned an index.
            if(indices.find(it) == indices.end()){
                // Assigns the index.
                indices.insert(make_pair(it, current_index++));
            }
            // Appends the index as explained in the ".h" file.
            steps.push_back(indices[it]);
        }
        else {
            // Appends the char to the vector.
            all_adding_chars.push_back(it);
            // Appends the negative index as explained in the ".h" file.
            steps.push_back(current_id--);
        }
    }
}

string RecursiveStepRule::execute_rule(vector<string> language_strings) {
    string result;
    for(const auto it:steps){
        // This means that we need to add a new char.
        if(it < 0){
            // Append the char.
           result += all_adding_chars[-it - 1];
        } else {
            // Append the string.
            result += language_strings[it];
        }
    }
    // Returns the generated result.
    return result;
}

// Function used internally to increment the indexes used when iterating the whole language.
int increment_index(vector<unsigned long>& indices, unsigned long language_length){
    if(language_length <= 1) return LANGUAGE_FINISHED;
    // Iterates through all the indices backwards.
    for(unsigned long i = indices.size() - 1; i >= 0; --i){
        // If we can still add one to the last index, do it.
       if(indices[i] < language_length - 1){
           indices[i]++;
           return ADDED_INDEX;
           // If it is not the first index (which would mean that we have traversed all the indices).
       } else if (i != 0){
           indices[i] = 0;
       } else {
           return LANGUAGE_FINISHED;
       }
    }
    // Returns a flag indicating that we have finished iterating.
    return LANGUAGE_FINISHED;
}

void RecursiveStepRule::compute_new_strings(set<string> &language_string, unsigned long language_size, vector<string>& strings_to_add) {
    // Create the vector where all indices will be stored, starting with only 0's.
    vector<unsigned long> current_indices(string_num, 0);
    vector<string> current_language_strings;

    do {
        // We need to clear the vector where we store the strings to use.
        current_language_strings.clear();
        // We iterate all indices.
        for(const auto it:current_indices){
            auto language_iter = language_string.begin();
            if(it >= language_size){
                current_language_strings.emplace_back("");
            } else {
                // We want to access the iterator in the position "it" (the index).
                advance(language_iter, it);
                // If it is a null string, just append an empty string.
                if(*language_iter == NULL_STRING){
                    current_language_strings.emplace_back("");
                } else {
                    current_language_strings.push_back(*language_iter);
                }
            }
        }
        // We generate a new string and append it to the vector, passing as arguments the strings to use.
        strings_to_add.push_back(execute_rule(current_language_strings));
        // We execute this loop until we receive the flag that we have finished iterating the language.
    } while(increment_index(current_indices, language_size) != LANGUAGE_FINISHED);
}


