#include "select_profession.h"
#include "ui_select_profession.h"

Select_Profession::Select_Profession(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Select_Profession)
{
    ui->setupUi(this);
}

Select_Profession::~Select_Profession()
{
    delete ui;
}

void Select_Profession::on_studentButton_clicked()
{
    hide();
    student_login_form_ui = new Student_Login_Form(this);
    student_login_form_ui->show();
}


void Select_Profession::on_lecturerButton_clicked()
{
    hide();
    lecturer_login_form_ui = new Lecturer_Login_Form(this);
    lecturer_login_form_ui->show();
}

