//
// Created by leonard on 09.04.2022.
//
#include "tests/tests.h"
#include "ui/ui.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv) {
    Test test = Test();
    test.runTests();
    if (argc > 1) {
        ifstream fin(argv[1]);
        if (!fin.good()) {
            cout << "File doesn't exist!\n";
        } else {
            Ui ui = Ui(fin);
            ui.run();
            return 0;
        }
    }
    Ui ui = Ui(cin);
    ui.run();
}
