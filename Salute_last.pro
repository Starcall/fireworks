QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ButtonsFactory.cpp \
    Explosion.cpp \
    ExplosionFactory.cpp \
    Firework.cpp \
    SaluteFactory.cpp \
    main.cpp \
    Game.cpp

HEADERS += \
    ButtonsFactory.h \
    Explosion.h \
    ExplosionFactory.h \
    Firework.h \
    Game.h \
    SaluteFactory.h \
    StaticData.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Pictures.qrc
