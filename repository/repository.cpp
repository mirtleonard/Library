//
// Created by leonard on 09.04.2022.
//

#include "DynamicVector.h"
#include "repository.h"
#include <iostream>


void Repository::addBook(const Book &book) {
    list.add(book);
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
    for (auto &book : list) {
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
    list.remove(pos);
}

void Repository::modifyBook(const int &id, const string &title, const string &author, const string &genre, const int &year) {
    const int pos = findBook(id);
    if (pos < 0) {
        throw "Invalid Id!";
    }
    Book &book = list[pos];
    book.setTitle(title);
    book.setAuthor(author);
    book.setGenre(genre);
    book.setYear(year);
}

const string Repository::stringify() {
    string result = "ID | Title | Author | Genre | year\n";
    for (auto &book : list) {
       result += book.stringify();
    }
    return result; }

const string Repository::filterBooks(const int &op, const string &key) {
    string result = "ID | Title | Author | Genre | year\n";
    for (auto &book : list) {
        if (op == 1 && book.getTitle() == key) {
            result += book.stringify();
        } else if (op == 2 && to_string(book.getYear()) == key) {
            result += book.stringify();
        }
    }
    return result;}

void Repository::change(Book &book1, Book &book2) {
    string aux = book1.getTitle();
    int aux2 = book1.getYear();
    book1.setYear(book2.getYear());
    book2.setYear(aux2);
    book1.setTitle(book2.getTitle());
    book2.setTitle(aux);
    aux = book1.getAuthor();
    book1.setAuthor(book2.getAuthor());
    book2.setAuthor(aux);
    aux = book1.getGenre();
    book1.setGenre(book2.getGenre());
    book2.setGenre(aux);
}

void Repository::sortBooks(const int &key) {
    for (auto &book1 : list) {
        for (auto &book2 : list) {
            if (key == 1 && book2.getTitle() > book1.getTitle()) {
                change(book1, book2);
            } else if (key == 2 && book2.getAuthor() > book1.getAuthor()) {
                change(book1, book2);
            } else if (key == 3 && book2.getGenre() > book1.getGenre()) {
                change(book1, book2);
            } else if (key == 4 && book2.getYear() > book1.getYear()) {
                change(book1, book2);
            }
        }
    }
}
