#ifndef LECTURER_STUDENT_RECORD_H
#define LECTURER_STUDENT_RECORD_H

#include <QMainWindow>
#include <QMoveEvent>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLayout>
#include <QLayoutItem>


// Forward declaration of class files
class Lecturer_Home;
class Lecturer_Classes_List;
class Lecturer_Classes_Info;


namespace Ui {
    class Lecturer_Student_Record;
}

class Lecturer_Student_Record : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Lecturer_Student_Record(QWidget *parent = nullptr);
        ~Lecturer_Student_Record();

    protected:
        void moveEvent(QMoveEvent *event) override;

    private:
        Ui::Lecturer_Student_Record *ui;
        QSqlDatabase database;
        QList<QGroupBox*> groupBoxList;

        // Reference the class files here
        Lecturer_Home *lecturer_home;
        Lecturer_Classes_List *lecturer_classes_list;
        Lecturer_Classes_Info *lecturer_classes_info;

        // All custom functions() should be recognized upon here
        void selectInfoFromDatabase(const QStringList &keys_classInfo);
        void displayInfoFromDatabase(const QStringList &dataList);
        void filterSearchCall();
        void selectDataFromDatabase(const int &pageNumber, const QStringList &keys_classInfo);
        void displayDataFromDatabase(const QList<QStringList> &dataList, const QList<QStringList> &recordList);
        void switchWindow_LecturerHome();
        void switchWindow_LecturerClassesList();
        void switchWindow_LecturerClassesInfo();
};

#endif // LECTURER_STUDENT_RECORD_H
