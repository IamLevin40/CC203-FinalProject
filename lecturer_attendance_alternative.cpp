#include "lecturer_attendance_alternative.h"
#include "ui_lecturer_attendance_alternative.h"

Lecturer_Attendance_Alternative::Lecturer_Attendance_Alternative(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lecturer_Attendance_Alternative)
{
    ui->setupUi(this);
}

Lecturer_Attendance_Alternative::~Lecturer_Attendance_Alternative()
{
    delete ui;
}
