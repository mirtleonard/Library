//
// Created by leonard on 09.04.2022.
//

#include "tests.h"
#include <assert.h>
#include "../domain/book.h"
#include "../repository/repository.h"
#include <iostream>

void Test::runTests() {
    testDomain();
    testRepository();
}

void Test::testDomain() {
    Book book = Book("Ion", "Liviu Rebreanu", "novel", 1920);
    assert(book.getTitle() == "Ion");
    assert(book.getAuthor() == "Liviu Rebreanu");
    assert(book.getGenre() == "novel");
    assert(book.getYear() == 1920);
    book.modifyBook("Moara cu noroc", "Ioan Slavici", "classics", 1881);
    assert(book.getTitle() == "Moara cu noroc");
    assert(book.getAuthor() == "Ioan Slavici");
    assert(book.getGenre() == "classics");
    assert(book.getYear() == 1881);
}

void Test::testRepository() {
    Repository repo = Repository();
    Book book = Book("Ion", "Liviu Rebreanu", "novel", 1920);
    repo.addBook(book);
    assert(repo.stringify() == "1 | Ion | Liviu Rebreanu | novel | 1920\n");
    book = Book("Ion", "Liviu Rebreanu", "novel", 1920);
    repo.addBook(book);
    book = Book("Ion", "Liviu Rebreanu", "novel", 1920);
    repo.addBook(book);
    repo.removeBook(3);
    book.modifyBook("Moara cu noroc", "Ioan Slavici", "classics", 1881);
    repo.modifyBook(1, book);
}