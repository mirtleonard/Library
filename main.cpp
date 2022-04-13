//
// Created by leonard on 09.04.2022.
//
#include "tests/tests.h"
#include "ui/ui.h"

int main() {
    Test test = Test();
    test.runTests();
    Ui ui = Ui();
    ui.run();
}