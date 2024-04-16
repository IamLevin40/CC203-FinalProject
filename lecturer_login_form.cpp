#include "lecturer_login_form.h"
#include "ui_lecturer_login_form.h"

Lecturer_Login_Form::Lecturer_Login_Form(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lecturer_Login_Form)
{
    ui->setupUi(this);
}

Lecturer_Login_Form::~Lecturer_Login_Form()
{
    delete ui;
}

void Lecturer_Login_Form::on_backButton_clicked()
{

}

