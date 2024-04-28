#include "global_main.h"

#include "select_profession.h"
#include "ui_select_profession.h"


// Include header files for forward declaration
#include "student_login_form.h"
#include "lecturer_login_form.h"


Select_Profession::Select_Profession(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Select_Profession)
{
    ui->setupUi(this);

    // Connect ui objects to functions based on user interaction
    connect(ui->studentButton, &QPushButton::clicked, this, &Select_Profession::switchWindow_StudentLoginForm);
    connect(ui->lecturerButton, &QPushButton::clicked, this, &Select_Profession::switchWindow_LecturerLoginForm);

    // Load window position
    QPoint windowPos = WindowPositionManager::loadWindowPosition();
    windowPos.setY(windowPos.y() - 31);
    move(windowPos);
}


Select_Profession::~Select_Profession()
{
    delete ui;
}


void Select_Profession::switchWindow_StudentLoginForm()
{
    // Switch ui window to Student_Login_Form
    student_login_form = new Student_Login_Form;
    student_login_form->show();
    this->hide();
}


void Select_Profession::switchWindow_LecturerLoginForm()
{
    // Switch ui window to Lecturer_Login_Form
    lecturer_login_form = new Lecturer_Login_Form;
    lecturer_login_form->show();
    this->hide();
}


void Select_Profession::moveEvent(QMoveEvent *event)
{
    // Saves window position every movement instance of a window
    QMainWindow::moveEvent(event);
    WindowPositionManager::saveWindowPosition(event->pos());
}
