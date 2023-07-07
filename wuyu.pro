QT       += core gui multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    battlewidget.cpp \
    characterslices.cpp \
    creature.cpp \
    main.cpp \
    mainwidget.cpp \
    helpwidget.cpp\
    mapwidget.cpp \
    mymusicplayer.cpp \
    soundeffectpalyer.cpp \
    weapon.cpp\
    atkanimation.cpp\
    fadelabel.cpp

HEADERS += \
    battlewidget.h \
    characterslices.h \
    creature.h \
    mainwidget.h \
    helpwidget.h\
    mapwidget.h \
    mymusicplayer.h \
    soundeffectpalyer.h \
    weapon.h\
    atkanimation.h\
    fadelabel.h

FORMS += \
    battlewidget.ui \
    mainwidget.ui \
    helpwidget.ui \
    mapwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
