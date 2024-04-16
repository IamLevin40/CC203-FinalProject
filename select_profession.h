#ifndef SELECT_PROFESSION_H
#define SELECT_PROFESSION_H

#include <QMainWindow>
#include "student_login_form.h"
#include "lecturer_login_form.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_studentButton_clicked();
    void on_lecturerButton_clicked();

private:
    Ui::MainWindow *ui;
    Student_Login_Form *student_login_form;
    Lecturer_Login_Form *lecturer_login_form;

};
#endif // SELECT_PROFESSION_H
