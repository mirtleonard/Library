//
// Created by leonard on 09.04.2022.
//

#ifndef LAB6_7_REPOSITORY_H
#define LAB6_7_REPOSITORY_H
#include <../domain/book.h>
#include <vector>

class Repository {
private:
    vector<Book> list;
public:
    friend class Cart;
    void addBook(const Book &book);
    void removeBook(const int &id);
    void modifyBook(const int &id, const string &title, const string &author, const string &genre, const int &year);
    const Book& getBook(const int &id);
    const int findBook(const int &id);
    const string stringify();
    const string filterBooks(const int &op, const string &key);
    void sortBooks(const int &key);
    void change(Book &book1, Book &book2);
    const int getSize();
};

class Compare {
private:
    int key;
public:
    Compare(const int &key);
    bool operator() (Book x, Book y);
};

#endif //LAB6_7_REPOSITORY_H
