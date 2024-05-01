#include "global_main.h"

#include "lecturer_attendance_list.h"
#include "ui_lecturer_attendance_list.h"


// Include header files for forward declaration
#include "lecturer_home_qr.h"
#include "lecturer_classes_list.h"
#include "lecturer_classes_info.h"
#include "lecturer_attendance_scanner.h"


Lecturer_Attendance_List::Lecturer_Attendance_List(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lecturer_Attendance_List)
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
    Lecturer_Attendance_List::selectClassInfo($selectKeys_classInfo);
    Lecturer_Attendance_List::filterSearchCall();
    DateTimeUtils::updateDateTimeUtils(ui->dateLabel, ui->timeLabel);

    // Connect ui objects to functions based on user interaction
    connect(ui->prevPageButton, &QPushButton::clicked, this, [=](){ FilteringManager::incrementPage(ui->numberPageTextbox, -1); });
    connect(ui->nextPageButton, &QPushButton::clicked, this, [=](){ FilteringManager::incrementPage(ui->numberPageTextbox, 1); });
    connect(ui->numberPageTextbox, &QLineEdit::textChanged, this, [=](){
        FilteringManager::validatePageEdit(ui->numberPageTextbox); Lecturer_Attendance_List::filterSearchCall();
    });

    connect(ui->backButton, &QPushButton::clicked, this, &Lecturer_Attendance_List::switchWindow_LecturerClassesInfo);
    connect(ui->homeButton, &QPushButton::clicked, this, &Lecturer_Attendance_List::switchWindow_LecturerHomeQr);
    connect(ui->classListButton, &QPushButton::clicked, this, &Lecturer_Attendance_List::switchWindow_LecturerClassesList);
    connect(ui->takeAttendanceButton, &QPushButton::clicked, this, &Lecturer_Attendance_List::switchWindow_LecturerAttendanceScanner);

    // Load window position
    QPoint windowPos = WindowPositionManager::loadWindowPosition();
    windowPos.setY(windowPos.y() - 31);
    move(windowPos);
}


Lecturer_Attendance_List::~Lecturer_Attendance_List()
{
    delete ui;
}


void Lecturer_Attendance_List::selectClassInfo(const QStringList &keys_classInfo)
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
    Lecturer_Attendance_List::displayClassInfo(classDataList);
}


void Lecturer_Attendance_List::displayClassInfo(const QStringList &dataList)
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


void Lecturer_Attendance_List::filterSearchCall()
{
    // Fetch string input text() from textboxes
    int pageNumber = ui->numberPageTextbox->text().toInt();
    QStringList keys_classInfo = $selectKeys_classInfo;

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDate = currentDateTime.date().toString("MMM_dd_yyyy").toUpper();  // MMM_dd_yyyy

    // Proceed to selecting data from database
    Lecturer_Attendance_List::selectAttendedStudents(pageNumber, keys_classInfo, currentDate);
}


void Lecturer_Attendance_List::selectAttendedStudents(const int &pageNumber, const QStringList &keys_classInfo, const QString &currentDate)
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

    // Calculate offset for pagination
    int offset = (pageNumber - 1) * $dataLimitPerPage;

    // Set up data list and queries for database
    QList<QStringList> studentRecordList;
    QList<QStringList> studentDataList;
    QSqlDatabase::database().transaction();
    QSqlQuery query(database);

    // Check if the column exists in the table
    bool columnExists = false;
    query.prepare("SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = :tableName AND COLUMN_NAME = :columnName");

    query.bindValue(":tableName", tableName);
    query.bindValue(":columnName", currentDate);

    if (!query.exec())
    {
        QSqlDatabase::database().rollback();
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }

    query.next();
    int count = query.value(0).toInt();
    columnExists = (count > 0);

    if (!columnExists) { return; }
    query.clear();

    // Prepare sql command for selecting data
    query.prepare("SELECT * FROM " + tableName +
                  " WHERE " + currentDate + " IS NOT NULL AND " + currentDate + " != ''" +
                  " ORDER BY " + currentDate + " ASC \
                  LIMIT :limit OFFSET :offset");

    // Bind values to the query
    query.bindValue(":limit", $dataLimitPerPage);
    query.bindValue(":offset", offset);

    // Return error if unable to select data
    if (!query.exec())
    {
        QSqlDatabase::database().rollback();
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }
    else
    {
        // Fetch and store the result rows
        while (query.next())
        {
            QStringList rowData;
            rowData << query.value(0).toString();               // StudentId
            rowData << query.value(currentDate).toString();     // Time of <CurrentDate>

            studentRecordList.append(rowData);
        }
    }
    query.clear();

    for (const auto &student : studentRecordList)
    {
        QString studentId = student[0];

        // Prepare sql command for selecting data
        query.prepare("SELECT * FROM StudentInfo WHERE StudentId = :studentId");

        // Bind values to the query
        query.bindValue(":studentId", studentId);

        // Return error if unable to select data
        if (!query.exec())
        {
            QSqlDatabase::database().rollback();
            GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
            return;
        }
        else
        {
            // Fetch and store the result rows
            query.next();

            QStringList rowData;
            rowData << query.value(0).toString();   // StudentId
            rowData << query.value(1).toString();   // Pin
            rowData << query.value(2).toString();   // LastName
            rowData << query.value(3).toString();   // FirstName
            rowData << query.value(4).toString();   // College
            rowData << query.value(5).toString();   // Program
            rowData << query.value(6).toString();   // Year
            rowData << query.value(7).toString();   // Section
            rowData << query.value(8).toString();   // IsRegular

            studentDataList.append(rowData);
        }

        query.clear();
    }

    // Close the database after using
    QSqlDatabase::database().commit();
    database.close();

    // Proceed to display data list
    Lecturer_Attendance_List::displayAttendedStudents(studentDataList, studentRecordList);
}


