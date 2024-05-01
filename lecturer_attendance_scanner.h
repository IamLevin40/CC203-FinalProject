#ifndef LECTURER_ATTENDANCE_SCANNER_H
#define LECTURER_ATTENDANCE_SCANNER_H

#include <QMainWindow>
#include <QMoveEvent>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QtCore>
#include <QtGui>
#include <QCamera>
#include <QtWidgets>
#include <QtMultimedia>
#include <QtMultimediaWidgets>


// Forward declaration of class files
class Lecturer_Home_Qr;
class Lecturer_Classes_List;
class Lecturer_Attendance_List;
class Lecturer_Attendance_Alternative;


namespace Ui {
    class Lecturer_Attendance_Scanner;
}

class Lecturer_Attendance_Scanner : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Lecturer_Attendance_Scanner(QWidget *parent = nullptr);
        ~Lecturer_Attendance_Scanner();
        QString verifiedAuthCode;

    protected:
        void moveEvent(QMoveEvent *event) override;

    private:
        Ui::Lecturer_Attendance_Scanner *ui;
        QSqlDatabase database;

        // Reference the class files here
        Lecturer_Home_Qr *lecturer_home_qr;
        Lecturer_Classes_List *lecturer_classes_list;
        Lecturer_Attendance_List *lecturer_attendance_list;
        Lecturer_Attendance_Alternative *lecturer_attendance_alternative;

        // All custom functions() should be recognized upon here
        void selectClassInfo(const QStringList &keys_classInfo);
        void displayClassInfo(const QStringList &dataList);

        void setCameraScanner();
        void captureQrCall();

        void decodeQrCall();
        QString verifyQrCode(const QStringList &keys_classInfo, const QString &studentId, const QString &lastName, const QString &college,
                             const QString &authCode);
        void selectStudentInfo(const QString &studentId, const QString &lastName, const QString &college,
                               const QString &authCode);
        void displayStudentInfo(const QStringList &dataList);

        void takeAttendanceCall();
        void updateStudentRecord(const QStringList &keys_classInfo, const QStringList &dataList,
                                 const QString &currentDate, const QString &currentTime);

        void switchWindow_LecturerHomeQr();
        void switchWindow_LecturerClassesList();
        void switchWindow_LecturerAttendanceList();
        void switchWindow_LecturerAttendanceAlternative();
};

#endif // LECTURER_ATTENDANCE_SCANNER_H
