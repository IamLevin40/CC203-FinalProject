#include "global_main.h"

#include "lecturer_attendance_alternative.h"
#include "ui_lecturer_attendance_alternative.h"


// Include header files for forward declaration
#include "lecturer_home_qr.h"
#include "lecturer_classes_list.h"
#include "lecturer_attendance_list.h"
#include "lecturer_attendance_scanner.h"


Lecturer_Attendance_Alternative::Lecturer_Attendance_Alternative(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lecturer_Attendance_Alternative)
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
    Lecturer_Attendance_Alternative::selectClassInfo($selectKeys_classInfo);

    // Connect ui objects to functions based on user interaction
    connect(ui->verifyButton, &QPushButton::clicked, this, &Lecturer_Attendance_Alternative::verifyAuthCodeCall);
    connect(ui->confirmButton, &QPushButton::clicked, this, &Lecturer_Attendance_Alternative::takeAttendanceCall);
    ui->confirmButton->setEnabled(false);

    connect(ui->backButton, &QPushButton::clicked, this, &Lecturer_Attendance_Alternative::switchWindow_LecturerAttendanceScanner);
    connect(ui->homeButton, &QPushButton::clicked, this, &Lecturer_Attendance_Alternative::switchWindow_LecturerHomeQr);
    connect(ui->classListButton, &QPushButton::clicked, this, &Lecturer_Attendance_Alternative::switchWindow_LecturerClassesList);

    // Load window position
    QPoint windowPos = WindowPositionManager::loadWindowPosition();
    windowPos.setY(windowPos.y() - 31);
    move(windowPos);
}


Lecturer_Attendance_Alternative::~Lecturer_Attendance_Alternative()
{
    delete ui;
}


void Lecturer_Attendance_Alternative::selectClassInfo(const QStringList &keys_classInfo)
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
    Lecturer_Attendance_Alternative::displayClassInfo(classDataList);
}


void Lecturer_Attendance_Alternative::displayClassInfo(const QStringList &dataList)
{
    // Assign members from dataList to variables
    QString subjectCode = dataList[0];
    QString subjectDesc = dataList[1];
    QString program = dataList[2];
    QString year = dataList[3];
    QString section = dataList[4];

    // Display class information
    ui->headerSubjectCodeLabel->setText(StringManipulator::separateSubjectCode(subjectCode));
    ui->headerSubjectDescLabel->setText(subjectDesc);
    ui->headerProgramLabel->setText(QString("%1 %2%3").arg(program, year, section));
}


void Lecturer_Attendance_Alternative::verifyAuthCodeCall()
{
    // Fetch string input text() from textboxes
    QString authCode = ui->authCodeTextbox->text();
    QStringList keys_classInfo = $selectKeys_classInfo;

    // Must return result in QString from authentication function
    QString result = Lecturer_Attendance_Alternative::authenticateStudent(keys_classInfo, authCode);

    // Return error if the result is not empty
    if (!result.isEmpty())
    {
        GlobalTimer::displayTextForDuration(ui->failedLabel, result, 5000);
        return;
    }

    Lecturer_Attendance_Alternative::selectStudentInfo(authCode);
}


QString Lecturer_Attendance_Alternative::authenticateStudent(const QStringList &keys_classInfo, const QString &authCode)
{
    if (authCode == "") { return Messages::emptyAuthCode(); }
    if (authCode.length() != $authCodeLength) { return Messages::incompleteLengthAuthCode(); }
    if (authCode.contains(" ")) { return Messages::invalidAuthCode(); }


    // Return error if unable to access the database
    if (!database.open()) { return Messages::errorConnection(); }

    // Set up queries for database
    QSqlDatabase::database().transaction();
    QSqlQuery query(database);


    // Prepare sql command for finding existing data
    query.prepare("SELECT COUNT(*) FROM StudentInfo WHERE AuthCode = :authCode");

    // Bind values to the query
    query.bindValue(":authCode", authCode);

    // Return error if unable to select data
    if (!query.exec())
    {
        QSqlDatabase::database().rollback();
        return Messages::errorConnection();
    }

    query.next();
    int count = query.value(0).toInt();
    bool isAuthCodeExist = count > 0;

    if (!isAuthCodeExist) { return Messages::invalidAuthCode(); }
    query.clear();


    // Prepare sql command for finding data
    query.prepare("SELECT StudentId FROM StudentInfo WHERE AuthCode = :authCode");

    // Bind values to the query
    query.bindValue(":authCode", authCode);

    // Return error if unable to select data
    if (!query.exec())
    {
        QSqlDatabase::database().rollback();
        return Messages::errorConnection();
    }

    query.next();
    QString studentId = query.value(0).toString();
    query.clear();


    // Get data from select key
    QString key_subjectCode = keys_classInfo[0];
    QString key_program = keys_classInfo[1];
    QString key_year = keys_classInfo[2];
    QString key_section = keys_classInfo[3];
    QString key_semester = keys_classInfo[4];
    QString key_schoolYear = keys_classInfo[5];

    QString tableName = QString("%1%2%3%4_S%5SY%6").arg(key_subjectCode, key_program, key_year, key_section, key_semester, StringManipulator::convertSchoolYear(key_schoolYear));

    // Prepare sql command for finding existing data
    query.prepare("SELECT COUNT(*) FROM " + tableName + " WHERE StudentId = :studentId");

    // Bind values to the query
    query.bindValue(":studentId", studentId);

    // Return error if unable to select data
    if (!query.exec())
    {
        QSqlDatabase::database().rollback();
        return Messages::errorConnection();
    }

    query.next();
    count = query.value(0).toInt();
    bool isStudentIdExist = count > 0;

    if (!isStudentIdExist) { return Messages::invalidAuthCode(); }


    return "";
}


