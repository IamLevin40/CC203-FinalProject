#ifndef LECTURER_CLASSES_INFO_H
#define LECTURER_CLASSES_INFO_H

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
class Lecturer_Student_Record;


namespace Ui {
    class Lecturer_Classes_Info;
}

class Lecturer_Classes_Info : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Lecturer_Classes_Info(QWidget *parent = nullptr);
        ~Lecturer_Classes_Info();

    protected:
        void moveEvent(QMoveEvent *event) override;

    private:
        Ui::Lecturer_Classes_Info *ui;
        QSqlDatabase database;

        // Reference the class files here
        Lecturer_Home_Qr *lecturer_home_qr;
        Lecturer_Classes_List *lecturer_classes_list;
        Lecturer_Attendance_List *lecturer_attendance_list;
        Lecturer_Student_Record *lecturer_student_record;

        // All custom functions() should be recognized upon here
        void selectInfoFromDatabase(const QString &key_lecturerId);
        void displayInfoFromDatabase(const QStringList &dataList);

        void selectDataFromDatabase(const QStringList &keys_classInfo);
        void displayDataFromDatabase(const QStringList &dataList);

        void switchWindow_LecturerHomeQr();
        void switchWindow_LecturerClassesList();
        void switchWindow_LecturerAttendanceList();
        void switchWindow_LecturerStudentRecord();
};

#endif // LECTURER_CLASSES_INFO_H
