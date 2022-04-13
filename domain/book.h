//
// Created by leonard on 09.04.2022.
//

#ifndef LAB6_7_BOOK_H
#define LAB6_7_BOOK_H
#include <string>
using namespace std;

class Book {

private:
    friend class Test;
    static int ID;
    string title, author, genre;
    int id;
    int year;

public:
    Book(const string &title, const string &author, const string &genre, const int &year);
    void modifyBook(const string &title, const string &author, const string &genre, const int &year);
    friend ostream& operator<<(ostream& os, const Book& book);
    const string getTitle() const {
        return title;
    }
    const string getAuthor() const {
        return author;
    }
    const string getGenre() const {
        return genre;
    }
    const int getYear() const {
        return year;
    }
    const int getId() const {
        return id;
    }
    const string stringify() const;
};


#endif //LAB6_7_BOOK_H
