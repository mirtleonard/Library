//
// Created by leonard on 09.04.2022.
//

#ifndef LAB6_7_TEST_H
#define LAB6_7_TEST_H
#include <string>


class Test {
private:
    std::string file = "/home/leonard/Documents/giani/facultate/I/sem2/OOP/learnQT/tests/test.txt";
    void testDomain();
    void testRepository();
    void testFileRepository();
    void testService();
    void testCart();
public:
    void runTests();

};


#endif //LAB6_7_TEST_H
