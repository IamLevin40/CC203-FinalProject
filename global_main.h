#ifndef GLOBAL_MAIN_H
#define GLOBAL_MAIN_H

#include <QObject>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QIcon>

#include <QString>
#include <QVector>
#include <QPoint>
#include <QList>
#include <QStringList>
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include <QSettings>
#include <QRandomGenerator>


// Global variables
extern QString $appCompany;
extern QString $appName;

extern short $studentIdLength;
extern short $lecturerIdLength;
extern short $pinLength;
extern short $authCodeLength;
extern short $minPage;
extern short $maxPage;
extern short $dataLimitPerPage;


// Global database
extern QString $sql_Driver;
extern QString $db_Hostname;
extern QString $db_Username;
extern QString $db_Password;
extern QString $db_Database;
extern int $db_Port;

extern QString $logKey_studentId;
extern QString $logKey_lecturerId;
extern QStringList $selectKeys_classInfo;


// Global colleges
namespace Colleges
{
    // Define colleges
    extern const QStringList $colleges;
}


// Global messages
namespace Messages
{
    inline QString errorConnection() { return "No internet connection. Try again."; }

    inline QString emptyStudentId() { return "Student number is required."; }
    inline QString incompleteLengthStudentId() { return "Student number should be exactly 9 characters long."; }
    inline QString invalidStudentId() { return "Student number is invalid."; }
    inline QString notExistStudentId() { return "Student number does not exist."; }
    inline QString alreadyAttendedStudent() { return "Student already attended today."; }

    inline QString emptyLecturerId() { return "Lecturer number is required."; }
    inline QString incompleteLengthLecturerId() { return "Lecturer number should be exactly 4 characters long."; }
    inline QString invalidLecturerId() { return "Lecturer number is invalid."; }
    inline QString notExistLecturerId() { return "Lecturer number does not exist."; }

    inline QString emptyPin() { return "Pin is required."; }
    inline QString incompleteLengthPin() { return "Pin should be exactly 6 digits long"; }
    inline QString invalidPin() { return "Pin is invalid. Must only consist digits."; }
    inline QString incorrectPin() { return "Incorrect pin."; }

    inline QString noSelectedCollege() { return "No selected college."; }
    inline QString incorrectCollege() { return "Incorrect college."; }

    inline QString noCameraSetup() { return "No camera set-up available."; }
    inline QString notExistScanner() { return "Scanner does not exist."; }
    inline QString invalidQrCode() { return "Invalid QR Code."; }

    inline QString emptyAuthCode() { return "Authentication code is required."; }
    inline QString incompleteLengthAuthCode() { return "Authenticaion code should be exactly 6 characters long."; }
    inline QString invalidAuthCode() { return "Invalid authenticaion code."; }

    inline QString unableCreateDataSheet() { return "Unable to create data sheet."; }
}


// Toggle manager
class ToggleManager {
    public:
        static void toggleEchoMode(QLineEdit *textbox, QPushButton *toggle);
};


// Authentication code generator
class Generator
{
    public:
        static QString authCodeGenerator();
};


// Global timer
class GlobalTimer : public QObject
{
    Q_OBJECT

    public:
        static QTimer* timer();
        static void displayTextForDuration(QObject* object, const QString& text, int duration);

    private:
        static QTimer* m_timer;
};


// Date and time utilities
class DateTimeUtils
{
    public:
        static void updateDateTimeUtils(QLabel *dateLabel, QLabel *timeLabel);
};


// String manipulator
class StringManipulator
{
    public:
        static QString separateSubjectCode(const QString &subjectCode);
        static QString convertSchoolYear(const QString &schoolYear);
};


// Filtering manager
class FilteringManager
{
    public:
        static void incrementPage(QObject *object, const int &index);
        static void validatePageEdit(QObject *object);
        static void checkComboboxIndex(QObject *object);
};


// Window position manager
class WindowPositionManager
{
    public:
        static QPoint loadWindowPosition();
        static void saveWindowPosition(const QPoint &position);
};


#endif // GLOBAL_MAIN_H


/*
 *   Copyright (c) 2024 - WVSU-CICT BSCS 1B: Batch 2027
 *   All rights reserved.
 */