void Lecturer_Attendance_Alternative::selectStudentInfo(const QString &authCode)
{
    // Return error if unable to access the database
    if (!database.open())
    {
        GlobalTimer::displayTextForDuration(ui->failedLabel, Messages::errorConnection(), 5000);
        return;
    }

    // Set up data list and queries for database
    QStringList studentDataList;
    QSqlDatabase::database().transaction();
    QSqlQuery query(database);


    // Prepare sql command for finding data
    query.prepare("SELECT * FROM StudentInfo WHERE AuthCode = :authCode");

    // Bind values to the query
    query.bindValue(":authCode", authCode);

    // Return error if unable to select data
    if (!query.exec())
    {
        QSqlDatabase::database().rollback();
        GlobalTimer::displayTextForDuration(ui->failedLabel, Messages::errorConnection(), 5000);
        return;
    }

    query.next();
    studentDataList << query.value(0).toString();   // StudentId
    studentDataList << query.value(1).toString();   // Pin
    studentDataList << query.value(2).toString();   // LastName
    studentDataList << query.value(3).toString();   // FirstName
    studentDataList << query.value(4).toString();   // College
    studentDataList << query.value(5).toString();   // Program
    studentDataList << query.value(6).toString();   // Year
    studentDataList << query.value(7).toString();   // Section
    studentDataList << query.value(8).toString();   // IsRegular

    // Close the database after using
    QSqlDatabase::database().commit();
    database.close();

    // Proceed to display data list
    Lecturer_Attendance_Alternative::displayStudentInfo(studentDataList);
    verifiedAuthCode = authCode;
}


void Lecturer_Attendance_Alternative::displayStudentInfo(const QStringList &dataList)
{
    QString studentId = dataList[0];
    QString lastName = dataList[2];
    QString firstName = dataList[3];
    QString college = dataList[4];
    QString program = dataList[5];
    QString year = dataList[6];
    QString section = dataList[7];
    QString isRegular = dataList[8];

    ui->dataNameLabel->setText(QString("%1, %2").arg(lastName, firstName));
    ui->dataProgramLabel->setText(QString("%1 - %2 %3%4").arg(college, program, year, section));
    ui->dataStudentIdLabel->setText(studentId);
    ui->dataIsRegularLabel->setText(isRegular == "1" ? "Regular" : "Irregular");
    ui->dataAvatarLabel->setPixmap(QPixmap(QString(":/res/assets/%1_avatar.png").arg(college.toLower())));

    ui->confirmButton->setEnabled(true);
}


void Lecturer_Attendance_Alternative::takeAttendanceCall()
{
    // Return error if unable to access the database
    if (!database.open())
    {
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }

    // Set up query for database
    QSqlDatabase::database().transaction();
    QSqlQuery query(database);


    // Prepare sql command for finding data
    query.prepare("SELECT StudentId FROM StudentInfo WHERE AuthCode = :authCode");

    // Bind values to the query
    query.bindValue(":authCode", verifiedAuthCode);

    // Return error if unable to select data
    if (!query.exec())
    {
        QSqlDatabase::database().rollback();
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }

    query.next();
    QString studentId = query.value(0).toString();
    QStringList keys_classInfo = $selectKeys_classInfo;

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDate = currentDateTime.date().toString("MMM_dd_yyyy").toUpper();  // MMM_dd_yyyy
    QString currentTime = currentDateTime.time().toString("h:mm:ssAP");              // h:mm:ss AM/PM

    // Close the database after using
    QSqlDatabase::database().commit();
    database.close();

    // Proceed to update student record
    Lecturer_Attendance_Alternative::updateStudentRecord(keys_classInfo, studentId, currentDate, currentTime);
}


