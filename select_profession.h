#ifndef SELECT_PROFESSION_H
#define SELECT_PROFESSION_H

#include <QMainWindow>
#include "student_login_form.h"
#include "lecturer_login_form.h"

namespace Ui {
class Select_Profession;
}

class Select_Profession : public QMainWindow
{
    Q_OBJECT

public:
    explicit Select_Profession(QWidget *parent = nullptr);
    ~Select_Profession();

private slots:
    void on_studentButton_clicked();
    void on_lecturerButton_clicked();

private:
    Ui::Select_Profession *ui;
    Student_Login_Form *student_login_form_ui;
    Lecturer_Login_Form *lecturer_login_form_ui;
};

#endif // SELECT_PROFESSION_H
