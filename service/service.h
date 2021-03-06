//
// Created by leonard on 09.04.2022.
//

#ifndef LAB6_7_SERVICE_H
#define LAB6_7_SERVICE_H

#include "../repository/repository.h"
#include "../repository/cart.h"
//#include "../domain/book.h"

class Service {
private:
    FileRepository repo;
    Cart cart;
public:
    Service(const string& file);
    void modifyBook(const int &id, const string &title, const string &author, const string &genre, const int &year);
    void addBook(const string &title, const string &author, const string &genre, const int &year);
    void removeBook(const int &id);
    const string searchBook(const int &id);
    const string showBooks();
    const string filterBooks(const int &op, const string &key);
    const string sortBooks(const int &key);
    const vector<Book>& getRepo();
    void generateCart(int books);
    const int getCartSize();
    const string getCart();
    void addToCart(int id);
    void clearCart();
    void clearFile();
};


#endif //LAB6_7_SERVICE_H
