//
// Created by axelzucho on 8/03/19.
//

#include "Language.h"
#include <fstream>
#include <iostream>

using namespace std;


Language::Language(const string &path, bool &generated) {
    fstream file;
    file.open(path);
    // Check if we could open the provided filepath.
    if (!file.is_open()) {
        cout << "File not opened correctly" << endl;
        // Signal that the language was not generated.
        generated = false;
        return;
    }

    this->language_generated.clear();
    this->new_additions.clear();

    string line;
    // Gets the first line containing Baseline.
    getline(file, line);
    {
        size_t previous_index = 0;
        // Finds the next ','.
        size_t current_index = line.find_first_of(',');
        // While there are still ','.
        while (current_index != string::npos) {
            this->new_additions.push_back(line.substr(previous_index, current_index));
            // Push the char into the language.
            this->language_generated.insert(line.substr(previous_index, current_index));
            previous_index = ++current_index;
            // Find the next ','.
            current_index = line.find_first_of(',', current_index);
        }
        // Add the last char after the last comma.
        if (!line.empty()) {
            string string_to_add = line.substr(previous_index, line.length());
            this->new_additions.push_back(line.substr(previous_index, line.length()));
            this->language_generated.insert(line.substr(previous_index, line.length()));
        }
    };

    // Gets the next line containing the rules.
    getline(file, line);
    size_t previous_index = 0;
    // Same as before, parses the rules.
    size_t current_index = line.find_first_of(',');
    while (current_index != string::npos) {
        // Creates a new Rule object with the string.
        RecursiveStepRule recursive_step_rule(line.substr(previous_index, current_index));
        this->recursive_steps.push_back(recursive_step_rule);
        previous_index = ++current_index;
        current_index = line.find_first_of(',', current_index);
    }
    // Adds the last rule after the last comma.
    if (!line.empty()) {
        RecursiveStepRule recursive_step_rule(line.substr(previous_index, line.length()));
        this->recursive_steps.push_back(recursive_step_rule);
    }

    // Finally, gets the number of steps to be executed.
    int step_num;
    file >> step_num;
    this->number_of_steps = step_num;

    // Signal that the language was generated successfully.
    generated = true;
}

void Language::recursive_step() {
    // Clears the vector of new additions to repopulate it.
    new_additions.clear();
    unsigned long current_size = language_generated.size();
    vector<string> strings_to_add;
    // Iterates all the rules, computing new strings, which stores them in the "strings_to_add" vector.
    // We can't add them directly to the language since strings computed in the first steps should not affect the later
    // rules.
    for (auto &it: recursive_steps) {
        it.compute_new_strings(language_generated, current_size, strings_to_add);
    }
    // Iterates all the newly generated strings.
    for (const auto &it: strings_to_add) {
        // If that string wasn't already in the language.
        if (language_generated.find(it) == language_generated.end()) {
            // Adds it to both places.
            language_generated.insert(it);
            new_additions.push_back(it);
        }
    }
}

void Language::print_step(int step) {
    cout << step << " times: ";

    // Checks if there were no new additions.
    if (new_additions.empty()) {
        cout << endl;
        return;
    }

    // Iterates all the new additions to print them.
    for (unsigned int i = 0; i < new_additions.size() - 1; ++i) {
        cout << new_additions[i] << ", ";
    }
    cout << new_additions[new_additions.size() - 1] << endl;
}

void Language::all_steps() {
    cout << "Applying the recursive step:" << endl;
    print_step(0);
    for (int i = 1; i <= number_of_steps; ++i) {
        // For all steps. executes the recursive step and prints it.
        recursive_step();
        print_step(i);
    }
}