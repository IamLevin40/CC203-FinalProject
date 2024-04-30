#include "global_main.h"

#include "lecturer_login_form.h"
#include "ui_lecturer_login_form.h"


// Include header files for forward declaration
#include "select_profession.h"
#include "lecturer_home_qr.h"


Lecturer_Login_Form::Lecturer_Login_Form(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lecturer_Login_Form)
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
    Lecturer_Login_Form::populateCombobox();

    // Connect ui objects to functions based on user interaction
    connect(ui->loginButton, &QPushButton::clicked, this, &Lecturer_Login_Form::loginCall);
    connect(ui->backButton, &QPushButton::clicked, this, &Lecturer_Login_Form::switchWindow_SelectProfession);

    // Load window position
    QPoint windowPos = WindowPositionManager::loadWindowPosition();
    windowPos.setY(windowPos.y() - 31);
    move(windowPos);
}


Lecturer_Login_Form::~Lecturer_Login_Form()
{
    delete ui;
}


void Lecturer_Login_Form::loginCall()
{
    // Fetch string input text() from textboxes and comboboxes
    QString lecturerId = ui->lecturerIdTextbox->text();
    QString pin = ui->pinTextbox->text();
    QString college = ui->collegeCombobox->currentText();

    // Extract unnecessary substring for data handling
    int collegeIndex = college.indexOf('|');
    college = college.left(collegeIndex).trimmed();

    // Must return result in QString from authentication function
    QString result = Lecturer_Login_Form::authenticateLecturer(lecturerId, pin, college);

    // Return error if the result is not empty
    if (!result.isEmpty())
    {
        GlobalTimer::displayTextForDuration(ui->errorLabel, result, 5000);
        return;
    }

    Lecturer_Login_Form::updateAuthCode(lecturerId);
    Lecturer_Login_Form::switchWindow_LecturerHomeQr(lecturerId);
}


QString Lecturer_Login_Form::authenticateLecturer(const QString &lecturerId, const QString &pin, const QString college)
{
    if (lecturerId == "") { return Messages::emptyLecturerId(); }
    if (lecturerId.length() != $lecturerIdLength) { return Messages::incompleteLengthLecturerId(); }
    if (lecturerId.contains(" ")) { return Messages::invalidLecturerId(); }

    if (pin == "") { return Messages::emptyPin(); }
    if (pin.length() != $pinLength) { return Messages::incompleteLengthPin(); }
    if (pin.contains(" ")) { return Messages::invalidPin(); }

    bool isNum;
    int _pin = pin.toInt(&isNum);
    if (!isNum) { return _pin + "" + Messages::invalidPin(); }

    if (college == "") { return Messages::noSelectedCollege(); }


    // Return error if unable to access the database
    if (!database.open()) { return Messages::errorConnection(); }

    // Set up queries for database
    QSqlDatabase::database().transaction();
    QSqlQuery query(database);


    // Prepare sql command for finding existing data
    query.prepare("SELECT COUNT(*) FROM LecturerInfo WHERE LecturerId = :lecturerId");

    // Bind values to the query
    query.bindValue(":lecturerId", lecturerId);

    // Return error if unable to select data
    if (!query.exec())
    {
        QSqlDatabase::database().rollback();
        return Messages::errorConnection();
    }

    query.next();
    int count = query.value(0).toInt();
    bool isLecturerIdExist = count > 0;

    if (!isLecturerIdExist) { return Messages::notExistLecturerId(); }
    query.clear();


    // Prepare sql command for finding data
    query.prepare("SELECT Pin, College FROM LecturerInfo WHERE LecturerId = :lecturerId");

    // Bind values to the query
    query.bindValue(":lecturerId", lecturerId);

    // Return error if unable to select data
    if (!query.exec())
    {
        QSqlDatabase::database().rollback();
        return Messages::errorConnection();
    }

    query.next();
    QString authenticPin = query.value(0).toString();
    QString authenticCollege = query.value(1).toString();

    if (authenticPin != pin) { return Messages::incorrectPin(); }
    if (authenticCollege != college) { return Messages::incorrectCollege(); }


    return "";
}


void Lecturer_Login_Form::updateAuthCode(const QString &lecturerId)
{
    // Return error if unable to access the database
    if (!database.open())
    {
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }

    // Set up queries for database
    QSqlDatabase::database().transaction();
    QSqlQuery query(database);


    QString authCode;
    bool isAuthCodeExist = true;

    // Check if authCode already exists, otherwise update authCode to the database
    while (isAuthCodeExist)
    {
        // Generate authentication code
        authCode = Generator::authCodeGenerator();

        // Prepare sql command for finding existing data
        query.prepare("SELECT COUNT(*) FROM LecturerInfo WHERE AuthCode = :authCode");

        // Bind values to the query
        query.bindValue(":authCode", authCode);

        // Return error if unable to select data
        if (!query.exec())
        {
            QSqlDatabase::database().rollback();
            GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
            return;
        }

        query.next();
        int count = query.value(0).toInt();
        isAuthCodeExist = count > 0;
    }

    // Prepare sql command for updating data
    query.prepare("UPDATE LecturerInfo SET \
                  AuthCode = :authCode \
                  WHERE LecturerId = :lecturerId");

    // Bind values to the query
    query.bindValue(":authCode", authCode);
    query.bindValue(":lecturerId", lecturerId);

    // Return error if unable to update data
    if (!query.exec())
    {
        QSqlDatabase::database().rollback();
        GlobalTimer::displayTextForDuration(ui->errorLabel, Messages::errorConnection(), 5000);
        return;
    }

    // Close the database after using
    QSqlDatabase::database().commit();
    database.close();
}


void Lecturer_Login_Form::populateCombobox()
{
    // Populate comboboxes with items
    ui->collegeCombobox->addItems(Colleges::$colleges);

    // Connect comboboxes to checkComboboxIndex()
    connect(ui->collegeCombobox, &QComboBox::currentIndexChanged, this, [=](){ FilteringManager::checkComboboxIndex(ui->collegeCombobox); });
}


void Lecturer_Login_Form::switchWindow_SelectProfession()
{
    // Switch ui window to Select_Profession
    select_profession = new Select_Profession;
    select_profession->show();
    this->hide();
}


void Lecturer_Login_Form::switchWindow_LecturerHomeQr(const QString &lecturerId)
{
    // Set primary key for logged-in lecturer id
    $logKey_lecturerId = lecturerId;

    // Switch ui window to Lecturer_Home
    lecturer_home_qr = new Lecturer_Home_Qr;
    lecturer_home_qr->show();
    this->hide();
}


void Lecturer_Login_Form::moveEvent(QMoveEvent *event)
{
    // Saves window position every movement instance of a window
    QMainWindow::moveEvent(event);
    WindowPositionManager::saveWindowPosition(event->pos());
}
