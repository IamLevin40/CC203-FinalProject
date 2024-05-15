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

#include <QtWidgets>
#include <QAxObject>


// Forward declaration of class files
class Lecturer_Home_Qr;
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
        Lecturer_Home_Qr *lecturer_home_qr;
        Lecturer_Classes_List *lecturer_classes_list;
        Lecturer_Classes_Info *lecturer_classes_info;

        // All custom functions() should be recognized upon here
        void selectClassInfo(const QStringList &keys_classInfo);
        void displayClassInfo(const QStringList &dataList);

        void filterSearchCall();
        void selectEnlistedStudents(const int &pageNumber, const QStringList &keys_classInfo);
        void displayEnlistedStudents(const QList<QStringList> &dataList);

        void createExcelFile(const QStringList &keys_classInfo);

        void switchWindow_LecturerHomeQr();
        void switchWindow_LecturerClassesList();
        void switchWindow_LecturerClassesInfo();
};

#endif // LECTURER_STUDENT_RECORD_H


/*
 *   Copyright (c) 2024 - WVSU-CICT BSCS 1B: Batch 2027
 *   All rights reserved.
 */
