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
class Student_Home_Qr;


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
        Student_Home_Qr *student_home_qr;

        // All custom functions() should be recognized upon here
        void loginCall();
        QString authenticateStudent(const QString &studentId, const QString &pin, const QString &college);
        void updateAuthCode(const QString &studentId);

        void populateCombobox();

        void switchWindow_SelectProfession();
        void switchWindow_StudentHomeQr(const QString &studentId);
};

#endif // STUDENT_LOGIN_FORM_H


/*
 *   Copyright (c) 2024 - WVSU-CICT BSCS 1B: Batch 2027
 *   All rights reserved.
 */
