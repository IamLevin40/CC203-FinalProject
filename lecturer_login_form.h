#ifndef LECTURER_LOGIN_FORM_H
#define LECTURER_LOGIN_FORM_H

#include <QMainWindow>
#include <QMoveEvent>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


// Forward declaration of class files
class Select_Profession;
class Lecturer_Home;


namespace Ui {
    class Lecturer_Login_Form;
}

class Lecturer_Login_Form : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Lecturer_Login_Form(QWidget *parent = nullptr);
        ~Lecturer_Login_Form();

    protected:
        void moveEvent(QMoveEvent *event) override;

    private:
        Ui::Lecturer_Login_Form *ui;
        QSqlDatabase database;

        // Reference the class files here
        Select_Profession *select_profession;
        Lecturer_Home *lecturer_home;

        // All custom functions() should be recognized upon here
        void loginCall();
        QString authenticateLecturer(const QString &lecturerId, const QString &pin, const QString college);
        void populateCombobox();
        void switchWindow_SelectProfession();
        void switchWindow_LecturerHome(const QString &lecturerId);
};

#endif // LECTURER_LOGIN_FORM_H
