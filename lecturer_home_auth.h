#ifndef LECTURER_HOME_AUTH_H
#define LECTURER_HOME_AUTH_H

#include <QMainWindow>
#include <QMoveEvent>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


// Forward declaration of class files
class Lecturer_Login_Form;
class Lecturer_Classes_List;
class Lecturer_Home_Qr;


namespace Ui {
    class Lecturer_Home_Auth;
}

class Lecturer_Home_Auth : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Lecturer_Home_Auth(QWidget *parent = nullptr);
        ~Lecturer_Home_Auth();

    protected:
        void moveEvent(QMoveEvent *event) override;

    private:
        Ui::Lecturer_Home_Auth *ui;
        QSqlDatabase database;

        // Reference the class files here
        Lecturer_Login_Form *lecturer_login_form;
        Lecturer_Classes_List *lecturer_classes_list;
        Lecturer_Home_Qr *lecturer_home_qr;

        // All custom functions() should be recognized upon here
        void selectLecturerInfo(const QString &key_lecturerId);
        void displayLecturerInfo(const QStringList &dataList);

        void displayAuthInfo(const QStringList &dataList);

        void switchWindow_LecturerLoginForm();
        void switchWindow_LecturerClassesList();
        void switchWindow_LecturerHomeQr();
};

#endif // LECTURER_HOME_AUTH_H
