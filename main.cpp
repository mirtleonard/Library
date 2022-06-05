#include <QApplication>
#include "service/service.h"
#include "ui/gui.h"
#include "tests/tests.h"

int main(int argc, char *argv[])
{
    Test test = Test();
    test.runTests();
    QApplication a(argc, argv);
    GUI w = GUI("/home/leonard/Documents/giani/facultate/I/sem2/OOP/learnQT/books.txt");
    w.show();
    return a.exec();
}
