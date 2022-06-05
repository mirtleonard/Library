#include "gui.h"
#include <unordered_map>

void GUI::layoutInitialization(){
    setLayout(mainLayout);
    QWidget* outputWidget = new QWidget;
    QVBoxLayout* outputLayout = new QVBoxLayout;

    outputWidget->setLayout(outputLayout);
    outputList = new QTableWidget;
    outputList->setRowCount(0);
    outputList->setColumnCount(5);
    outputList->setSelectionMode(QAbstractItemView::SingleSelection);
    outputList->setSelectionBehavior(QAbstractItemView::SelectRows);
    QStringList tempTableHeader;
    tempTableHeader << "Id" << "Book Title" << "Author" << "Genre" << "Year";
    outputList->setHorizontalHeaderLabels(tempTableHeader);
    outputLayout->addWidget(outputList);
    mainLayout->addWidget(outputWidget);

    QWidget* inputWidget = new QWidget;
    QVBoxLayout* inputLayout = new QVBoxLayout;

    inputWidget->setLayout(inputLayout);
    addButton = new QPushButton("Add");
    deleteButton = new QPushButton("Delete");
    modifyButton = new QPushButton("Modify");
    sortButton = new QPushButton("Sort");

    sortList = new QComboBox;
    sortList->addItem(QString("Sort by Title"));
    sortList->addItem(QString("Sort by Author"));
    sortList->addItem(QString("Sort by Genre"));
    sortList->addItem(QString("Sort by Year"));

    inputLayout->addWidget(addButton);
    inputLayout->addWidget(deleteButton);
    inputLayout->addWidget(modifyButton);
    inputLayout->addWidget(sortList);
    inputLayout->addWidget(sortButton);

    mainLayout->addWidget(inputWidget);
    QWidget* newWidget = new QWidget;
    newWidget->setLayout(newLayout);
    mainLayout->addWidget(newWidget);
}

void GUI::eventConnection() {
   QObject::connect(addButton, &QPushButton::clicked, this, &GUI::addAction);
   QObject::connect(deleteButton, &QPushButton::clicked, this, &GUI::deleteAction);
   QObject::connect(modifyButton, &QPushButton::clicked, this, &GUI::modifyAction);
   QObject::connect(sortButton, &QPushButton::clicked, this, &GUI::sortAction);
}

void GUI::reloadList() {
    outputList->clearContents();
    unordered_map<string, int> map;
    auto list = srv.getRepo();
    outputList->setRowCount(list.size());
    int i = 0;
    for(const auto& book: list) {
       try{
           auto& temporary = map.at(book.getGenre());
           temporary++;
       }catch(...){
           map.insert({book.getGenre(), 1});
       }
      outputList->setItem(i, 0, new QTableWidgetItem(QString::number(book.getId())));
      outputList->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(book.getTitle())));
      outputList->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(book.getAuthor())));
      outputList->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(book.getGenre())));
      outputList->setItem(i, 4, new QTableWidgetItem(QString::number(book.getYear())));
      ++i;
    }

    clearLayout(newLayout);
    for(const auto& el: map){
      QPushButton* btn = new QPushButton(QString::fromStdString(el.first));
      int number = el.second;
      QObject::connect(btn, &QPushButton::clicked, [number, this](){
        QMessageBox::information(this, "Number of Books:", QString::number(number));
      });
      newLayout->addWidget(btn);
    }

    mainLayout->update();
}

GUI::GUI(const string& file) : srv(file) {
      layoutInitialization();
      eventConnection();
      reloadList();
}

