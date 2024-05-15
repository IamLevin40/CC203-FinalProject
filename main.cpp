#include "global_main.h"
#include "lecturer_attendance_list.h"
#include "lecturer_attendance_scanner.h"
#include "lecturer_classes_info.h"
#include "lecturer_classes_list.h"
#include "lecturer_home_qr.h"
#include "lecturer_login_form.h"
#include "lecturer_student_record.h"
#include "select_profession.h"
#include "student_home_qr.h"
#include "student_login_form.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Select_Profession w;
    w.show();

    return a.exec();
}


/*
 *   Copyright (c) 2024 - WVSU-CICT BSCS 1B: Batch 2027
 *   All rights reserved.
 */
