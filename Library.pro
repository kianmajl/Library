QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addbook.cpp \
    addgroup.cpp \
    authentication.cpp \
    book.cpp \
    book_item.cpp \
    booklist_admin.cpp \
    booklist_user.cpp \
    compose.cpp \
    edit_user_data.cpp \
    edit_user_profile.cpp \
    editbook.cpp \
    group_item.cpp \
    groupbooks.cpp \
    inbox.cpp \
    issuedbooks_admin.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow_user.cpp \
    message.cpp \
    outbox.cpp \
    returnbook.cpp \
    user.cpp

HEADERS += \
    addbook.h \
    addgroup.h \
    authentication.h \
    book.h \
    book_item.h \
    booklist_admin.h \
    booklist_user.h \
    compose.h \
    edit_user_data.h \
    edit_user_profile.h \
    editbook.h \
    group_item.h \
    groupbooks.h \
    inbox.h \
    issuedbooks_admin.h \
    mainwindow.h \
    mainwindow_user.h \
    message.h \
    outbox.h \
    returnbook.h \
    user.h

FORMS += \
    addbook.ui \
    addgroup.ui \
    authentication.ui \
    booklist_admin.ui \
    booklist_user.ui \
    compose.ui \
    edit_user_data.ui \
    edit_user_profile.ui \
    editbook.ui \
    groupbooks.ui \
    inbox.ui \
    issuedbooks_admin.ui \
    mainwindow.ui \
    mainwindow_user.ui \
    outbox.ui \
    returnbook.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
