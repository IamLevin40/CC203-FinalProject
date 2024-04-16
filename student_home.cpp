#include "student_home.h"
#include "ui_student_home.h"

Student_Home::Student_Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Student_Home)
{
    ui->setupUi(this);
}

Student_Home::~Student_Home()
{
    delete ui;
}
