#ifndef LECTURER_LOGIN_FORM_H
#define LECTURER_LOGIN_FORM_H

#include <QMainWindow>

namespace Ui {
class Lecturer_Login_Form;
}

class Lecturer_Login_Form : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lecturer_Login_Form(QWidget *parent = nullptr);
    ~Lecturer_Login_Form();

private slots:
    void on_backButton_clicked();

private:
    Ui::Lecturer_Login_Form *ui;

};

#endif // LECTURER_LOGIN_FORM_H
