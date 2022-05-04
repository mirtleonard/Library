//
// Created by leonard on 09.04.2022.
//

#include "service.h"
#include <random>

Service::Service() {
    this->repo = Repository();
    this->cart = Cart();
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
        const int pos = repo.findBook(id);
        const Book &book = repo.getBook(pos);
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

void Service::clearCart() {
    cart.clearCart();
}

const int Service::getCartSize() {
    return cart.getSize();
}

void Service::addToCart(int id) {
    try {
        if (cart.findBook(id) != -1) {
            throw "Id already exists";
        }
        const int pos = repo.findBook(id);
        const Book &book = repo.getBook(pos);
        cart.addBook(book);
    } catch (const char *msg) {
        throw msg;
    }
}

void Service::generateCart(int books) {
    if (books > repo.getSize() || books < 0) {
        throw exception();
    }
    cart.clearCart();
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, repo.getSize() - 1);
    while (books) {
        int rndNr = dist(mt);// numar aleator intre [0,size-1]
        const Book &book = repo.getBook(rndNr);
        if (cart.findBook(book.getId()) == -1) {
            cart.addBook(book);
            --books;
        }
    }
}

const string Service::getCart() {
    return cart.stringify();
}
