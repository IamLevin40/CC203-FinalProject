#ifndef STUDENT_HOME_H
#define STUDENT_HOME_H

#include <QMainWindow>
#include <QMoveEvent>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QrCodeGenerator.h>


// Forward declaration of class files
class Student_Login_Form;


namespace Ui {
    class Student_Home;
}

class Student_Home : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Student_Home(QWidget *parent = nullptr);
        ~Student_Home();

    protected:
        void moveEvent(QMoveEvent *event) override;

    private:
        Ui::Student_Home *ui;
        QSqlDatabase database;
        QrCodeGenerator qrGenerator;

        // Reference the class files here
        Student_Login_Form *student_login_form;

        // All custom functions() should be recognized upon here
        void selectInfoFromDatabase(const QString &key_studentId);
        void displayInfoFromDatabase(const QStringList &dataList);
        void displayDataFromDatabase(const QStringList &dataList);
        void generateQr(const QStringList &dataList);
        void switchWindow_StudentLoginForm();
};

#endif // STUDENT_HOME_H
