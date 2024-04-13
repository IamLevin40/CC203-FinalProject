/********************************************************************************
** Form generated from reading UI file 'selectProfession.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTPROFESSION_H
#define UI_SELECTPROFESSION_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *appGroup;
    QLabel *presenceIcon;
    QLabel *appTitleLabel;
    QLabel *appSubtitleLabel;
    QGroupBox *selectionGroup;
    QLabel *selectTitleLabel;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(360, 640);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget {\n"
"	background-color: #000F2A;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        appGroup = new QGroupBox(centralwidget);
        appGroup->setObjectName("appGroup");
        appGroup->setGeometry(QRect(30, 100, 300, 200));
        appGroup->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 0px;\n"
"	border-radius: 0px;\n"
"}"));
        appGroup->setFlat(true);
        appGroup->setCheckable(false);
        presenceIcon = new QLabel(appGroup);
        presenceIcon->setObjectName("presenceIcon");
        presenceIcon->setGeometry(QRect(0, 0, 201, 200));
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
"}"));
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
        selectionGroup = new QGroupBox(centralwidget);
        selectionGroup->setObjectName("selectionGroup");
        selectionGroup->setGeometry(QRect(30, 330, 300, 230));
        selectionGroup->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 0px;\n"
"	border-radius: 0px;\n"
"}"));
        selectTitleLabel = new QLabel(selectionGroup);
        selectTitleLabel->setObjectName("selectTitleLabel");
        selectTitleLabel->setGeometry(QRect(10, 10, 271, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Poppins")});
        font2.setWeight(QFont::Medium);
        font2.setItalic(false);
        selectTitleLabel->setFont(font2);
        selectTitleLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	color: #FFFFFF;\n"
"	font-size: 24px;\n"
"	font-style: normal;\n"
"	font-weight: 500;\n"
"	line-height: normal;\n"
"}"));
        selectTitleLabel->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(selectionGroup);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 70, 125, 155));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/assets/studentButton.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(125, 155));
        pushButton->setFlat(true);
        pushButton_2 = new QPushButton(selectionGroup);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(160, 70, 125, 155));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/assets/lecturerButton.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon1);
        pushButton_2->setIconSize(QSize(125, 155));
        pushButton_2->setCheckable(false);
        pushButton_2->setFlat(true);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        pushButton->setDefault(false);
        pushButton_2->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Select Profession", nullptr));
        appGroup->setTitle(QString());
        presenceIcon->setText(QString());
        selectionGroup->setTitle(QString());
        selectTitleLabel->setText(QCoreApplication::translate("MainWindow", "Select your profession", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTPROFESSION_H
