#include "global_main.h"


// Global variables
QString $appCompany = "BSCS1B";
QString $appName = "Presence";

short $studentIdLength = 9;
short $lecturerIdLength = 4;
short $pinLength = 6;
short $minPage = 1;
short $maxPage = 999;
short $dataLimitPerPage = 5;


// Global database
QString $sql_Driver= "QMYSQL";
QString $db_Hostname = "sql6.freesqldatabase.com";
QString $db_Username = "sql6701487";
QString $db_Password = "6adX9UfkzD";
QString $db_Database = "sql6701487";
int $db_Port = 3306;

QString $logKey_studentId = "";
QString $logKey_lecturerId = "";
QStringList $selectKeys_classInfo;


// Global colleges and its corresponding programs
namespace Colleges
{
    const QStringList $colleges = {
        "",
        "CAS | College of Arts & Sciences",
        "CBM | College of Business & Management",
        "CICT | College of Information and Communications Technology",
        "COC | College of Communication",
        "COD | College of Dentistry",
        "COE | College of Education",
        "COL | College of Law",
        "COM | College of Medicine",
        "CON | College of Nursing",
        "PESCAR | College of Physical Education, Sports, Culture, Arts, and Recreation"
    };
}


// Global timer
QTimer* GlobalTimer::m_timer = new QTimer();
void GlobalTimer::displayTextForDuration(QObject* object, const QString& text, int duration)
{
    QLabel* label = qobject_cast<QLabel*>(object);
    if (label) {
        label->setText(text);

        // Stop the existing timer if it's running
        if (m_timer->isActive()) {
            m_timer->stop();
        }

        // Start a new timer with the specified duration
        m_timer->singleShot(duration, label, [=]() {
            label->clear();
        });
    }
}


// Update date and time label text
void DateTimeUtils::updateDateTimeUtils(QLabel *dateLabel, QLabel *timeLabel)
{
    QTimer *timer = new QTimer();

    // Connect the timer's timeout signal to a lambda function that updates the labels
    QObject::connect(timer, &QTimer::timeout, [=]() {
        // Get current date and time
        QDateTime currentDateTime = QDateTime::currentDateTime();
        dateLabel->setText(currentDateTime.date().toString("MMM. dd, yyyy"));
        timeLabel->setText(currentDateTime.time().toString("h:mm:ssAP"));
    });

    // Start the timer to trigger the update every second
    timer->start(1000);
}


// Convert school year to short year and vice versa
QString FilteringManager::convertSchoolYear(const QString &schoolYear)
{
    // Check if the input year has a dash, if yes, convert to short year
    if (schoolYear.contains("-"))
    {
        QString firstPart = schoolYear.mid(2, 2);
        QString secondPart = schoolYear.mid(7, 2);
        return firstPart + secondPart;
    }
    // If the input year is already a short year, convert to full school year
    else
    {
        QString firstPart = schoolYear.mid(0, 2);
        QString lastPart = schoolYear.mid(2, 2);
        return "20" + firstPart + "-" + "20" + lastPart;
    }
}


// Increment or decrement page
void FilteringManager::incrementPage(QObject *object, const int &index)
{
    // Get the sender object: lineedit
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(object);
    if (!lineEdit)
        return;

    // Fetch the current page and increment with index
    int currentPage = lineEdit->text().toInt();
    currentPage += index;

    // Check if exceeds maximum page or below minimum page
    if (currentPage <= $minPage) { currentPage = $minPage; }
    if (currentPage >= $maxPage) { currentPage = $maxPage; }

    lineEdit->setText(QString::number(currentPage));
}


// Validate the page textbox that user edited
void FilteringManager::validatePageEdit(QObject *object)
{
    // Get the sender object: lineedit
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(object);
    if (!lineEdit)
        return;

    // Get the text from lineedit
    QString text = lineEdit->text();
    bool isNum;
    int pageNumber = text.toInt(&isNum);

    // Return if the user is still editing the page number
    if (text.isEmpty() && lineEdit->hasFocus())
        return;

    // Check if conversion to integer was successful and within range
    if (!(isNum && pageNumber >= $minPage && pageNumber <= $maxPage))
    {
        // Revert back to the last valid page number
        lineEdit->setText(QString::number($minPage));
        return;
    }

    // Update the text to remove leading zeroes
    lineEdit->setText(QString::number(pageNumber));
}


// Check selected option from combobox
void FilteringManager::checkComboboxIndex(QObject *object)
{
    // Get the sender object: combobox
    QComboBox *comboBox = qobject_cast<QComboBox*>(object);
    if (!comboBox)
        return;

    // Deselect the combobox if the current option has no string
    QString selectedText = comboBox->currentText();
    if (selectedText.isEmpty()) {
        comboBox->setCurrentIndex(-1);
    }
}


// Window position manager
QPoint WindowPositionManager::loadWindowPosition()
{
    // Return value of "windowPosition" from HKEY_CURRENT_USER\Software\$appCompany\$appName
    QSettings settings($appCompany, $appName);
    return settings.value("windowPosition", QPoint(0, 30)).toPoint();
}

void WindowPositionManager::saveWindowPosition(const QPoint &position)
{
    // Saves value of "windowPosition" to HKEY_CURRENT_USER\Software\$appCompany\$appName
    QSettings settings($appCompany, $appName);
    settings.setValue("windowPosition", position);
}
