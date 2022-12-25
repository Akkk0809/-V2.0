#-------------------------------------------------
#
# Project title 你帮我助物品交换系统
# 版本：V2.0
# Project created by 艾科Akkk 2022-12-19   上海
#
#-------------------------------------------------

QT       += core gui
QT       +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    register_page.cpp \
    userdate.cpp

HEADERS += \
    MainWindow.h \
    register_page.h \
    userdate.h

FORMS += \
    MainWindow.ui \
    register_page.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    iamges.qrc

DISTFILES +=
