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


namespace Ui {
    class Lecturer_Attendance_Scanner;
}

class Lecturer_Attendance_Scanner : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Lecturer_Attendance_Scanner(QWidget *parent = nullptr);
        ~Lecturer_Attendance_Scanner();

    protected:
        void moveEvent(QMoveEvent *event) override;

    private:
        Ui::Lecturer_Attendance_Scanner *ui;
        QSqlDatabase database;

        // Reference the class files here
        Lecturer_Home_Qr *lecturer_home_qr;
        Lecturer_Classes_List *lecturer_classes_list;
        Lecturer_Attendance_List *lecturer_attendance_list;

        // All custom functions() should be recognized upon here
        void selectInfoFromDatabase(const QStringList &keys_classInfo);
        void displayInfoFromDatabase(const QStringList &dataList);

        void setCameraScanner();
        void captureQrCall();

        void decodeQrCall();
        QString verifyQrCode(const QString &studentId, const QString &lastName, const QString &college);
        void displayDataFromDatabase(const QStringList &dataList);

        void takeAttendanceCall();
        void updateDataFromDatabase(const QStringList &keys_classInfo, const QStringList &dataList);

        void switchWindow_LecturerHomeQr();
        void switchWindow_LecturerClassesList();
        void switchWindow_LecturerAttendanceList();
};

#endif // LECTURER_ATTENDANCE_SCANNER_H
