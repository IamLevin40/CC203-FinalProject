#ifndef LECTURER_ATTENDANCE_ALTERNATIVE_H
#define LECTURER_ATTENDANCE_ALTERNATIVE_H

#include <QMainWindow>

namespace Ui {
class Lecturer_Attendance_Alternative;
}

class Lecturer_Attendance_Alternative : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lecturer_Attendance_Alternative(QWidget *parent = nullptr);
    ~Lecturer_Attendance_Alternative();

private:
    Ui::Lecturer_Attendance_Alternative *ui;
};

#endif // LECTURER_ATTENDANCE_ALTERNATIVE_H
