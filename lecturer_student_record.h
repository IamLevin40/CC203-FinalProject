#ifndef LECTURER_STUDENT_RECORD_H
#define LECTURER_STUDENT_RECORD_H

#include <QMainWindow>

namespace Ui {
class Lecturer_Student_Record;
}

class Lecturer_Student_Record : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lecturer_Student_Record(QWidget *parent = nullptr);
    ~Lecturer_Student_Record();

private:
    Ui::Lecturer_Student_Record *ui;
};

#endif // LECTURER_STUDENT_RECORD_H
