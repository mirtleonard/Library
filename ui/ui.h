//
// Created by leonard on 09.04.2022.
//

#ifndef LAB6_7_UI_H
#define LAB6_7_UI_H

#include "../service/service.h"

class Ui {
private:
    Service service;
    void addBook();
    void removeBook();
    void modifyBook();
    void searchBook();
    void showBooks();
    void filterBooks();
    void sortBooks();
    void help();
public:
    void run();
    Ui();
};

#endif //LAB6_7_UI_H
