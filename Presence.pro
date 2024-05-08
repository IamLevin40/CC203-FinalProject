greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += core gui sql axcontainer multimedia multimediawidgets
CONFIG += c++17

include(QtQrCodeGenerator/QtQrCodeGenerator.pri)
# INCLUDEPATH += $$PWD/qzxing/include
# LIBS += -L$$PWD/qzxing/lib -lqzxing


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    global_main.cpp \
    lecturer_attendance_alternative.cpp \
    lecturer_attendance_list.cpp \
    lecturer_attendance_scanner.cpp \
    lecturer_classes_info.cpp \
    lecturer_classes_list.cpp \
    lecturer_home_auth.cpp \
    lecturer_home_qr.cpp \
    lecturer_login_form.cpp \
    lecturer_student_record.cpp \
    main.cpp \
    select_profession.cpp \
    student_home_auth.cpp \
    student_home_qr.cpp \
    student_login_form.cpp

HEADERS += \
    global_main.h \
    lecturer_attendance_alternative.h \
    lecturer_attendance_list.h \
    lecturer_attendance_scanner.h \
    lecturer_classes_info.h \
    lecturer_classes_list.h \
    lecturer_home_auth.h \
    lecturer_home_qr.h \
    lecturer_login_form.h \
    lecturer_student_record.h \
    select_profession.h \
    student_home_auth.h \
    student_home_qr.h \
    student_login_form.h

FORMS += \
    lecturer_attendance_alternative.ui \
    lecturer_attendance_list.ui \
    lecturer_attendance_scanner.ui \
    lecturer_classes_info.ui \
    lecturer_classes_list.ui \
    lecturer_home_auth.ui \
    lecturer_home_qr.ui \
    lecturer_login_form.ui \
    lecturer_student_record.ui \
    select_profession.ui \
    student_home_auth.ui \
    student_home_qr.ui \
    student_login_form.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

