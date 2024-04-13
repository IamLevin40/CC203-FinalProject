#ifndef STUDENT_LOGIN_FORM_H
#define STUDENT_LOGIN_FORM_H

#include <QMainWindow>

namespace Ui {
class Student_Login_Form;
}

class Student_Login_Form : public QMainWindow
{
    Q_OBJECT

public:
    explicit Student_Login_Form(QWidget *parent = nullptr);
    ~Student_Login_Form();

private slots:
    void on_backButton_clicked();

private:
    Ui::Student_Login_Form *ui;

};

#endif // STUDENT_LOGIN_FORM_H
