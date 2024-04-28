#include "global_main.h"

#include "lecturer_attendance_scanner.h"
#include "ui_lecturer_attendance_scanner.h"


// Include header files for forward declaration
#include "lecturer_home.h"
#include "lecturer_classes_list.h"
#include "lecturer_attendance_list.h"


Lecturer_Attendance_Scanner::Lecturer_Attendance_Scanner(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lecturer_Attendance_Scanner)
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
    Lecturer_Attendance_Scanner::selectInfoFromDatabase($selectKeys_classInfo);
    Lecturer_Attendance_Scanner::scanQrCall();

    // Connect ui objects to functions based on user interaction
    connect(ui->confirmButton, &QPushButton::clicked, this, &Lecturer_Attendance_Scanner::takeAttendanceCall);
    ui->confirmButton->setEnabled(false);

    connect(ui->backButton, &QPushButton::clicked, this, &Lecturer_Attendance_Scanner::switchWindow_LecturerAttendanceList);
    connect(ui->homeButton, &QPushButton::clicked, this, &Lecturer_Attendance_Scanner::switchWindow_LecturerHome);
    connect(ui->classListButton, &QPushButton::clicked, this, &Lecturer_Attendance_Scanner::switchWindow_LecturerClassesList);

    // Load window position
    QPoint windowPos = WindowPositionManager::loadWindowPosition();
    windowPos.setY(windowPos.y() - 31);
    move(windowPos);
}


Lecturer_Attendance_Scanner::~Lecturer_Attendance_Scanner()
{
    delete ui;
}


void Lecturer_Attendance_Scanner::selectInfoFromDatabase(const QStringList &keys_classInfo)
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
    query.prepare("SELECT SubjectCode, SubjectDesc, Program, Year, Section FROM ClassInfo WHERE \
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
    classDataList << query.value(2).toString();     // Program
    classDataList << query.value(3).toString();     // Year
    classDataList << query.value(4).toString();     // Section

    // Close the database after using
    QSqlDatabase::database().commit();
    database.close();

    // Proceed to display data list
    Lecturer_Attendance_Scanner::displayInfoFromDatabase(classDataList);
}


void Lecturer_Attendance_Scanner::displayInfoFromDatabase(const QStringList &dataList)
{
    // Assign members from dataList to variables
    QString subjectCode = dataList[0];
    QString subjectDesc = dataList[1];
    QString program = dataList[2];
    QString year = dataList[3];
    QString section = dataList[4];

    // Display class information
    ui->headerSubjectCodeLabel->setText(subjectCode);
    ui->headerSubjectDescLabel->setText(subjectDesc);
    ui->headerProgramLabel->setText(QString("%1 %2%3").arg(program, year, section));
}


void Lecturer_Attendance_Scanner::scanQrCall()
{

}


QString Lecturer_Attendance_Scanner::verifyQrCode(const QString &qrData)
{

}


void Lecturer_Attendance_Scanner::selectDataFromDatabase(const QString &qrData)
{

}


void Lecturer_Attendance_Scanner::displayDataFromDatabase(const QStringList &dataList)
{

}


void Lecturer_Attendance_Scanner::takeAttendanceCall()
{

}


void Lecturer_Attendance_Scanner::updateDataFromDatabase(const QStringList &keys_classInfo, const QStringList &dataList)
{

}


void Lecturer_Attendance_Scanner::switchWindow_LecturerHome()
{
    // Switch ui window to Lecturer_Home
    lecturer_home = new Lecturer_Home;
    lecturer_home->show();
    this->hide();
}


void Lecturer_Attendance_Scanner::switchWindow_LecturerClassesList()
{
    // Switch ui window to Lecturer_Classes_List
    lecturer_classes_list = new Lecturer_Classes_List;
    lecturer_classes_list->show();
    this->hide();
}


void Lecturer_Attendance_Scanner::switchWindow_LecturerAttendanceList()
{
    // Switch ui window to Lecturer_Attendance_List
    lecturer_attendance_list = new Lecturer_Attendance_List;
    lecturer_attendance_list->show();
    this->hide();
}


void Lecturer_Attendance_Scanner::moveEvent(QMoveEvent *event)
{
    // Saves window position every movement instance of a window
    QMainWindow::moveEvent(event);
    WindowPositionManager::saveWindowPosition(event->pos());
}
