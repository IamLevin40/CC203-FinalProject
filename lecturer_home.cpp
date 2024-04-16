#include "lecturer_home.h"
#include "ui_lecturer_home.h"

Lecturer_Home::Lecturer_Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lecturer_Home)
{
    ui->setupUi(this);
}

Lecturer_Home::~Lecturer_Home()
{
    delete ui;
}
