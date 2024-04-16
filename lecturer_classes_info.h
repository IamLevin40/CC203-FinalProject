#ifndef LECTURER_CLASSES_INFO_H
#define LECTURER_CLASSES_INFO_H

#include <QMainWindow>

namespace Ui {
class Lecturer_Classes_Info;
}

class Lecturer_Classes_Info : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lecturer_Classes_Info(QWidget *parent = nullptr);
    ~Lecturer_Classes_Info();

private:
    Ui::Lecturer_Classes_Info *ui;
};

#endif // LECTURER_CLASSES_INFO_H
