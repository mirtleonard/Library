//
// Created by leonard on 09.04.2022.
//

#include "repository.h"
#include <iostream>

void Repository::addBook(const Book &book) {
    list.push_back(book);
}

const int Repository::findBook(const int &id) {
    int pos = 0;
    for (auto book : list) {
        if (book.getId() == id) {
            return pos;
        }
        ++pos;
    }
    return -1;
}

void Repository::removeBook(const int &id) {
    const int pos = findBook(id);
    if (pos < 0) {
        throw exception();
    }
    list.erase(list.begin() + pos);
}

void Repository::modifyBook(const int &id, const Book &newBook) {
    const int pos = findBook(id);
    if (pos < 0) {
        throw exception();
    }
    Book &book = list[pos];
    book.modifyBook(newBook.getTitle(), newBook.getAuthor(), newBook.getGenre(), newBook.getYear());
}

const string Repository::stringify() {
    string result = "";
    for (auto book : list) {
       result += to_string(book.getId()) + " | " + book.getTitle() + " | " + book.getAuthor() + " | " + book.getGenre() + " | " + to_string(book.getYear()) + "\n";
    }
    return result;
}