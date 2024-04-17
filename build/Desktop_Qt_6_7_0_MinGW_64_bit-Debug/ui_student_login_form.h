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
#include <QtWidgets/QComboBox>
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
    QGroupBox *appGroup;
    QLabel *presenceIcon;
    QLabel *appTitleLabel;
    QLabel *appSubtitleLabel;
    QGroupBox *formGroup;
    QLabel *background;
    QGroupBox *studentIdGroup;
    QLabel *studentIdHud;
    QLineEdit *studentIdTextbox;
    QGroupBox *pinGroup;
    QLabel *pinHud;
    QLineEdit *pinTextbox;
    QGroupBox *collegeGroup;
    QComboBox *collegeCombobox;
    QLabel *collegeHud;
    QPushButton *loginButton;
    QPushButton *backButton;

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
        presenceIcon->setPixmap(QPixmap(QString::fromUtf8(":/res/assets/presence_logo.png")));
        presenceIcon->setScaledContents(false);
        appTitleLabel = new QLabel(appGroup);
        appTitleLabel->setObjectName("appTitleLabel");
        appTitleLabel->setGeometry(QRect(140, 80, 151, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Poppins")});
        font.setWeight(QFont::ExtraBold);
        font.setItalic(false);
        appTitleLabel->setFont(font);
        appTitleLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	color: #FFFFFF;\n"
"	font-family: Poppins;\n"
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
        formGroup = new QGroupBox(centralwidget);
        formGroup->setObjectName("formGroup");
        formGroup->setGeometry(QRect(0, 210, 360, 430));
        formGroup->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 0px;\n"
"	border-radius: 0px;\n"
"}"));
        background = new QLabel(formGroup);
        background->setObjectName("background");
        background->setGeometry(QRect(0, 0, 360, 430));
        background->setPixmap(QPixmap(QString::fromUtf8(":/res/assets/form_background.png")));
        background->setScaledContents(true);
        studentIdGroup = new QGroupBox(formGroup);
        studentIdGroup->setObjectName("studentIdGroup");
        studentIdGroup->setEnabled(true);
        studentIdGroup->setGeometry(QRect(55, 110, 250, 40));
        studentIdGroup->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 0px;\n"
"	border-radius: 0px;\n"
"	background: none\n"
"}"));
        studentIdGroup->setAlignment(Qt::AlignCenter);
        studentIdGroup->setFlat(true);
        studentIdHud = new QLabel(studentIdGroup);
        studentIdHud->setObjectName("studentIdHud");
        studentIdHud->setGeometry(QRect(0, 0, 250, 40));
        studentIdHud->setStyleSheet(QString::fromUtf8("QLabel {	\n"
"	background: none;\n"
"}"));
        studentIdHud->setPixmap(QPixmap(QString::fromUtf8(":/res/assets/login_field.png")));
        studentIdHud->setScaledContents(false);
        studentIdHud->setAlignment(Qt::AlignCenter);
        studentIdTextbox = new QLineEdit(studentIdGroup);
        studentIdTextbox->setObjectName("studentIdTextbox");
        studentIdTextbox->setGeometry(QRect(15, 0, 220, 30));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Poppins")});
        font2.setWeight(QFont::Medium);
        font2.setItalic(false);
        studentIdTextbox->setFont(font2);
        studentIdTextbox->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"	background-color: transparent;\n"
"	border: 0px;\n"
"	color: #FFFFFF;\n"
"	font-family: Poppins;\n"
"	font-size: 12px;\n"
"	font-style: normal;\n"
"	font-weight: 500;\n"
"	line-height: normal;\n"
"}"));
        studentIdTextbox->setMaxLength(9);
        pinGroup = new QGroupBox(formGroup);
        pinGroup->setObjectName("pinGroup");
        pinGroup->setEnabled(true);
        pinGroup->setGeometry(QRect(55, 160, 250, 40));
        pinGroup->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 0px;\n"
"	border-radius: 0px;\n"
"	background: none\n"
"}"));
        pinGroup->setAlignment(Qt::AlignCenter);
        pinGroup->setFlat(true);
        pinHud = new QLabel(pinGroup);
        pinHud->setObjectName("pinHud");
        pinHud->setGeometry(QRect(0, 0, 250, 40));
        pinHud->setStyleSheet(QString::fromUtf8("QLabel {	\n"
"	background: none;\n"
"}"));
        pinHud->setPixmap(QPixmap(QString::fromUtf8(":/res/assets/login_field.png")));
        pinHud->setScaledContents(false);
        pinHud->setAlignment(Qt::AlignCenter);
        pinTextbox = new QLineEdit(pinGroup);
        pinTextbox->setObjectName("pinTextbox");
        pinTextbox->setGeometry(QRect(15, 0, 220, 30));
        pinTextbox->setFont(font2);
        pinTextbox->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"	background-color: transparent;\n"
"	border: 0px;\n"
"	color: #FFFFFF;\n"
"	font-family: Poppins;\n"
"	font-size: 12px;\n"
"	font-style: normal;\n"
"	font-weight: 500;\n"
"	line-height: normal;\n"
"}"));
        pinTextbox->setMaxLength(6);
        pinTextbox->setEchoMode(QLineEdit::Password);
        collegeGroup = new QGroupBox(formGroup);
        collegeGroup->setObjectName("collegeGroup");
        collegeGroup->setEnabled(true);
        collegeGroup->setGeometry(QRect(55, 210, 250, 40));
        collegeGroup->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 0px;\n"
