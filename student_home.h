#ifndef STUDENT_HOME_H
#define STUDENT_HOME_H

#include <QMainWindow>

namespace Ui {
class Student_Home;
}

class Student_Home : public QMainWindow
{
    Q_OBJECT

public:
    explicit Student_Home(QWidget *parent = nullptr);
    ~Student_Home();

private:
    Ui::Student_Home *ui;
};

#endif // STUDENT_HOME_H
