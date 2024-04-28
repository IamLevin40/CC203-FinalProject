#ifndef LECTURER_HOME_H
#define LECTURER_HOME_H

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


namespace Ui {
    class Lecturer_Home;
}

    class Lecturer_Home : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit Lecturer_Home(QWidget *parent = nullptr);
        ~Lecturer_Home();

    protected:
        void moveEvent(QMoveEvent *event) override;

    private:
        Ui::Lecturer_Home *ui;
        QSqlDatabase database;
        QrCodeGenerator qrGenerator;

        // Reference the class files here
        Lecturer_Login_Form *lecturer_login_form;
        Lecturer_Classes_List *lecturer_classes_list;

        // All custom functions() should be recognized upon here
        void selectInfoFromDatabase(const QString &key_lecturerId);
        void displayInfoFromDatabase(const QStringList &dataList);
        void displayDataFromDatabase(const QStringList &dataList);
        void generateQr(const QStringList &dataList);
        void switchWindow_LecturerLoginForm();
        void switchWindow_LecturerClassesList();
};

#endif // LECTURER_HOME_H
