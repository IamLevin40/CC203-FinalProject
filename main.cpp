#include "select_profession.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Select_Profession select_profession;
    select_profession.show();
    return a.exec();
}
