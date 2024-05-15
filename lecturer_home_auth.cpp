#include "global_main.h"

#include "lecturer_home_auth.h"
#include "ui_lecturer_home_auth.h"


// Include header files for forward declaration
#include "lecturer_login_form.h"
#include "lecturer_classes_list.h"
#include "lecturer_home_qr.h"


Lecturer_Home_Auth::Lecturer_Home_Auth(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lecturer_Home_Auth)
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
    Lecturer_Home_Auth::selectLecturerInfo($logKey_lecturerId);
    DateTimeUtils::updateDateTimeUtils(ui->dateLabel, ui->timeLabel);

    // Connect ui objects to functions based on user interaction
    connect(ui->backButton, &QPushButton::clicked, this, &Lecturer_Home_Auth::switchWindow_LecturerLoginForm);
    connect(ui->classListButton, &QPushButton::clicked, this, &Lecturer_Home_Auth::switchWindow_LecturerClassesList);
    connect(ui->qrCodeButton, &QPushButton::clicked, this, &Lecturer_Home_Auth::switchWindow_LecturerHomeQr);

    // Load window position
    QPoint windowPos = WindowPositionManager::loadWindowPosition();
    windowPos.setY(windowPos.y() - 31);
    move(windowPos);
}


Lecturer_Home_Auth::~Lecturer_Home_Auth()
{
    delete ui;
}


void Lecturer_Home_Auth::selectLecturerInfo(const QString &key_lecturerId)
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
    lecturerDataList << query.value(5).toString();      // AuthCode

    // Close the database after using
    QSqlDatabase::database().commit();
    database.close();

    // Proceed to display data list
    Lecturer_Home_Auth::displayLecturerInfo(lecturerDataList);
    Lecturer_Home_Auth::displayAuthInfo(lecturerDataList);
}


void Lecturer_Home_Auth::displayLecturerInfo(const QStringList &dataList)
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


void Lecturer_Home_Auth::displayAuthInfo(const QStringList &dataList)
{
    // Assign members from dataList to variables
    QString lastName = dataList[2];
    QString firstName = dataList[3];
    QString college = dataList[4];
    QString authCode = dataList[5];

    // Display lecturer informaton below generated qr
    ui->nameLabel->setText(QString("%1, %2***").arg(lastName, firstName.left(2)));
    ui->lecturerIdLabel->setText("LN: ****");
    ui->collegeLabel->setText(college);
    ui->authCodeLabel->setText(authCode);
}


void Lecturer_Home_Auth::switchWindow_LecturerLoginForm()
{
    // Switch ui window to Lecturer_Login_Form
    lecturer_login_form = new Lecturer_Login_Form;
    lecturer_login_form->show();
    this->hide();
}


void Lecturer_Home_Auth::switchWindow_LecturerClassesList()
{
    // Switch ui window to Lecturer_Classes_List
    lecturer_classes_list = new Lecturer_Classes_List;
    lecturer_classes_list->show();
    this->hide();
}


void Lecturer_Home_Auth::switchWindow_LecturerHomeQr()
{
    // Switch ui window to Lecturer_Home_Qr
    lecturer_home_qr = new Lecturer_Home_Qr;
    lecturer_home_qr->show();
    this->hide();
}


void Lecturer_Home_Auth::moveEvent(QMoveEvent *event)
{
    // Saves window position every movement instance of a window
    QMainWindow::moveEvent(event);
    WindowPositionManager::saveWindowPosition(event->pos());
}


/*
 *   Copyright (c) 2024 - WVSU-CICT BSCS 1B: Batch 2027
 *   All rights reserved.
 */
