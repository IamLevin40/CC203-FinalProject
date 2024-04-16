#ifndef LECTURER_ATTENDANCE_SCANNER_H
#define LECTURER_ATTENDANCE_SCANNER_H

#include <QMainWindow>

namespace Ui {
class Lecturer_Attendance_Scanner;
}

class Lecturer_Attendance_Scanner : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lecturer_Attendance_Scanner(QWidget *parent = nullptr);
    ~Lecturer_Attendance_Scanner();

private:
    Ui::Lecturer_Attendance_Scanner *ui;
};

#endif // LECTURER_ATTENDANCE_SCANNER_H
