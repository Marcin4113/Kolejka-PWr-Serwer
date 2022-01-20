QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    server_connection.cpp

HEADERS += \
    mainwindow.h \
    server_connection.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Kolejka_PWr_Serwer_pl_PL.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/ -lwsock32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/ -lwsock32
else:unix: LIBS += -L$$PWD/libs/ -lwsock32

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs
