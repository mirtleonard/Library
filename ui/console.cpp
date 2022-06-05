//
// Created by leonard on 09.04.2022.
//

#include "console.h"
#include <string>
#include <iostream>
#include <unistd.h>
using namespace std;

/*
Console::Console(istream &stream):in(stream) {
    this->service = Service("");
}
*/
const int Console::readNumber(string msg) {
    int number;
    string input;
    cout << msg;
    getline(in, input);
    try {
        number = stoi(input);
    } catch(exception &e) {
        throw e;
    }
    return number;
}

void Console::run() {
    string command;
    cout << "Welcome to Book Manager\nUse 'help' if you are stuck\n";
    while (true) {
        cout << "You have " << service.getCartSize() << " books in the cart\n";
        cout << ">>> ";
        getline(in, command);
        cout << command << "\n";
        try {
            if (command == "help") {
                help();
            } else if (command == "add") {
                addBook();
            } else if (command == "remove") {
                removeBook();
            } else if (command == "modify") {
                modifyBook();
            } else if (command == "search") {
                searchBook();
            } else if (command == "show") {
                showBooks();
            } else if (command == "filter") {
                filterBooks();
            } else if (command == "sort") {
                sortBooks();
            } else if (command == "clcart") {
                service.clearCart();
            } else if (command == "addcart") {
                addToCart();
            } else if (command == "gencart") {
                generateCart();
            } else if (command == "showcart") {
                cout << service.getCart();
            } else if (command == "exit") {
                break;
            } else {
                throw "Invalid input!";
            }
        } catch(const char *msg) {
            cout << msg << "\n";
            sleep(1);
        }
    }
}

void Console::help() {
    cout << "Commands:\n";
    cout << "add - add book to repo\n";
    cout << "remove - remove book from repo\n";
    cout << "modify - modify book from repo\n";
    cout << "search - search book from repo\n";
    cout << "show - show books from repo\n";
    cout << "filter - filter books from repo\n";
    cout << "sort - sort books from repo\n";
    cout << "clcart - clear cart\n";
    cout << "addcart - add book to cart\n";
    cout << "gencart - generate random cart\n";
    cout << "showcart - print books from cart\n";
    cout << "exit - exit from the program\n";
}

void Console::addBook() {
    string title, author, genre, input;
    int year;
    cout << "Title: ";
    getline(in,  title);
    cout << "Author: ";
    getline(in,  author);
    cout << "Genre: ";
    getline(in,  genre);
    try {
        year = readNumber("Publishing year: ");
    } catch (const exception &e) {
        throw "Year is not valid";
    }
    service.addBook(title, author, genre, year);
}

void Console::removeBook() {
    string input;
    int id;
    try {
        id = readNumber("Id: ");
        service.removeBook(id);
    } catch(const exception &e) {
        throw "Invalid Id";
    }
}

void Console::modifyBook() {
    string title, author, genre, input;
    int year, id;
    try {
        id = readNumber("Insert the book id: ");
    } catch (const exception &e) {
        throw "Invalid id";
    }
    cout << "New title: ";
    getline(in, title);
    cout << "New author: ";
    getline(in,  author);
    cout << "New genre: ";
    getline(in,  genre);
    try {
        year = readNumber("New publishing year: ");
        service.modifyBook(id, title, author, genre, year);
    } catch (const exception &e) {
        throw "Year is not valid";
    }
}

void Console::searchBook() {
    string id;
    try {
        cout << service.searchBook(readNumber("Book id: "));
    } catch (const char *msg) {
        throw msg;
    }
}

void Console::showBooks() {
    cout << service.showBooks();
}

void Console::filterBooks() {
    int op;
    string input;
    try {
        op = readNumber("Filter by title(1)/year(2): ");
        if (op != 1 && op != 2) {
            throw exception();
        }
    } catch (exception &e) {
        throw "Invalid option";
    }
    cout << "Insert the " << (op == 1 ? "title: " : "year: ");
    getline(in, input);
    cout << service.filterBooks(op, input);
}

void Console::sortBooks() {
    int key;
    string input;
    try {
        key = readNumber("Sort by title(1)/author(2)/genre(3)/year(4): ");
        if (key < 1 || key > 4) {
            throw exception();
        }
    } catch(exception &e) {
        throw "Invalid option";
    }
    cout << service.sortBooks(key);
}

void Console::addToCart() {
    string input;
    cout << "Enter the title of the book: ";
    getline(in, input);
    string result = service.filterBooks(1, input);
    if (result == "" ) {
        throw "Book does't exist";
    }
    int id;
    try {
        id = readNumber("Choose ID: ");
    } catch(exception &e) {
        throw "Invalid Id";
    }
    service.addToCart(id);
}

void Console::generateCart() {
    int number;
    try {
        number = readNumber("Enter the number of books: ");
        service.generateCart(number);
    } catch (exception &e) {
        throw "Not enough books";
    }
}

