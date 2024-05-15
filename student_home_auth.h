#ifndef STUDENT_HOME_AUTH_H
#define STUDENT_HOME_AUTH_H

#include <QMainWindow>
#include <QMoveEvent>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


// Forward declaration of class files
class Student_Login_Form;
class Student_Home_Qr;


namespace Ui {
    class Student_Home_Auth;
}

class Student_Home_Auth : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Student_Home_Auth(QWidget *parent = nullptr);
        ~Student_Home_Auth();

    protected:
        void moveEvent(QMoveEvent *event) override;

    private:
        Ui::Student_Home_Auth *ui;
        QSqlDatabase database;

        // Reference the class files here
        Student_Login_Form *student_login_form;
        Student_Home_Qr *student_home_qr;

        // All custom functions() should be recognized upon here
        void selectStudentInfo(const QString &key_studentId);
        void displayStudentInfo(const QStringList &dataList);

        void displayAuthInfo(const QStringList &dataList);

        void switchWindow_StudentLoginForm();
        void switchWindow_StudentHomeQr();
};

#endif // STUDENT_HOME_AUTH_H


/*
 *   Copyright (c) 2024 - WVSU-CICT BSCS 1B: Batch 2027
 *   All rights reserved.
 */
