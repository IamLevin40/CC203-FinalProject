#include "lecturer_attendance_scanner.h"
#include "ui_lecturer_attendance_scanner.h"

Lecturer_Attendance_Scanner::Lecturer_Attendance_Scanner(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lecturer_Attendance_Scanner)
{
    ui->setupUi(this);
}

Lecturer_Attendance_Scanner::~Lecturer_Attendance_Scanner()
{
    delete ui;
}
