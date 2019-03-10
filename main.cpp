#include <iostream>
#include "Language.h"

int main() {
    string file_path;

    cout << "Input the file path\n";
    cin >> file_path;

    Language language(file_path);
    language.all_steps();

    return 0;
}