void GUI::addAction() {
      QDialog* diag = new QDialog(this);
      diag->setModal(true);
      QVBoxLayout* diagLayout = new QVBoxLayout;
      diag->setLayout(diagLayout);

      QWidget* form = new QWidget();
      QFormLayout* formLayout = new QFormLayout;
      form->setLayout(formLayout);

      QLineEdit* titleTxt = new QLineEdit;
      formLayout->addRow(new QLabel("Book Title: "), titleTxt);

      QLineEdit* authorTxt= new QLineEdit;
      formLayout->addRow(new QLabel("Author: "), authorTxt);

      QLineEdit* genreTxt = new QLineEdit;
      formLayout->addRow(new QLabel("Genre: "), genreTxt);

      QLineEdit* yearTxt = new QLineEdit;
      formLayout->addRow(new QLabel("Year: "), yearTxt);

      QPushButton* add = new QPushButton("Add");
      diagLayout->addWidget(form);
      diagLayout->addWidget(add);

      QObject::connect(add, &QPushButton::clicked, [&](){

        int year;
        std::string author, genre, title;
        try{
          title = titleTxt->text().toStdString();
          author = authorTxt->text().toStdString();
          genre = genreTxt->text().toStdString();
          year = yearTxt->text().toInt();
          this->srv.addBook(title, author, genre, year);
          reloadList();

        }
        catch(exception& ex){
          QMessageBox::warning(diag, "Warning", QString::fromStdString(ex.what()));
        }
        QMessageBox::warning(diag, "Book added", QString::fromStdString(titleTxt->text().toStdString()));
      });
      diag->exec();
}

void GUI::sortAction() {
      srv.sortBooks(sortList->currentIndex()+1);
      reloadList();

}

void GUI::deleteAction(){
      auto row = outputList->currentRow();
      if (row == -1) {
        QMessageBox::warning(this, "Warning", "No book was selected");
      } else {
        int bookID = (outputList->item(row, 0))->text().toInt();
        srv.removeBook(bookID);
        reloadList();
      }
}

void GUI::clearLayout(QLayout *layout) {
       if (layout == NULL)
           return;
       QLayoutItem *item;
       while((item = layout->takeAt(0))) {
           if (item->layout()) {
               clearLayout(item->layout());
               delete item->layout();
           }
           if (item->widget()) {
              delete item->widget();
           }
           delete item;
       }
}

void GUI::modifyAction() {
      auto row = outputList->currentRow();
      if (row == -1) {
        QMessageBox::warning(this, "Warning", "No book was selected");
      } else {
        int bookID = (outputList->item(row, 0))->text().toInt();
        QDialog* diag = new QDialog(this);
        diag->setModal(true);
        QVBoxLayout* diagLayout= new QVBoxLayout;
        diag->setLayout(diagLayout);

        QWidget *form = new QWidget;
        QFormLayout *formLayout = new QFormLayout;
        form->setLayout(formLayout);

        QLineEdit* titleTxt = new QLineEdit;
        formLayout->addRow(new QLabel("Book Title: "), titleTxt);

        QLineEdit* authorTxt= new QLineEdit;
        formLayout->addRow(new QLabel("Author: "), authorTxt);

        QLineEdit* genreTxt = new QLineEdit;
        formLayout->addRow(new QLabel("Genre: "), genreTxt);

        QLineEdit* yearTxt = new QLineEdit;
        formLayout->addRow(new QLabel("Year: "), yearTxt);

        QPushButton* add = new QPushButton("Modify");
        diagLayout->addWidget(form);
        diagLayout->addWidget(add);

        titleTxt->setText((outputList->item(row, 1))->text());
        authorTxt->setText((outputList->item(row, 2))->text());
        genreTxt->setText((outputList->item(row, 3))->text());
        yearTxt->setText((outputList->item(row, 4))->text());
        QObject::connect(add, &QPushButton::clicked,[&](){
          string title, author, genre;
          int year;
          title = titleTxt->text().toStdString();
          author = authorTxt->text().toStdString();
          genre = genreTxt->text().toStdString();
          year = yearTxt->text().toInt();
          srv.modifyBook(bookID, title, author, genre, year);
          reloadList();
          diag->close();
        });
        diag->exec();
      }
}