void Lecturer_Attendance_List::displayAttendedStudents(const QList<QStringList> &dataList, const QList<QStringList> &recordList)
{
    // Clear existing QGroupBox objects
    qDeleteAll(groupBoxList);
    groupBoxList.clear();

    int posX = 0;
    int posY = 0;

    // Create objects and add data groups
    int sizeList = recordList.size();
    for (int i = 0; i < sizeList; i++)
    {
        // Assign members from dataList to variables
        const QStringList &data = dataList.at(i);
        const QStringList &record = recordList.at(i);

        QString studentId = record.at(0);
        QString timeAtCurrentDate = record.at(1);

        QString lastName = data.at(2);
        QString firstName = data.at(3);
        QString college = data.at(4);
        QString program = data.at(5);
        QString year = data.at(6);
        QString section = data.at(7);
        QString isRegular = data.at(8);

        // Create data group box
        QGroupBox *dataGroup = new QGroupBox(ui->attendanceListArea);
        dataGroup->setGeometry(posX, posY, 310, 60);

        // Add the new QGroupBox pointer to the list
        groupBoxList.append(dataGroup);

        // Set up dataHud
        QLabel *dataHud = new QLabel(dataGroup);
        dataHud->setPixmap(QPixmap(":/res/assets/data_display.png"));
        dataHud->setGeometry(0, 0, 310, 60);

        // Set up dataAvatarLabel
        QLabel *dataAvatarLabel = new QLabel(dataGroup);
        dataAvatarLabel->setPixmap(QPixmap(QString(":/res/assets/%1_avatar.png").arg(college.toLower())));
        dataAvatarLabel->setGeometry(10, 10, 40, 40);

        // Set up dataNameLabel
        QLabel *dataNameLabel = new QLabel(dataGroup);
        dataNameLabel->setText(QString("%1, %2").arg(lastName, firstName));
        dataNameLabel->setStyleSheet("QLabel { color: #FFFFFF; font-family: Poppins; font-size: 12px; font-style: normal; font-weight: 600; line-height: normal; }");
        dataNameLabel->setGeometry(60, 12, 180, 10);

        // Set up dataProgramLabel
        QLabel *dataProgramLabel = new QLabel(dataGroup);
        dataProgramLabel->setText(QString("%1 - %2 %3%4").arg(college, program, year, section));
        dataProgramLabel->setStyleSheet("QLabel { color: #FFFFFF; font-family: Poppins; font-size: 9px; font-style: normal; font-weight: 400; line-height: normal; }");
        dataProgramLabel->setGeometry(60, 25, 180, 10);

        // Set up dataStudentIdLabel
        QLabel *dataStudentIdLabel = new QLabel(dataGroup);
        dataStudentIdLabel->setText(studentId);
        dataStudentIdLabel->setStyleSheet("QLabel { color: #15CAE3; font-family: Poppins; font-size: 9px; font-style: normal; font-weight: 400; line-height: normal; }");
        dataStudentIdLabel->setGeometry(60, 40, 70, 10);

        // Set up dataIsRegularLabel
        QLabel *dataIsRegularLabel = new QLabel(dataGroup);
        dataIsRegularLabel->setText(isRegular == "1" ? "Regular" : "Irregular");
        dataIsRegularLabel->setStyleSheet("QLabel { color: #15CAE3; font-family: Poppins; font-size: 9px; font-style: normal; font-weight: 400; line-height: normal; }");
        dataIsRegularLabel->setGeometry(130, 40, 70, 10);

        // Set up dataTimeAtCurrentDateLabel
        QLabel *dataTimeAtCurrentDateLabel = new QLabel(dataGroup);
        dataTimeAtCurrentDateLabel->setText(timeAtCurrentDate);
        dataTimeAtCurrentDateLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        dataTimeAtCurrentDateLabel->setStyleSheet("QLabel { color: #15CAE3; font-family: Poppins; font-size: 9px; font-style: normal; font-weight: 400; line-height: normal; }");
        dataTimeAtCurrentDateLabel->setGeometry(240, 40, 60, 10);

        // Add data group box to contents layout
        posY += dataGroup->height() + 5;
        dataGroup->setVisible(true);
        dataGroup->raise();
    }
}


void Lecturer_Attendance_List::switchWindow_LecturerHomeQr()
{
    // Switch ui window to Lecturer_Home_Qr
    lecturer_home_qr = new Lecturer_Home_Qr;
    lecturer_home_qr->show();
    this->hide();
}


void Lecturer_Attendance_List::switchWindow_LecturerClassesList()
{
    // Switch ui window to Lecturer_Classes_List
    lecturer_classes_list = new Lecturer_Classes_List;
    lecturer_classes_list->show();
    this->hide();
}


void Lecturer_Attendance_List::switchWindow_LecturerClassesInfo()
{
    // Switch ui window to Lecturer_Classes_Info
    lecturer_classes_info = new Lecturer_Classes_Info;
    lecturer_classes_info->show();
    this->hide();
}


void Lecturer_Attendance_List::switchWindow_LecturerAttendanceScanner()
{
    // Switch ui window to Lecturer_Attendance_Scanner
    lecturer_attendance_scanner = new Lecturer_Attendance_Scanner;
    lecturer_attendance_scanner->show();
    this->hide();
}


void Lecturer_Attendance_List::moveEvent(QMoveEvent *event)
{
    // Saves window position every movement instance of a window
    QMainWindow::moveEvent(event);
    WindowPositionManager::saveWindowPosition(event->pos());
}
