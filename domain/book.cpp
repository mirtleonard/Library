//
// Created by leonard on 09.04.2022.
//

#include "book.h"
#include <string>

int Book::ID = 0;

Book::Book(const string &title, const string &author, const string &genre, const int &year) {
    this->id = ID++;
    modifyBook(title, author, genre, year);
}

void Book::modifyBook(const string &title, const string &author, const string &genre, const int &year) {
    this->title = title;
    this->author = author;
    this->genre = genre;
    this->year = year;
}

ostream& operator<<(ostream& os, const Book &book) {
    os << to_string(book.getId()) + " | " + book.getTitle() + " | " + book.getAuthor() + " | " + book.getGenre() + " | " + to_string(book.getYear()) + "\n";
    return os;
}