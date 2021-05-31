QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authentication.cpp \
    booklist_admin.cpp \
    edit_user_profile.cpp \
    groupbooks.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow_user.cpp \
    user.cpp

HEADERS += \
    authentication.h \
    booklist_admin.h \
    edit_user_profile.h \
    groupbooks.h \
    mainwindow.h \
    mainwindow_user.h \
    user.h

FORMS += \
    authentication.ui \
    booklist_admin.ui \
    edit_user_profile.ui \
    groupbooks.ui \
    mainwindow.ui \
    mainwindow_user.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
