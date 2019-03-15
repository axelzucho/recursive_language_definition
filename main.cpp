#include <iostream>
#include "Language.h"

int main() {
    string file_path;
    bool generated;

    cout << "Please input the file path:\n";
    cin >> file_path;

    // We just create a language with the data in the provided file.
    Language language(file_path, generated);
    if (!generated) {
        printf("Could not generate the language, exiting.\n");
        return 0;
    }

    // And then we execute all steps.
    language.all_steps();

    return 0;
}