//
// Created by axelzucho on 8/03/19.
//

#include "Language.h"
#include <fstream>
#include <iostream>

using namespace std;


Language::Language(const string &path) {
    fstream file;
    file.open(path);
    if (!file.is_open()) {
        cout << "File not opened correctly" << endl;
        return;
    }

    this->language_generated.clear();

    string line;
    // Getting base
    getline(file, line);
    {
        size_t previous_index = 0;
        size_t current_index = line.find_first_of(',');
        while (current_index != string::npos) {
            this->language_generated.insert(line.substr(previous_index, current_index));
            previous_index = ++current_index;
            current_index = line.find_first_of(',', current_index);
        }
        string string_to_add = line.substr(previous_index, line.length());
        this->language_generated.insert(line.substr(previous_index, line.length()));
    };
    getline(file, line);
    size_t previous_index = 0;
    size_t current_index = line.find_first_of(',');
    while (current_index != string::npos)
    {
        RecursiveStepRule recursive_step_rule(line.substr(previous_index, current_index));
        this->recursive_steps.push_back(recursive_step_rule);
        previous_index = ++current_index;
        current_index = line.find_first_of(',', current_index);
    }
    RecursiveStepRule recursive_step_rule(line.substr(previous_index, line.length()));
    this->recursive_steps.push_back(recursive_step_rule);
}

void Language::recursive_step() {
    unsigned long current_size = language_generated.size();
    vector<string> strings_to_add;
    for(auto& it: recursive_steps){
        it.add_strings_to_language(language_generated, current_size, strings_to_add);
    }
    for(const auto& it: strings_to_add){
        language_generated.insert(it);
    }
}