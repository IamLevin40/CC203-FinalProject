#ifndef STUDENT_HOME_QR_H
#define STUDENT_HOME_QR_H

#include <QMainWindow>
#include <QMoveEvent>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QrCodeGenerator.h>


// Forward declaration of class files
class Student_Login_Form;
class Student_Home_Auth;


namespace Ui {
    class Student_Home_Qr;
}

class Student_Home_Qr : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Student_Home_Qr(QWidget *parent = nullptr);
        ~Student_Home_Qr();

    protected:
        void moveEvent(QMoveEvent *event) override;

    private:
        Ui::Student_Home_Qr *ui;
        QSqlDatabase database;
        QrCodeGenerator qrGenerator;

        // Reference the class files here
        Student_Login_Form *student_login_form;
        Student_Home_Auth *student_home_auth;

        // All custom functions() should be recognized upon here
        void selectInfoFromDatabase(const QString &key_studentId);
        void displayInfoFromDatabase(const QStringList &dataList);

        void displayDataFromDatabase(const QStringList &dataList);
        void generateQr(const QStringList &dataList);

        void switchWindow_StudentLoginForm();
        void switchWindow_StudentHomeAuth();
};

#endif // STUDENT_HOME_QR_H
