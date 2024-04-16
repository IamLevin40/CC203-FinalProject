#include "lecturer_classes_info.h"
#include "ui_lecturer_classes_info.h"

Lecturer_Classes_Info::Lecturer_Classes_Info(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lecturer_Classes_Info)
{
    ui->setupUi(this);
}

Lecturer_Classes_Info::~Lecturer_Classes_Info()
{
    delete ui;
}
