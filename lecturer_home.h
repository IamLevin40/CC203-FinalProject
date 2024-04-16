#ifndef LECTURER_HOME_H
#define LECTURER_HOME_H

#include <QMainWindow>

namespace Ui {
class Lecturer_Home;
}

class Lecturer_Home : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lecturer_Home(QWidget *parent = nullptr);
    ~Lecturer_Home();

private:
    Ui::Lecturer_Home *ui;
};

#endif // LECTURER_HOME_H
