#include "global_main.h"

#include "student_home_auth.h"
#include "ui_student_home_auth.h"


// Include header files for forward declaration
#include "student_login_form.h"
#include "student_home_qr.h"


Student_Home_Auth::Student_Home_Auth(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Student_Home_Auth)
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
    Student_Home_Auth::selectStudentInfo($logKey_studentId);
    DateTimeUtils::updateDateTimeUtils(ui->dateLabel, ui->timeLabel);

    // Connect ui objects to functions based on user interaction
    connect(ui->backButton, &QPushButton::clicked, this, &Student_Home_Auth::switchWindow_StudentLoginForm);
    connect(ui->qrCodeButton, &QPushButton::clicked, this, &Student_Home_Auth::switchWindow_StudentHomeQr);

    // Load window position
    QPoint windowPos = WindowPositionManager::loadWindowPosition();
    windowPos.setY(windowPos.y() - 31);
    move(windowPos);
}


Student_Home_Auth::~Student_Home_Auth()
{
    delete ui;
}


void Student_Home_Auth::selectStudentInfo(const QString &key_studentId)
{
    // Return error if unable to access the database
    if (!database.open())
    {
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }

    // Set up data list and queries for database
    QStringList studentDataList;
    QSqlDatabase::database().transaction();
    QSqlQuery query(database);

    // Prepare sql command for selecting data
    query.prepare("SELECT * FROM StudentInfo WHERE StudentId = :studentId");

    // Bind values to the query
    query.bindValue(":studentId", key_studentId);

    // Return error if unable to select data
    if (!query.exec())
    {
        QSqlDatabase::database().rollback();
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }

    // Fetch and store data
    query.next();
    studentDataList << query.value(0).toString();       // StudentId
    studentDataList << query.value(1).toString();       // Pin
    studentDataList << query.value(2).toString();       // LastName
    studentDataList << query.value(3).toString();       // FirstName
    studentDataList << query.value(4).toString();       // College
    studentDataList << query.value(5).toString();       // Program
    studentDataList << query.value(6).toString();       // Year
    studentDataList << query.value(7).toString();       // Section
    studentDataList << query.value(8).toString();       // IsRegular
    studentDataList << query.value(9).toString();       // AuthCode

    // Close the database after using
    QSqlDatabase::database().commit();
    database.close();

    // Proceed to display data list
    Student_Home_Auth::displayStudentInfo(studentDataList);
    Student_Home_Auth::displayAuthInfo(studentDataList);
}


void Student_Home_Auth::displayStudentInfo(const QStringList &dataList)
{
    // Assign members from dataList to variables
    QString studentId = dataList[0];
    QString lastName = dataList[2];
    QString college = dataList[4];
    QString program = dataList[5];
    QString year = dataList[6];
    QString section = dataList[7];

    // Display student information in the header
    ui->headerWelcomeLabel->setText(QString("Hello, %1").arg(lastName));
    ui->headerProgramLabel->setText(QString("%1 - %2 %3%4").arg(college, program, year, section));
    ui->headerStudentIdLabel->setText(studentId.replace(5, 4, "****"));
    ui->headerAvatarLabel->setPixmap(QPixmap(QString(":/res/assets/%1_avatar.png").arg(college.toLower())));
}


void Student_Home_Auth::displayAuthInfo(const QStringList &dataList)
{
    // Assign members from dataList to variables
    QString studentId = dataList[0];
    QString lastName = dataList[2];
    QString firstName = dataList[3];
    QString college = dataList[4];
    QString program = dataList[5];
    QString year = dataList[6];
    QString section = dataList[7];
    QString authCode = dataList[9];

    // Display student informaton below generated qr
    ui->nameLabel->setText(QString("%1, %2***").arg(lastName, firstName.left(2)));
    ui->studentIdLabel->setText(studentId.replace(5, 4, "****"));
    ui->programLabel->setText(QString("%1 - %2 %3%4").arg(college, program, year, section));
    ui->authCodeLabel->setText(authCode);
}


void Student_Home_Auth::switchWindow_StudentLoginForm()
{
    // Switch ui window to Student_Login_Form
    student_login_form = new Student_Login_Form;
    student_login_form->show();
    this->hide();
}


void Student_Home_Auth::switchWindow_StudentHomeQr()
{
    // Switch ui window to Student_Home_Qr
    student_home_qr = new Student_Home_Qr;
    student_home_qr->show();
    this->hide();
}


void Student_Home_Auth::moveEvent(QMoveEvent *event)
{
    // Saves window position every movement instance of a window
    QMainWindow::moveEvent(event);
    WindowPositionManager::saveWindowPosition(event->pos());
}


/*
 *   Copyright (c) 2024 - WVSU-CICT BSCS 1B: Batch 2027
 *   All rights reserved.
 */
