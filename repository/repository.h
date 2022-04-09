//
// Created by leonard on 09.04.2022.
//

#ifndef LAB6_7_REPOSITORY_H
#define LAB6_7_REPOSITORY_H
#include <vector>
#include <../domain/book.h>

class Repository {
private:
    vector<Book> list;
public:
    void addBook(const Book &book);
    void removeBook(const int &id);
    void modifyBook(const int &id, const Book &newBook);
    const int findBook(const int &id);
    const string stringify();
};


#endif //LAB6_7_REPOSITORY_H