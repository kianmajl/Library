QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addbook.cpp \
    authentication.cpp \
    book.cpp \
    booklist_admin.cpp \
    compose.cpp \
    edit_user_data.cpp \
    edit_user_profile.cpp \
    editbook.cpp \
    groupbooks.cpp \
    inbox.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow_user.cpp \
    message.cpp \
    outbox.cpp \
    user.cpp

HEADERS += \
    addbook.h \
    authentication.h \
    book.h \
    booklist_admin.h \
    compose.h \
    edit_user_data.h \
    edit_user_profile.h \
    editbook.h \
    groupbooks.h \
    inbox.h \
    mainwindow.h \
    mainwindow_user.h \
    message.h \
    outbox.h \
    user.h

FORMS += \
    addbook.ui \
    authentication.ui \
    booklist_admin.ui \
    compose.ui \
    edit_user_data.ui \
    edit_user_profile.ui \
    editbook.ui \
    groupbooks.ui \
    inbox.ui \
    mainwindow.ui \
    mainwindow_user.ui \
    outbox.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
