#ifndef LECTURER_ATTENDANCE_LIST_H
#define LECTURER_ATTENDANCE_LIST_H

#include <QMainWindow>

namespace Ui {
class Lecturer_Attendance_List;
}

class Lecturer_Attendance_List : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lecturer_Attendance_List(QWidget *parent = nullptr);
    ~Lecturer_Attendance_List();

private:
    Ui::Lecturer_Attendance_List *ui;
};

#endif // LECTURER_ATTENDANCE_LIST_H
