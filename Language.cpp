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
    this->new_additions.clear();
    this->number_of_steps = number_of_steps;

    string line;
    // Getting base
    getline(file, line);
    {
        size_t previous_index = 0;
        size_t current_index = line.find_first_of(',');
        while (current_index != string::npos) {
            this->new_additions.push_back(line.substr(previous_index, current_index));
            this->language_generated.insert(line.substr(previous_index, current_index));
            previous_index = ++current_index;
            current_index = line.find_first_of(',', current_index);
        }
        string string_to_add = line.substr(previous_index, line.length());
        this->new_additions.push_back(line.substr(previous_index, line.length()));
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

    int step_num;
    file >> step_num;
    this->number_of_steps = step_num;
}

void Language::recursive_step() {
    new_additions.clear();
    unsigned long current_size = language_generated.size();
    vector<string> strings_to_add;
    for(auto& it: recursive_steps){
        it.add_strings_to_language(language_generated, current_size, strings_to_add);
    }
    for(const auto& it: strings_to_add){
        if(language_generated.find(it) == language_generated.end()){
            language_generated.insert(it);
            new_additions.push_back(it);
        }
    }
}

void Language::print_step(int step){
    cout << step << " times: ";
    for(int i = 0; i < new_additions.size() - 1; ++i){
        cout << new_additions[i] << ", ";
    }
    cout << new_additions[new_additions.size()-1] << endl;
}

void Language::all_steps() {
    cout << "Applying the recursive step:" << endl;
    print_step(0);
    for(int i = 1; i <= number_of_steps; ++i){
        recursive_step();
        print_step(i);
    }
}