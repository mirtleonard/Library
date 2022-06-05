#ifndef GUI_H
#define GUI_H

#include "mainwindow.h"
#include <QMessageBox>
#include <QComboBox>
#include <QWidget>
#include <QDialog>
#include <QFormLayout>
#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <qboxlayout.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <qlineedit.h>
#include <qlabel.h>
#include "service/service.h"
#include <string>
//#include "main.moc"

class GUI : public QWidget {
  //Q_OBJECT

private:
    Service srv;
    QWidget* outputWidget = new QWidget;

    QHBoxLayout* mainLayout = new QHBoxLayout;
    QHBoxLayout* newLayout = new QHBoxLayout;
    QTableWidget* outputList;
    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* modifyButton;
    QPushButton* sortButton;
    QComboBox* sortList;
    void layoutInitialization();
    void eventConnection();
    void newAction();
    void reloadList();
    void addAction();
    void deleteAction();
    void undoAction();
    void modifyAction();
    void sortAction();
    static void clearLayout(QLayout *layout);
public:
    GUI(const string &file);
    //GUI();
    //~GUI();
};




#endif // GUI_H
