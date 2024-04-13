#include "student_login_form.h"
#include "ui_student_login_form.h"

#include "select_profession.h"
MainWindow *main;

Student_Login_Form::Student_Login_Form(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Student_Login_Form)
{
    ui->setupUi(this);
}

Student_Login_Form::~Student_Login_Form()
{
    delete ui;
}

void Student_Login_Form::on_backButton_clicked()
{

    // Hide the previous ui.
    hide();

    // Show the ui of Student_Login_Form
    main = new MainWindow(this);
    main->show();

}