void Lecturer_Attendance_Alternative::updateStudentRecord(const QStringList &keys_classInfo, const QString &studentId,
                                                          const QString &currentDate, const QString &currentTime)
{
    // Return error if unable to access the database
    if (!database.open())
    {
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }

    // Get data from select key
    QString key_subjectCode = keys_classInfo[0];
    QString key_program = keys_classInfo[1];
    QString key_year = keys_classInfo[2];
    QString key_section = keys_classInfo[3];
    QString key_semester = keys_classInfo[4];
    QString key_schoolYear = keys_classInfo[5];

    QString tableName = QString("%1%2%3%4_S%5SY%6").arg(key_subjectCode, key_program, key_year, key_section, key_semester, StringManipulator::convertSchoolYear(key_schoolYear));

    // Set up query for database
    QSqlDatabase::database().transaction();
    QSqlQuery query(database);


    // Check if the column exists in the table
    bool columnExists = false;
    query.prepare("SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = :tableName AND COLUMN_NAME = :columnName");

    query.bindValue(":tableName", tableName);
    query.bindValue(":columnName", currentDate);

    if (!query.exec())
    {
        qDebug() << query.lastError().text();
        QSqlDatabase::database().rollback();
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }

    query.next();
    int count = query.value(0).toInt();
    columnExists = (count > 0);

    query.clear();

    // If column does not exist, create a new column named MMM_dd_yyyy (currentDate)
    if (!columnExists)
    {
        // Prepare sql command for adding column
        query.prepare("ALTER TABLE " + tableName + " ADD " +
                      currentDate + " VARCHAR(16) NOT NULL");

        if (!query.exec())
        {
            qDebug() << query.lastError().text();
            QSqlDatabase::database().rollback();
            GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
            return;
        }
        query.clear();


        // Prepare sql command for increasing absentcount value
        query.prepare("UPDATE " + tableName + " SET AbsentCount = AbsentCount + 1");

        if (!query.exec())
        {
            qDebug() << query.lastError().text();
            QSqlDatabase::database().rollback();
            GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
            return;
        }
        query.clear();
    }


    // Check if the student already attended the class this currentDay
    query.prepare("SELECT " + currentDate + " FROM " + tableName + " WHERE StudentId = :studentId");
    query.bindValue(":studentId", studentId);

    if (!query.exec())
    {
        qDebug() << query.lastError().text();
        QSqlDatabase::database().rollback();
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }

    query.next();
    QString value = query.value(0).toString();

    if (!value.isEmpty())
    {
        qDebug() << query.lastError().text();
        QSqlDatabase::database().rollback();
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::alreadyAttendedStudent(), 5000);
        return;
    }
    query.clear();


    // Prepare sql command for updating data
    query.prepare("UPDATE " + tableName + " SET " + currentDate + " = :currentTime WHERE StudentId = :studentId");

    // Bind values to the query
    query.bindValue(":currentTime", currentTime);
    query.bindValue(":studentId", studentId);

    if (!query.exec())
    {
        qDebug() << query.lastError().text();
        QSqlDatabase::database().rollback();
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }
    query.clear();


    // Prepare sql command for updating presentcount and absentcount
    query.prepare("UPDATE " + tableName + " SET AbsentCount = AbsentCount - 1 WHERE StudentId = :studentId");
    query.bindValue(":studentId", studentId);

    if (!query.exec())
    {
        qDebug() << query.lastError().text();
        QSqlDatabase::database().rollback();
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }
    query.clear();

    query.prepare("UPDATE " + tableName + " SET PresentCount = PresentCount + 1 WHERE StudentId = :studentId");
    query.bindValue(":studentId", studentId);

    if (!query.exec())
    {
        qDebug() << query.lastError().text();
        QSqlDatabase::database().rollback();
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }
    query.clear();


    // Close the database after using
    QSqlDatabase::database().commit();
    database.close();

    Lecturer_Attendance_Alternative::switchWindow_LecturerAttendanceList();
}


void Lecturer_Attendance_Alternative::switchWindow_LecturerHomeQr()
{
    // Switch ui window to Lecturer_Home_Qr
    lecturer_home_qr = new Lecturer_Home_Qr;
    lecturer_home_qr->show();
    this->hide();
}


void Lecturer_Attendance_Alternative::switchWindow_LecturerClassesList()
{
    // Switch ui window to Lecturer_Classes_List
    lecturer_classes_list = new Lecturer_Classes_List;
    lecturer_classes_list->show();
    this->hide();
}


void Lecturer_Attendance_Alternative::switchWindow_LecturerAttendanceList()
{
    // Switch ui window to Lecturer_Attendance_List
    lecturer_attendance_list = new Lecturer_Attendance_List;
    lecturer_attendance_list->show();
    this->hide();
}


void Lecturer_Attendance_Alternative::switchWindow_LecturerAttendanceScanner()
{
    // Switch ui window to Lecturer_Attendance_Scanner
    lecturer_attendance_scanner = new Lecturer_Attendance_Scanner;
    lecturer_attendance_scanner->show();
    this->hide();
}


void Lecturer_Attendance_Alternative::moveEvent(QMoveEvent *event)
{
    // Saves window position every movement instance of a window
    QMainWindow::moveEvent(event);
    WindowPositionManager::saveWindowPosition(event->pos());
}
