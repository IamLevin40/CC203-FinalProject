#ifndef SELECT_PROFESSION_H
#define SELECT_PROFESSION_H

#include <QMainWindow>
#include <QMoveEvent>


// Forward declaration of class files
class Student_Login_Form;
class Lecturer_Login_Form;


namespace Ui {
    class Select_Profession;
}

class Select_Profession : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Select_Profession(QWidget *parent = nullptr);
        ~Select_Profession();

    protected:
        void moveEvent(QMoveEvent *event) override;

    private:
        Ui::Select_Profession *ui;

        // Reference the class files here
        Student_Login_Form *student_login_form;
        Lecturer_Login_Form *lecturer_login_form;

        // All custom functions() should be recognized upon here
        void switchWindow_StudentLoginForm();
        void switchWindow_LecturerLoginForm();
};

#endif // SELECT_PROFESSION_H
