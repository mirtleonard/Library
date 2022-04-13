//
// Created by leonard on 09.04.2022.
//

#include "ui.h"
#include <string>
#include <iostream>
#include <unistd.h>
using namespace std;

Ui::Ui() {
    this->service = Service();
}

void Ui::run() {
    string command;
    cout << "Welcome to Book Manager\nUse 'help' if you are stuck\n";
    while (true) {
        cout << ">>> ";
        getline(cin,  command);
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

void Ui::help() {
    cout << "Choose an action(number):\n";
    cout << "add\n";
    cout << "remove\n";
    cout << "modify\n";
    cout << "search\n";
    cout << "show\n";
    cout << "filter\n";
    cout << "sort\n";
    cout << "exit\n";
}

void Ui::addBook() {
    string title, author, genre, input;
    int year;
    cout << "Title: ";
    getline(cin,  title);
    cout << "Author: ";
    getline(cin,  author);
    cout << "Genre: ";
    getline(cin,  genre);
    cout << "Publishing year: ";
    getline(cin,  input);
    try {
        year = stoi(input);
    } catch (const exception &e) {
        throw "Year is not valid";
    }
    service.addBook(title, author, genre, year);
}

void Ui::removeBook() {
    string input;
    int id;
    cout << "Id: ";
    getline(cin,  input);
    try {
        id = stoi(input);
        service.removeBook(id);
    } catch(const exception &e) {
        throw "Invalid Id";
    }
}

void Ui::modifyBook() {
    string title, author, genre, input;
    int year, id;
    cout << "Insert the book id";
    getline(cin, input);
    try {
        id = stoi(input);
    } catch (const exception &e) {
        throw "Invalid id";
    }
    cout << "New title: ";
    getline(cin, title);
    cout << "New author: ";
    getline(cin,  author);
    cout << "New genre: ";
    getline(cin,  genre);
    cout << "New publishing year: ";
    getline(cin,  input);
    try {
        year = stoi(input);
        service.modifyBook(id, title, author, genre, year);
    } catch (const exception &e) {
        throw "Year is not valid";
    }
}

void Ui::searchBook() {
    string id;
    cout << "Book id: ";
    getline(cin, id);
    try {
        cout << service.searchBook(stoi(id));
    } catch (const char *msg) {
        throw msg;
    }
}

void Ui::showBooks() {
    cout << service.showBooks();
}

void Ui::filterBooks() {
    int op;
    string input;
    cout << "Filter by title(1)/year(2): ";
    getline(cin, input);
    try {
        op = stoi(input);
        if (op != 1 && op != 2) {
            throw exception();
        }
    } catch (exception &e) {
        throw "Invalid option";
    }
    cout << "Insert the " << (op == 1 ? "title: " : "year: ");
    getline(cin, input);
    cout << service.filterBooks(op, input);
}

void Ui::sortBooks() {
    int key;
    string input;
    cout << "Sort by title(1)/author(2)/genre(3)/year(4): ";
    getline(cin, input);
    try {
        key = stoi(input);
        if (key < 1 || key > 4) {
            throw exception();
        }
    } catch(exception &e) {
        throw "Invalid option";
    }
    cout << service.sortBooks(key);
}
