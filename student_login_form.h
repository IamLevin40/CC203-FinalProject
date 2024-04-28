#ifndef STUDENT_LOGIN_FORM_H
#define STUDENT_LOGIN_FORM_H

#include <QMainWindow>
#include <QMoveEvent>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


// Forward declaration of class files
class Select_Profession;
class Student_Home;


namespace Ui {
    class Student_Login_Form;
}

class Student_Login_Form : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Student_Login_Form(QWidget *parent = nullptr);
        ~Student_Login_Form();

    protected:
        void moveEvent(QMoveEvent *event) override;

    private:
        Ui::Student_Login_Form *ui;
        QSqlDatabase database;

        // Reference the class files here
        Select_Profession *select_profession;
        Student_Home *student_home;

        // All custom functions() should be recognized upon here
        void loginCall();
        QString authenticateStudent(const QString &studentId, const QString &pin, const QString &college);
        void populateCombobox();
        void switchWindow_SelectProfession();
        void switchWindow_StudentHome(const QString &studentId);
};

#endif // STUDENT_LOGIN_FORM_H
