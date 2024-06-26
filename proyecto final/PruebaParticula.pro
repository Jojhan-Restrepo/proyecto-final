QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bala.cpp \
    Jugador.cpp \
    Particula.cpp \
    PropQGRaphicsView.cpp \
    balaenemigo.cpp \
    enemigos.cpp \
    entidad.cpp \
    invocacionjug.cpp \
    main.cpp \
    mainwindow.cpp \
    proyectil.cpp \
    trampas.cpp \
    trampas2.cpp

HEADERS += \
    Bala.h \
    Jugador.h \
    Particula.h \
    PropQGraphicsView.h \
    balaenemigo.h \
    enemigos.h \
    entidad.h \
    invocacionjug.h \
    mainwindow.h \
    proyectil.h \
    trampas.h \
    trampas2.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background.qrc \
    sprite.qrc

DISTFILES +=
