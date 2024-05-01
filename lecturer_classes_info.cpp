#include "global_main.h"

#include "lecturer_classes_info.h"
#include "ui_lecturer_classes_info.h"


// Include header files for forward declaration
#include "lecturer_home_qr.h"
#include "lecturer_classes_list.h"
#include "lecturer_attendance_list.h"
#include "lecturer_student_record.h"


Lecturer_Classes_Info::Lecturer_Classes_Info(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lecturer_Classes_Info)
{
    ui->setupUi(this);

    // Set up sql online database with connection parameters
    database = QSqlDatabase::addDatabase($sql_Driver);
    database.setHostName($db_Hostname);
    database.setUserName($db_Username);
    database.setPassword($db_Password);
    database.setDatabaseName($db_Database);
    database.setPort($db_Port);

    // Initiate functions on awake
    Lecturer_Classes_Info::selectLecturerInfo($logKey_lecturerId);
    Lecturer_Classes_Info::selectPickedClass($selectKeys_classInfo);
    DateTimeUtils::updateDateTimeUtils(ui->dateLabel, ui->timeLabel);

    // Connect ui objects to functions based on user interaction
    connect(ui->backButton, &QPushButton::clicked, this, &Lecturer_Classes_Info::switchWindow_LecturerClassesList);
    connect(ui->homeButton, &QPushButton::clicked, this, &Lecturer_Classes_Info::switchWindow_LecturerHomeQr);
    connect(ui->classListButton, &QPushButton::clicked, this, &Lecturer_Classes_Info::switchWindow_LecturerClassesList);
    connect(ui->attendanceButton, &QPushButton::clicked, this, &Lecturer_Classes_Info::switchWindow_LecturerAttendanceList);
    connect(ui->studentRecordButton, &QPushButton::clicked, this, &Lecturer_Classes_Info::switchWindow_LecturerStudentRecord);

    // Load window position
    QPoint windowPos = WindowPositionManager::loadWindowPosition();
    windowPos.setY(windowPos.y() - 31);
    move(windowPos);
}


Lecturer_Classes_Info::~Lecturer_Classes_Info()
{
    delete ui;
}


void Lecturer_Classes_Info::selectLecturerInfo(const QString &key_lecturerId)
{
    // Return error if unable to access the database
    if (!database.open())
    {
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }

    // Set up data list and queries for database
    QStringList lecturerDataList;
    QSqlDatabase::database().transaction();
    QSqlQuery query(database);


    // Prepare sql command for selecting data
    query.prepare("SELECT * FROM LecturerInfo WHERE LecturerId = :lecturerId");

    // Bind values to the query
    query.bindValue(":lecturerId", key_lecturerId);

    // Return error if unable to select data
    if (!query.exec())
    {
        QSqlDatabase::database().rollback();
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }

    // Fetch and store data
    query.next();
    lecturerDataList << query.value(0).toString();      // LecturerId
    lecturerDataList << query.value(1).toString();      // Pin
    lecturerDataList << query.value(2).toString();      // LastName
    lecturerDataList << query.value(3).toString();      // FirstName
    lecturerDataList << query.value(4).toString();      // College

    // Close the database after using
    QSqlDatabase::database().commit();
    database.close();

    // Proceed to display data list
    Lecturer_Classes_Info::displayLecturerInfo(lecturerDataList);
}


void Lecturer_Classes_Info::displayLecturerInfo(const QStringList &dataList)
{
    // Assign members from dataList to variables
    QString lastName = dataList[2];
    QString college = dataList[4];

    // Display lecturer information in the header
    ui->headerWelcomeLabel->setText(QString("Hello, %1").arg(lastName));
    ui->headerCollegeLabel->setText(college);
    ui->headerLecturerIdLabel->setText("LN: ****");
    ui->headerAvatarLabel->setPixmap(QPixmap(QString(":/res/assets/%1_avatar.png").arg(college.toLower())));
}


