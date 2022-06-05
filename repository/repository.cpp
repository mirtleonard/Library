//
// Created by leonard on 09.04.2022.
//
#include "repository.h"
#include <fstream>
#include <QtDebug>

void Repository::addBook(const Book &book) {
    list.push_back(book);
}

const int Repository::getSize() {
    return list.size();
}

const vector<Book>& Repository::getList() {
    return list;
}

const Book& Repository::getBook(const int &pos) {
    if (pos < 0 || pos > list.size()) {
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
    list.erase(list.begin() + pos);
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

FileRepository::FileRepository(const string& file) {
    this->fileName = file;
    ifstream fin(fileName);
    try {
        while (!fin.eof()) {
            string title, author, genre, year;
            getline(fin, title, '|');
            getline(fin, author, '|');
            getline(fin, genre, '|');
            getline(fin, year);
            list.push_back(Book(title, author, genre, stoi(year)));
        }
    } catch(const exception &e) {
        //qDebug() << e.what();
    }

    fin.close();
}

void FileRepository::updateFile() {
    ofstream fout(fileName);
    for (auto book : list) {
        fout << book.getTitle() << "|" << book.getAuthor() << "|" << book.getGenre() << "|" << book.getYear() << "\n";
    }
    fout.close();
}

void FileRepository::clearFile() {
    ofstream fout(fileName);
    fout.close();
}
