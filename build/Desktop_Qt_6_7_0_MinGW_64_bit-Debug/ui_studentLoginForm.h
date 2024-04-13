/********************************************************************************
** Form generated from reading UI file 'studentLoginForm.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDENTLOGINFORM_H
#define UI_STUDENTLOGINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StudentLoginForm
{
public:

    void setupUi(QWidget *StudentLoginForm)
    {
        if (StudentLoginForm->objectName().isEmpty())
            StudentLoginForm->setObjectName("StudentLoginForm");
        StudentLoginForm->resize(360, 640);

        retranslateUi(StudentLoginForm);

        QMetaObject::connectSlotsByName(StudentLoginForm);
    } // setupUi

    void retranslateUi(QWidget *StudentLoginForm)
    {
        StudentLoginForm->setWindowTitle(QCoreApplication::translate("StudentLoginForm", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StudentLoginForm: public Ui_StudentLoginForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENTLOGINFORM_H