"	border-radius: 0px;\n"
"	background: none\n"
"}"));
        collegeGroup->setAlignment(Qt::AlignCenter);
        collegeGroup->setFlat(true);
        collegeCombobox = new QComboBox(collegeGroup);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/assets/cict_avatar.png"), QSize(), QIcon::Normal, QIcon::Off);
        collegeCombobox->addItem(icon, QString());
        collegeCombobox->addItem(QString());
        collegeCombobox->addItem(QString());
        collegeCombobox->addItem(QString());
        collegeCombobox->addItem(QString());
        collegeCombobox->addItem(QString());
        collegeCombobox->addItem(QString());
        collegeCombobox->addItem(QString());
        collegeCombobox->addItem(QString());
        collegeCombobox->addItem(QString());
        collegeCombobox->setObjectName("collegeCombobox");
        collegeCombobox->setGeometry(QRect(12, 0, 226, 30));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(collegeCombobox->sizePolicy().hasHeightForWidth());
        collegeCombobox->setSizePolicy(sizePolicy);
        collegeCombobox->setFont(font2);
        collegeCombobox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"	background-color: transparent;\n"
"	border: 0px;\n"
"	color: #FFFFFF;\n"
"	font-family: Poppins;\n"
"	font-size: 12px;\n"
"	font-style: normal;\n"
"	font-weight: 500;\n"
"	line-height: normal;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"    margin-top: 4px;\n"
"}\n"
"\n"
"QComboBox QScrollBar::add-page:vertical,\n"
"QComboBox QScrollBar::sub-page:vertical {\n"
"    background: none;\n"
"	border-style: solid;\n"
"}"));
        collegeCombobox->setEditable(false);
        collegeCombobox->setMaxVisibleItems(8);
        collegeCombobox->setInsertPolicy(QComboBox::InsertAfterCurrent);
        collegeCombobox->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
        collegeHud = new QLabel(collegeGroup);
        collegeHud->setObjectName("collegeHud");
        collegeHud->setGeometry(QRect(0, 0, 250, 40));
        collegeHud->setStyleSheet(QString::fromUtf8("QLabel {	\n"
"	background: none;\n"
"}"));
        collegeHud->setPixmap(QPixmap(QString::fromUtf8(":/res/assets/login_field.png")));
        collegeHud->setScaledContents(false);
        collegeHud->setAlignment(Qt::AlignCenter);
        collegeHud->raise();
        collegeCombobox->raise();
        loginButton = new QPushButton(formGroup);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(75, 330, 210, 40));
        loginButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border: 0px;\n"
"	border-radius: 0px;\n"
"	background: none;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/assets/login_button.png"), QSize(), QIcon::Normal, QIcon::Off);
        loginButton->setIcon(icon1);
        loginButton->setIconSize(QSize(210, 40));
        loginButton->setFlat(true);
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(15, 15, 30, 30));
        backButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border: 0px;\n"
"	border-radius: 0px;\n"
"	background: none;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/res/assets/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        backButton->setIcon(icon2);
        backButton->setIconSize(QSize(30, 30));
        backButton->setFlat(true);
        Student_Login_Form->setCentralWidget(centralwidget);

        retranslateUi(Student_Login_Form);

        QMetaObject::connectSlotsByName(Student_Login_Form);
    } // setupUi

    void retranslateUi(QMainWindow *Student_Login_Form)
    {
        Student_Login_Form->setWindowTitle(QCoreApplication::translate("Student_Login_Form", "Student Login Form", nullptr));
        appGroup->setTitle(QString());
        presenceIcon->setText(QString());
        formGroup->setTitle(QString());
        background->setText(QString());
        studentIdGroup->setTitle(QString());
        studentIdHud->setText(QString());
        studentIdTextbox->setPlaceholderText(QCoreApplication::translate("Student_Login_Form", "Student No.", nullptr));
        pinGroup->setTitle(QString());
        pinHud->setText(QString());
        pinTextbox->setPlaceholderText(QCoreApplication::translate("Student_Login_Form", "Pin", nullptr));
        collegeGroup->setTitle(QString());
        collegeCombobox->setItemText(0, QCoreApplication::translate("Student_Login_Form", "CICT", nullptr));
        collegeCombobox->setItemText(1, QCoreApplication::translate("Student_Login_Form", "CAS", nullptr));
        collegeCombobox->setItemText(2, QCoreApplication::translate("Student_Login_Form", "CBM", nullptr));
        collegeCombobox->setItemText(3, QCoreApplication::translate("Student_Login_Form", "COC", nullptr));
        collegeCombobox->setItemText(4, QCoreApplication::translate("Student_Login_Form", "COD", nullptr));
        collegeCombobox->setItemText(5, QCoreApplication::translate("Student_Login_Form", "COE", nullptr));
        collegeCombobox->setItemText(6, QCoreApplication::translate("Student_Login_Form", "COL", nullptr));
        collegeCombobox->setItemText(7, QCoreApplication::translate("Student_Login_Form", "COM", nullptr));
        collegeCombobox->setItemText(8, QCoreApplication::translate("Student_Login_Form", "CON", nullptr));
        collegeCombobox->setItemText(9, QCoreApplication::translate("Student_Login_Form", "PESCAR", nullptr));

        collegeCombobox->setPlaceholderText(QCoreApplication::translate("Student_Login_Form", "College", nullptr));
        collegeHud->setText(QString());
        loginButton->setText(QString());
        backButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Student_Login_Form: public Ui_Student_Login_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENT_LOGIN_FORM_H
