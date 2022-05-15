QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client_connection.cpp \
    main.cpp \
    main_window.cpp \
    working_window.cpp

HEADERS += \
    client_connection.h \
    defs.h \
    main_window.h \
    working_window.h

FORMS += \
    main_window.ui \
    working_window.ui

TRANSLATIONS += \
    Kolejka_PWr_Stanowisko_pl_PL.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/ -lwsock32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/ -lwsock32
else:unix: LIBS += -L$$PWD/libs/ -lwsock32

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs
