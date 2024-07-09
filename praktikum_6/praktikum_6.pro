QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AbstractUI.cpp \
    Aktive.cpp \
    AttackController.cpp \
    Character.cpp \
    Door.cpp \
    DungeonCrawler.cpp \
    Floor.cpp \
    GraphicalUI.cpp \
    GuardController.cpp \
    Level.cpp \
    Levelchanger.cpp \
    Lootchest.cpp \
    MyButton.cpp \
    Passive.cpp \
    Pit.cpp \
    Portal.cpp \
    Ramp.cpp \
    RandomController.cpp \
    StartScreem.cpp \
    StationaryController.cpp \
    Switch.cpp \
    TerminalUI.cpp \
    Tile.cpp \
    Wall.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AbstractUI.h \
    Aktive.h \
    AttackController.h \
    Character.h \
    Door.h \
    DungeonCrawler.h \
    Floor.h \
    GraphicalUI.h \
    GuardController.h \
    Level.h \
    Levelchanger.h \
    List.h \
    List_impl.h \
    Lootchest.h \
    MyButton.h \
    Passive.h \
    Pit.h \
    Portal.h \
    Ramp.h \
    RandomController.h \
    StartScreem.h \
    StationaryController.h \
    Switch.h \
    TerminalUI.h \
    Tile.h \
    Wall.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    praktikum_6.pro.user
