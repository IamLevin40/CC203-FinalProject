#include "global_main.h"

#include "lecturer_classes_list.h"
#include "ui_lecturer_classes_list.h"


// Include header files for forward declaration
#include "lecturer_login_form.h"
#include "lecturer_home_qr.h"
#include "lecturer_classes_info.h"


Lecturer_Classes_List::Lecturer_Classes_List(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lecturer_Classes_List)
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
    Lecturer_Classes_List::selectInfoFromDatabase($logKey_lecturerId);
    Lecturer_Classes_List::filterSearchCall();
    DateTimeUtils::updateDateTimeUtils(ui->dateLabel, ui->timeLabel);

    // Connect ui objects to functions based on user interaction
    connect(ui->prevPageButton, &QPushButton::clicked, this, [=](){ FilteringManager::incrementPage(ui->numberPageTextbox, -1); });
    connect(ui->nextPageButton, &QPushButton::clicked, this, [=](){ FilteringManager::incrementPage(ui->numberPageTextbox, 1); });
    connect(ui->numberPageTextbox, &QLineEdit::textChanged, this, [=](){
        FilteringManager::validatePageEdit(ui->numberPageTextbox); Lecturer_Classes_List::filterSearchCall();
    });

    connect(ui->backButton, &QPushButton::clicked, this, &Lecturer_Classes_List::switchWindow_LecturerLoginForm);
    connect(ui->homeButton, &QPushButton::clicked, this, &Lecturer_Classes_List::switchWindow_LecturerHomeQr);

    // Load window position
    QPoint windowPos = WindowPositionManager::loadWindowPosition();
    windowPos.setY(windowPos.y() - 31);
    move(windowPos);
}


Lecturer_Classes_List::~Lecturer_Classes_List()
{
    delete ui;
}


void Lecturer_Classes_List::selectInfoFromDatabase(const QString &key_lecturerId)
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
    Lecturer_Classes_List::displayInfoFromDatabase(lecturerDataList);
}


void Lecturer_Classes_List::displayInfoFromDatabase(const QStringList &dataList)
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


void Lecturer_Classes_List::filterSearchCall()
{
    // Fetch string input text() from textboxes
    int pageNumber = ui->numberPageTextbox->text().toInt();
    QString key_lecturerId = $logKey_lecturerId;

    // Proceed to selecting data from database
    Lecturer_Classes_List::selectDataFromDatabase(pageNumber, key_lecturerId);
}


void Lecturer_Classes_List::selectDataFromDatabase(const int &pageNumber, const QString &lecturerId)
{
    // Return error if unable to access the database
    if (!database.open())
    {
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }

    // Calculate offset for pagination
    int offset = (pageNumber - 1) * $dataLimitPerPage;

    // Set up data list and queries for database
    QList<QStringList> classDataList;
    QSqlDatabase::database().transaction();
    QSqlQuery query(database);

    // Prepare sql command for selecting data
    query.prepare("SELECT * FROM ClassInfo WHERE LecturerId = :lecturerId \
                  LIMIT :limit OFFSET :offset");

    // Bind values to the query
    query.bindValue(":lecturerId", lecturerId);
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
            rowData << query.value(0).toString();   // SubjectCode
            rowData << query.value(1).toString();   // SubjectDesc
            rowData << query.value(2).toString();   // SchoolYear
            rowData << query.value(3).toString();   // Semester
            rowData << query.value(4).toString();   // Program
            rowData << query.value(5).toString();   // Year
            rowData << query.value(6).toString();   // Section
            rowData << query.value(7).toString();   // Day
            rowData << query.value(8).toString();   // Time
            rowData << query.value(9).toString();   // Room
            rowData << query.value(10).toString();  // LecturerId

            classDataList.append(rowData);
        }
    }

    // Close the database after using
    QSqlDatabase::database().commit();
    database.close();

    // Proceed to display data list
    Lecturer_Classes_List::displayDataFromDatabase(classDataList);
}


