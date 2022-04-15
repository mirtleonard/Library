//
// Created by leonard on 09.04.2022.
//

#include "service.h"

Service::Service() {
    this->repo = Repository();
}

void Service::addBook(const string &title, const string &author, const string &genre, const int &year) {
    Book book = Book(title, author, genre, year);
    repo.addBook(book);
}

void Service::removeBook(const int &id) {
    try {
        repo.removeBook(id);
    } catch(const char* msg) {
        throw msg;
    }
}

void Service::modifyBook(const int &id, const string &title, const string &author, const string &genre, const int &year) {
    try {
        repo.modifyBook(id, title, author, genre, year);
    } catch (const char *msg) {
        throw msg;
    }}

const string Service::showBooks() {
    return repo.stringify();
}

const string Service::searchBook(const int &id) {
    try {
        const Book &book = repo.searchBook(id);
        return book.stringify();
    } catch (const char *msg) {
        throw msg;
    }
}

const string Service::filterBooks(const int &op, const string &key) {
    return repo.filterBooks(op, key);
}

const string Service::sortBooks(const int &key) {
    repo.sortBooks(key);
    return repo.stringify();
}
