#include "lecturer_student_record.h"
#include "ui_lecturer_student_record.h"

Lecturer_Student_Record::Lecturer_Student_Record(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lecturer_Student_Record)
{
    ui->setupUi(this);
}

Lecturer_Student_Record::~Lecturer_Student_Record()
{
    delete ui;
}