void Lecturer_Classes_Info::selectPickedClass(const QStringList &keys_classInfo)
{
    // Return error if unable to access the database
    if (!database.open())
    {
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }

    // Separate keys onto different key variables
    QString key_subjectCode = keys_classInfo[0];
    QString key_program = keys_classInfo[1];
    QString key_year = keys_classInfo[2];
    QString key_section = keys_classInfo[3];
    QString key_semester = keys_classInfo[4];
    QString key_schoolYear = keys_classInfo[5];

    // Set up data list and queries for database
    QStringList classDataList;
    QSqlDatabase::database().transaction();
    QSqlQuery query(database);

    // Prepare sql command for selecting data
    query.prepare("SELECT * FROM ClassInfo WHERE \
                  SubjectCode = :subjectCode AND \
                  Program = :program AND \
                  Year = :year AND \
                  Section = :section AND \
                  Semester = :semester AND \
                  SchoolYear = :schoolYear");

    // Bind values to the query
    query.bindValue(":subjectCode", key_subjectCode);
    query.bindValue(":program", key_program);
    query.bindValue(":year", key_year);
    query.bindValue(":section", key_section);
    query.bindValue(":semester", key_semester);
    query.bindValue(":schoolYear", key_schoolYear);

    // Return error if unable to select data
    if (!query.exec())
    {
        QSqlDatabase::database().rollback();
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }

    // Fetch and store data
    query.next();
    classDataList << query.value(0).toString();     // SubjectCode
    classDataList << query.value(1).toString();     // SubjectDesc
    classDataList << query.value(2).toString();     // SchoolYear
    classDataList << query.value(3).toString();     // Semester
    classDataList << query.value(4).toString();     // Program
    classDataList << query.value(5).toString();     // Year
    classDataList << query.value(6).toString();     // Section
    classDataList << query.value(7).toString();     // Day
    classDataList << query.value(8).toString();     // Time
    classDataList << query.value(9).toString();     // Room
    classDataList << query.value(10).toString();    // LecturerId

    // Close the database after using
    QSqlDatabase::database().commit();
    database.close();

    // Proceed to display data list
    Lecturer_Classes_Info::displayPickedClass(classDataList);
}


void Lecturer_Classes_Info::displayPickedClass(const QStringList &dataList)
{
    // Assign members from dataList to variables
    QString subjectCode = dataList[0];
    QString subjectDesc = dataList[1];
    QString schoolYear = dataList[2];
    QString semester = dataList[3];
    QString program = dataList[4];
    QString year = dataList[5];
    QString section = dataList[6];
    QString day = dataList[7];
    QString time = dataList[8];
    QString room = dataList[9];

    // Display class information
    ui->subjectCodeLabel->setText(StringManipulator::separateSubjectCode(subjectCode));
    ui->subjectDescLabel->setText(subjectDesc);
    ui->schoolYearLabel->setText(QString("SY %1   SEM %2").arg(schoolYear, semester));
    ui->programLabel->setText(QString("%1 %2%3").arg(program, year, section));
    ui->scheduleLabel->setText(QString("%1   %2").arg(day, time));
    ui->roomLabel->setText(room);
}


void Lecturer_Classes_Info::switchWindow_LecturerHomeQr()
{
    // Switch ui window to Lecturer_Home_Qr
    lecturer_home_qr = new Lecturer_Home_Qr;
    lecturer_home_qr->show();
    this->hide();
}


void Lecturer_Classes_Info::switchWindow_LecturerClassesList()
{
    // Switch ui window to Lecturer_Classes_List
    lecturer_classes_list = new Lecturer_Classes_List;
    lecturer_classes_list->show();
    this->hide();
}


void Lecturer_Classes_Info::switchWindow_LecturerAttendanceList()
{
    // Switch ui window to Lecturer_Attendance_List
    lecturer_attendance_list = new Lecturer_Attendance_List;
    lecturer_attendance_list->show();
    this->hide();
}


void Lecturer_Classes_Info::switchWindow_LecturerStudentRecord()
{
    // Switch ui window to Lecturer_Student_Record
    lecturer_student_record = new Lecturer_Student_Record;
    lecturer_student_record->show();
    this->hide();
}


void Lecturer_Classes_Info::moveEvent(QMoveEvent *event)
{
    // Saves window position every movement instance of a window
    QMainWindow::moveEvent(event);
    WindowPositionManager::saveWindowPosition(event->pos());
}
