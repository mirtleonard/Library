//
// Created by leonard on 09.04.2022.
//

#include <QDebug>
#include "tests.h"
#include <assert.h>
#include "../domain/book.h"
#include "../repository/repository.h"
#include "../service/service.h"
#include <iostream>
#include <fstream>
#include <string>

void testDynamicVector();

void Test::runTests() {
    testDomain();
    testRepository();
    testService();
    testCart();
    testFileRepository();
    Book::ID = 0;
}

void Test::testDomain() {
    Book book = Book("Ion", "Liviu Rebreanu", "novel", 1920);
    assert(book.getTitle() == "Ion");
    assert(book.getAuthor() == "Liviu Rebreanu");
    assert(book.getGenre() == "novel");
    assert(book.getYear() == 1920);
}

void Test::testRepository() {
    Repository repo = Repository();
    Book book = Book("Ion", "Liviu Rebreanu", "novel", 1920);
    repo.addBook(book);
    assert(repo.stringify() == "ID | Title | Author | Genre | year\n1 | Ion | Liviu Rebreanu | novel | 1920\n");
    book = Book("Ion", "Liviu Rebreanu", "novel", 1921);
    repo.addBook(book);
    book = Book("Ion", "Liviu Rebreanu", "novel", 1922);
    repo.addBook(book);
    assert(repo.filterBooks(2, "1920") == "ID | Title | Author | Genre | year\n1 | Ion | Liviu Rebreanu | novel | 1920\n");
    repo.removeBook(3);
    repo.modifyBook(1, "Moara cu noroc", "Ioan Slavici", "classics", 1881);
    repo.sortBooks(1);
    repo.sortBooks(2);
    repo.sortBooks(3);
    repo.sortBooks(4);
}

void Test::testFileRepository() {
    FileRepository repo = FileRepository(file);
    Book book = Book("Ion", "Liviu Rebreanu", "novel", 1920);
    repo.addBook(book);
    assert(repo.stringify() == "ID | Title | Author | Genre | year\n6 | Ion | Liviu Rebreanu | novel | 1920\n");
    FileRepository repo2 = FileRepository(file);
    assert(repo2.stringify() == "ID | Title | Author | Genre | year\n7 | Ion | Liviu Rebreanu | novel | 1920\n");
    book = Book("Ion", "Liviu Rebreanu", "novel", 1921);
    repo.addBook(book);
    repo.removeBook(6);
    repo.modifyBook(8, "Moara cu noroc", "Ioan Slavici", "classics", 1881);
    repo.sortBooks(2);
    repo.clearFile();
}

void Test::testService() {
    Service srv = Service(file);
    srv.addBook("Ion", "Liviu Rebreanu", "novel", 1920);
    srv.addToCart(4);
    assert(srv.getCart() == "ID | Title | Author | Genre | year\n4 | Ion | Liviu Rebreanu | novel | 1920\n");
    assert(srv.getCartSize() == 1);
    srv.clearCart();
    srv.generateCart(1);
   // qDebug() << srv.showBooks().c_str();
    assert(srv.getCart() == "ID | Title | Author | Genre | year\n4 | Ion | Liviu Rebreanu | novel | 1920\n");
    try {
        srv.generateCart(10);
    } catch(const exception &e) {
    }
    try {
        srv.addToCart(4);
    } catch(const char *msg) {
    }
    assert(srv.showBooks() == "ID | Title | Author | Genre | year\n4 | Ion | Liviu Rebreanu | novel | 1920\n");
    string book = srv.searchBook(4);
    assert(book == "4 | Ion | Liviu Rebreanu | novel | 1920\n");
    srv.sortBooks(1);
    assert(srv.filterBooks(1, "Ion") ==
           "ID | Title | Author | Genre | year\n4 | Ion | Liviu Rebreanu | novel | 1920\n");
    srv.removeBook(4);
    try {
        srv.removeBook(4);
        //assert(false);
    } catch (const char *msg) {
        assert(true);
    }
    try {
        srv.searchBook(4);
        //assert(false);
    } catch (const char *msg) {
        assert(true);
    }
    try {
        srv.modifyBook(-1, "a", "b", "c", 1);
        assert(false);
    } catch (const char *msg) {
        assert(true);
    }
    assert(srv.showBooks() == "ID | Title | Author | Genre | year\n");
    srv.clearFile();
}

void Test::testCart() {
   Cart cart = Cart();
   Book book = Book("Ion", "Liviu Rebreanu", "novel", 1920);
   cart.addBook(book);
   cart.clearCart();
   assert(cart.getSize() == 0);
}
