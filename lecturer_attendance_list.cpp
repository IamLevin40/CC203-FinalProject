#include "lecturer_attendance_list.h"
#include "ui_lecturer_attendance_list.h"

Lecturer_Attendance_List::Lecturer_Attendance_List(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lecturer_Attendance_List)
{
    ui->setupUi(this);
}

Lecturer_Attendance_List::~Lecturer_Attendance_List()
{
    delete ui;
}
