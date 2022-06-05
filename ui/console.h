//
// Created by leonard on 09.04.2022.
//

#ifndef LAB6_7_UI_H
#define LAB6_7_UI_H

#include <istream>
#include "../service/service.h"

class Console {
private:
    istream &in;
    Service service;
    void addBook();
    void removeBook();
    const int readNumber(string msg);
    void modifyBook();
    void searchBook();
    void showBooks();
    void filterBooks();
    void sortBooks();
    void addToCart();
    void generateCart();
    void help();
public:
    void run();
    Console(istream &in);
};

#endif //LAB6_7_UI_H
