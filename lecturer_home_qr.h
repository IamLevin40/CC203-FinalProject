#ifndef LECTURER_HOME_QR_H
#define LECTURER_HOME_QR_H

#include <QMainWindow>
#include <QMoveEvent>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QrCodeGenerator.h>


// Forward declaration of class files
class Lecturer_Login_Form;
class Lecturer_Classes_List;
class Lecturer_Home_Auth;


namespace Ui {
    class Lecturer_Home_Qr;
}

    class Lecturer_Home_Qr : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit Lecturer_Home_Qr(QWidget *parent = nullptr);
        ~Lecturer_Home_Qr();

    protected:
        void moveEvent(QMoveEvent *event) override;

    private:
        Ui::Lecturer_Home_Qr *ui;
        QSqlDatabase database;
        QrCodeGenerator qrGenerator;

        // Reference the class files here
        Lecturer_Login_Form *lecturer_login_form;
        Lecturer_Classes_List *lecturer_classes_list;
        Lecturer_Home_Auth *lecturer_home_auth;

        // All custom functions() should be recognized upon here
        void selectLecturerInfo(const QString &key_lecturerId);
        void displayLecturerInfo(const QStringList &dataList);

        void displayQrInfo(const QStringList &dataList);
        void generateQr(const QStringList &dataList);

        void switchWindow_LecturerLoginForm();
        void switchWindow_LecturerClassesList();
        void switchWindow_LecturerHomeAuth();
};

#endif // LECTURER_HOME_QR_H
