#ifndef LECTURER_CLASSES_LIST_H
#define LECTURER_CLASSES_LIST_H

#include <QMainWindow>
#include <QMoveEvent>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLayout>
#include <QLayoutItem>


// Forward declaration of class files
class Lecturer_Login_Form;
class Lecturer_Home_Qr;
class Lecturer_Classes_Info;


namespace Ui {
    class Lecturer_Classes_List;
}

class Lecturer_Classes_List : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Lecturer_Classes_List(QWidget *parent = nullptr);
        ~Lecturer_Classes_List();

    protected:
        void moveEvent(QMoveEvent *event) override;

    private:
        Ui::Lecturer_Classes_List *ui;
        QSqlDatabase database;
        QList<QGroupBox*> groupBoxList;

        // Reference the class files here
        Lecturer_Login_Form *lecturer_login_form;
        Lecturer_Home_Qr *lecturer_home_qr;
        Lecturer_Classes_Info *lecturer_classes_info;

        // All custom functions() should be recognized upon here
        void selectLecturerInfo(const QString &key_lecturerId);
        void displayLecturerInfo(const QStringList &dataList);

        void filterSearchCall();
        void selectCorrespondClasses(const int &pageNumber, const QString &lecturerId);
        void displayCorrespondClasses(const QList<QStringList> &dataList);

        void switchWindow_LecturerLoginForm();
        void switchWindow_LecturerHomeQr();
        void switchWindow_LecturerClassesInfo(const QStringList &keys_classInfo);
};

#endif // LECTURER_CLASSES_LIST_H
