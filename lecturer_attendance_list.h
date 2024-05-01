#ifndef LECTURER_ATTENDANCE_LIST_H
#define LECTURER_ATTENDANCE_LIST_H

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
class Lecturer_Home_Qr;
class Lecturer_Classes_List;
class Lecturer_Classes_Info;
class Lecturer_Attendance_Scanner;


namespace Ui {
    class Lecturer_Attendance_List;
}

class Lecturer_Attendance_List : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Lecturer_Attendance_List(QWidget *parent = nullptr);
        ~Lecturer_Attendance_List();

    protected:
        void moveEvent(QMoveEvent *event) override;

    private:
        Ui::Lecturer_Attendance_List *ui;
        QSqlDatabase database;
        QList<QGroupBox*> groupBoxList;

        // Reference the class files here
        Lecturer_Home_Qr *lecturer_home_qr;
        Lecturer_Classes_List *lecturer_classes_list;
        Lecturer_Classes_Info *lecturer_classes_info;
        Lecturer_Attendance_Scanner *lecturer_attendance_scanner;

        // All custom functions() should be recognized upon here
        void selectClassInfo(const QStringList &keys_classInfo);
        void displayClassInfo(const QStringList &dataList);

        void filterSearchCall();
        void selectAttendedStudents(const int &pageNumber, const QStringList &keys_classInfo, const QString &currentDate);
        void displayAttendedStudents(const QList<QStringList> &dataList, const QList<QStringList> &recordList);

        void switchWindow_LecturerHomeQr();
        void switchWindow_LecturerClassesList();
        void switchWindow_LecturerClassesInfo();
        void switchWindow_LecturerAttendanceScanner();
};

#endif // LECTURER_ATTENDANCE_LIST_H
