#include "lecturer_attendance_list.h"
#include "lecturer_attendance_scanner.h"
#include "lecturer_classes_info.h"
#include "lecturer_classes_list.h"
#include "lecturer_home.h"
#include "lecturer_login_form.h"
#include "lecturer_student_record.h"
#include "select_profession.h"
#include "student_home.h"
#include "student_login_form.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Select_Profession w;
    w.show();
    return a.exec();
}
