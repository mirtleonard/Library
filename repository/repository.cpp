//
// Created by leonard on 09.04.2022.
//

#include "repository.h"
#include <algorithm>
#include <iostream>


void Repository::addBook(const Book &book) {
    list.push_back(book);
}

const Book& Repository::searchBook(const int &id) {
    int pos = findBook(id);
    if (pos < 0) {
        throw "Invalid id";
    }
    return list[pos];
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
        throw "Invalid Id";
    }
    list.erase(list.begin() + pos);
}

void Repository::modifyBook(const int &id, const Book &newBook) {
    const int pos = findBook(id);
    if (pos < 0) {
        throw "Invalid Id!";
    }
    Book &book = list[pos];
    book.modifyBook(newBook.getTitle(), newBook.getAuthor(), newBook.getGenre(), newBook.getYear());
}

const string Repository::stringify() {
    string result = "ID | Title | Author | Genre | year\n";
    for (auto book : list) {
       result += book.stringify();
    }
    return result; }

const string Repository::filterBooks(const int &op, const string &key) {
    string result = "ID | Title | Author | Genre | year\n";
    for (auto book : list) {
        if (op == 1 && book.getTitle() == key) {
            result += book.stringify();
        } else if (op == 2 && to_string(book.getYear()) == key) {
            result += book.stringify();
        }
    }
    return result; }

void Repository::sortBooks(const int &key) {
    sort(list.begin(), list.end(), Compare(key));
}

Compare::Compare(const int &key)  {
    this->key = key;
}

bool Compare::operator() (Book x, Book y) {
    if (key == 1) {
        return x.getTitle() < y.getTitle();
    } else if (key == 2) {
        return x.getAuthor() < y.getAuthor();
    } else if (key == 3) {
        return x.getGenre() < y.getGenre();
    } else {
        return x.getYear() < y.getYear();
    }
}