#include "lecturer_classes_list.h"
#include "ui_lecturer_classes_list.h"

Lecturer_Classes_List::Lecturer_Classes_List(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lecturer_Classes_List)
{
    ui->setupUi(this);
}

Lecturer_Classes_List::~Lecturer_Classes_List()
{
    delete ui;
}