void Lecturer_Classes_List::displayDataFromDatabase(const QList<QStringList> &dataList)
{
    // Clear existing QGroupBox objects
    qDeleteAll(groupBoxList);
    groupBoxList.clear();

    int posX = 0;
    int posY = 0;

    // Create objects and add data groups
    for (const auto &data : dataList)
    {
        // Assign members from dataList to variables
        QString subjectCode = data[0];
        QString subjectDesc = data[1];
        QString schoolYear = data[2];
        QString semester = data[3];
        QString program = data[4];
        QString year = data[5];
        QString section = data[6];
        QString day = data[7];
        QString time = data[8];
        QString room = data[9];

        // List down class information for class info keys
        QStringList classInfo;
        classInfo << subjectCode;
        classInfo << program;
        classInfo << year;
        classInfo << section;
        classInfo << semester;
        classInfo << schoolYear;

        // Create data group box
        QGroupBox *dataGroup = new QGroupBox(ui->classesListArea);
        dataGroup->setGeometry(posX, posY, 310, 60);

        // Add the new QGroupBox pointer to the list
        groupBoxList.append(dataGroup);

        // Set up dataHud
        QLabel *dataHud = new QLabel(dataGroup);
        dataHud->setPixmap(QPixmap(":/res/assets/data_display.png"));
        dataHud->setGeometry(0, 0, 310, 60);

        // Set up dataSubjectCodeLabel
        QLabel *dataSubjectCodeLabel = new QLabel(dataGroup);
        dataSubjectCodeLabel->setText(subjectCode);
        dataSubjectCodeLabel->setStyleSheet("QLabel { color: #FFFFFF; font-family: Poppins; font-size: 9px; font-style: normal; font-weight: 600; line-height: normal; }");
        dataSubjectCodeLabel->setGeometry(10, 12, 45, 10);

        // Set up dataSubjectDescLabel
        QLabel *dataSubjectDescLabel = new QLabel(dataGroup);
        dataSubjectDescLabel->setText(subjectDesc);
        dataSubjectDescLabel->setStyleSheet("QLabel { color: #FFFFFF; font-family: Poppins; font-size: 9px; font-style: normal; font-weight: 600; line-height: normal; }");
        dataSubjectDescLabel->setGeometry(60, 12, 180, 10);

        // Set up dataSchoolYearLabel
        QLabel *dataSchoolYearLabel = new QLabel(dataGroup);
        dataSchoolYearLabel->setText(QString("SY %1   SEM %2").arg(schoolYear, semester));
        dataSchoolYearLabel->setStyleSheet("QLabel { color: #15CAE3; font-family: Poppins; font-size: 7px; font-style: normal; font-weight: 400; line-height: normal; }");
        dataSchoolYearLabel->setGeometry(60, 32, 180, 10);

        // Set up dataProgramLabel
        QLabel *dataProgramLabel = new QLabel(dataGroup);
        dataProgramLabel->setText(QString("%1 %2%3").arg(program, year, section));
        dataProgramLabel->setStyleSheet("QLabel { color: #15CAE3; font-family: Poppins; font-size: 7px; font-style: normal; font-weight: 400; line-height: normal; }");
        dataProgramLabel->setGeometry(10, 40, 45, 10);

        // Set up dataScheduleLabel
        QLabel *dataScheduleLabel = new QLabel(dataGroup);
        dataScheduleLabel->setText(QString("%1   %2").arg(day, time));
        dataScheduleLabel->setStyleSheet("QLabel { color: #15CAE3; font-family: Poppins; font-size: 7px; font-style: normal; font-weight: 400; line-height: normal; }");
        dataScheduleLabel->setGeometry(60, 40, 180, 10);

        // Set up dataRoomLabel
        QLabel *dataRoomLabel = new QLabel(dataGroup);
        dataRoomLabel->setText(room);
        dataRoomLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        dataRoomLabel->setStyleSheet("QLabel { color: #15CAE3; font-family: Poppins; font-size: 7px; font-style: normal; font-weight: 400; line-height: normal; }");
        dataRoomLabel->setGeometry(240, 40, 60, 10);

        // Set up dataListButton
        QPushButton *dataListButton = new QPushButton(dataGroup);
        dataListButton->setIcon(QIcon(":res/assets/list.png"));
        dataListButton->setStyleSheet("QPushButton { border: 0px; border-radius: 0px; background: none; }");
        dataListButton->setGeometry(285, 10, 15, 15);
        connect(dataListButton, &QPushButton::clicked, this, [=]() {
            Lecturer_Classes_List::switchWindow_LecturerClassesInfo(classInfo);
        });

        // Add data group box to contents layout
        posY += dataGroup->height() + 5;
        dataGroup->setVisible(true);
        dataGroup->raise();
    }
}


void Lecturer_Classes_List::switchWindow_LecturerLoginForm()
{
    // Switch ui window to Lecturer_Login_Form
    lecturer_login_form = new Lecturer_Login_Form;
    lecturer_login_form->show();
    this->hide();
}


void Lecturer_Classes_List::switchWindow_LecturerHomeQr()
{
    // Switch ui window to Lecturer_Home_Qr
    lecturer_home_qr = new Lecturer_Home_Qr;
    lecturer_home_qr->show();
    this->hide();
}


void Lecturer_Classes_List::switchWindow_LecturerClassesInfo(const QStringList &keys_classInfo)
{
    // Set primary keys for class info
    $selectKeys_classInfo = keys_classInfo;

    // Switch ui window to Lecturer_Classes_Info
    lecturer_classes_info = new Lecturer_Classes_Info;
    lecturer_classes_info->show();
    this->hide();
}


void Lecturer_Classes_List::moveEvent(QMoveEvent *event)
{
    // Saves window position every movement instance of a window
    QMainWindow::moveEvent(event);
    WindowPositionManager::saveWindowPosition(event->pos());
}
