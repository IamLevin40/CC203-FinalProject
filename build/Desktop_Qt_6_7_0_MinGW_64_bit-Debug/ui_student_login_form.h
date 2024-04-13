/********************************************************************************
** Form generated from reading UI file 'student_login_form.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDENT_LOGIN_FORM_H
#define UI_STUDENT_LOGIN_FORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Student_Login_Form
{
public:
    QWidget *centralwidget;
    QPushButton *backButton;
    QGroupBox *appGroup;
    QLabel *presenceIcon;
    QLabel *appTitleLabel;
    QLabel *appSubtitleLabel;
    QGroupBox *groupBox;
    QLabel *background;
    QLineEdit *studentNumTextbox;
    QLabel *label;

    void setupUi(QMainWindow *Student_Login_Form)
    {
        if (Student_Login_Form->objectName().isEmpty())
            Student_Login_Form->setObjectName("Student_Login_Form");
        Student_Login_Form->resize(360, 640);
        Student_Login_Form->setStyleSheet(QString::fromUtf8("QWidget {\n"
"	background-color: #000F2A;\n"
"}\n"
""));
        centralwidget = new QWidget(Student_Login_Form);
        centralwidget->setObjectName("centralwidget");
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(15, 15, 30, 30));
        backButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border: 0px;\n"
"	border-radius: 0px;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/assets/backButton.png"), QSize(), QIcon::Normal, QIcon::Off);
        backButton->setIcon(icon);
        backButton->setIconSize(QSize(30, 30));
        backButton->setFlat(true);
        appGroup = new QGroupBox(centralwidget);
        appGroup->setObjectName("appGroup");
        appGroup->setGeometry(QRect(30, 20, 300, 200));
        appGroup->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 0px;\n"
"	border-radius: 0px;\n"
"}"));
        appGroup->setFlat(true);
        appGroup->setCheckable(false);
        presenceIcon = new QLabel(appGroup);
        presenceIcon->setObjectName("presenceIcon");
        presenceIcon->setGeometry(QRect(0, 0, 200, 200));
        presenceIcon->setStyleSheet(QString::fromUtf8(""));
        presenceIcon->setPixmap(QPixmap(QString::fromUtf8(":/res/assets/presenceLogo.png")));
        presenceIcon->setScaledContents(false);
        appTitleLabel = new QLabel(appGroup);
        appTitleLabel->setObjectName("appTitleLabel");
        appTitleLabel->setGeometry(QRect(140, 80, 151, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Montserrat ExtraBold")});
        font.setWeight(QFont::ExtraBold);
        font.setItalic(false);
        appTitleLabel->setFont(font);
        appTitleLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	color: #FFFFFF;\n"
"	font-size: 35px;\n"
"	font-style: normal;\n"
"	font-weight: 800;\n"
"	line-height: normal;\n"
"}\n"
""));
        appTitleLabel->setText(QString::fromUtf8("resence"));
        appSubtitleLabel = new QLabel(appGroup);
        appSubtitleLabel->setObjectName("appSubtitleLabel");
        appSubtitleLabel->setGeometry(QRect(160, 110, 131, 20));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Montserrat Medium")});
        font1.setBold(false);
        font1.setItalic(false);
        appSubtitleLabel->setFont(font1);
        appSubtitleLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	color: #15CAE3;\n"
"	font-size: 9px;\n"
"	font-style: normal;\n"
"	font-weight: 400;\n"
"	line-height: normal;\n"
"}"));
        appSubtitleLabel->setText(QString::fromUtf8("KEEP IN TRACK EVERYTIME"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 210, 360, 430));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 0px;\n"
"	border-radius: 0px;\n"
"}"));
        background = new QLabel(groupBox);
        background->setObjectName("background");
        background->setGeometry(QRect(0, 0, 360, 430));
        background->setPixmap(QPixmap(QString::fromUtf8(":/res/assets/formBackground.png")));
        background->setScaledContents(true);
        studentNumTextbox = new QLineEdit(groupBox);
        studentNumTextbox->setObjectName("studentNumTextbox");
        studentNumTextbox->setGeometry(QRect(70, 140, 220, 30));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Poppins")});
        font2.setWeight(QFont::Medium);
        font2.setItalic(false);
        studentNumTextbox->setFont(font2);
        studentNumTextbox->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 0px;\n"
"color: #FFFFFF;\n"
"font-size: 12px;\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"line-height: normal;"));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(55, 140, 250, 40));
        label->setStyleSheet(QString::fromUtf8("background: none;"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/res/assets/inputFieldHud.png")));
        label->setScaledContents(false);
        background->raise();
        label->raise();
        studentNumTextbox->raise();
        Student_Login_Form->setCentralWidget(centralwidget);
        appGroup->raise();
        groupBox->raise();
        backButton->raise();

        retranslateUi(Student_Login_Form);

        QMetaObject::connectSlotsByName(Student_Login_Form);
    } // setupUi

    void retranslateUi(QMainWindow *Student_Login_Form)
    {
        Student_Login_Form->setWindowTitle(QCoreApplication::translate("Student_Login_Form", "Student Login Form", nullptr));
        backButton->setText(QString());
        appGroup->setTitle(QString());
        presenceIcon->setText(QString());
        groupBox->setTitle(QString());
        background->setText(QString());
        studentNumTextbox->setPlaceholderText(QCoreApplication::translate("Student_Login_Form", "Student No.", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Student_Login_Form: public Ui_Student_Login_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENT_LOGIN_FORM_H
