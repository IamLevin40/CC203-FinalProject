#ifndef LECTURER_ATTENDANCE_ALTERNATIVE_H
#define LECTURER_ATTENDANCE_ALTERNATIVE_H

#include <QMainWindow>
#include <QMoveEvent>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


// Forward declaration of class files
class Lecturer_Home_Qr;
class Lecturer_Classes_List;
class Lecturer_Attendance_List;
class Lecturer_Attendance_Scanner;


namespace Ui {
    class Lecturer_Attendance_Alternative;
}

class Lecturer_Attendance_Alternative : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Lecturer_Attendance_Alternative(QWidget *parent = nullptr);
        ~Lecturer_Attendance_Alternative();
        QString verifiedAuthCode;

    protected:
        void moveEvent(QMoveEvent *event) override;

    private:
        Ui::Lecturer_Attendance_Alternative *ui;
        QSqlDatabase database;

        // Reference the class files here
        Lecturer_Home_Qr *lecturer_home_qr;
        Lecturer_Classes_List *lecturer_classes_list;
        Lecturer_Attendance_List *lecturer_attendance_list;
        Lecturer_Attendance_Scanner *lecturer_attendance_scanner;

        // All custom functions() should be recognized upon here
        void selectClassInfo(const QStringList &keys_classInfo);
        void displayClassInfo(const QStringList &dataList);

        void verifyAuthCodeCall();
        QString authenticateStudent(const QStringList &keys_classInfo, const QString &authCode);
        void selectStudentInfo(const QString &authCode);
        void displayStudentInfo(const QStringList &dataList);

        void takeAttendanceCall();
        void updateStudentRecord(const QStringList &keys_classInfo, const QString &studentId,
                                 const QString &currentDate, const QString &currentTime);

        void switchWindow_LecturerHomeQr();
        void switchWindow_LecturerClassesList();
        void switchWindow_LecturerAttendanceList();
        void switchWindow_LecturerAttendanceScanner();
};

#endif // LECTURER_ATTENDANCE_ALTERNATIVE_H
