#ifndef LECTURER_CLASSES_LIST_H
#define LECTURER_CLASSES_LIST_H

#include <QMainWindow>

namespace Ui {
class Lecturer_Classes_List;
}

class Lecturer_Classes_List : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lecturer_Classes_List(QWidget *parent = nullptr);
    ~Lecturer_Classes_List();

private:
    Ui::Lecturer_Classes_List *ui;
};

#endif // LECTURER_CLASSES_LIST_H
