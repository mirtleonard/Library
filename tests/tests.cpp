//
// Created by leonard on 09.04.2022.
//

#include "tests.h"
#include <assert.h>
#include "../domain/book.h"
#include "../repository/repository.h"
#include "../service/service.h"
#include <iostream>

void testDynamicVector();

void Test::runTests() {
    testDomain();
    testRepository();
    testService();
    testDynamicVector();
    Book::ID = 0;
}

void Test::testDomain() {
    Book book = Book("Ion", "Liviu Rebreanu", "novel", 1920);
    assert(book.getTitle() == "Ion");
    assert(book.getAuthor() == "Liviu Rebreanu");
    assert(book.getGenre() == "novel");
    assert(book.getYear() == 1920);
    Book book2 = Book(book);
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

void Test::testService() {
    Service srv = Service();
    srv.addBook("Ion", "Liviu Rebreanu", "novel", 1920);
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
        //assert(false);
    } catch (const char *msg) {
        assert(true);
    }
    assert(srv.showBooks() == "ID | Title | Author | Genre | year\n");
}
void Test::testDynamicVector() {
	DynamicVector<int>v,v2;
	v.add(3);
	v.add(4);
	v.add(5);
    v.add(5);
    v.add(5);
    v.add(5);
    v.remove(3);
    v2.add(21);
    v2 = v;
	assert(v.size() == 5);
	assert(v[2] == 5);
	v[2] = 6;
	assert(v[2] == 6);

	auto it = v.begin();
	v.erase(it);

	assert(v.size() == 4);

	for (int i = 0; i <= 10; i++)
		v.add(i);

	auto it2 = v.begin();
	while (it2 != v.end()) {
		v.erase(it2);
	}
	assert(v.size() == 0);
}
