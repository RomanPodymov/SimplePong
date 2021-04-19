TEMPLATE = app

QT += core gui widgets

CONFIG += c++17 warn_on

SOURCES += \
    ball.cpp \
    main.cpp \
    gameentity.cpp \
    gamemanager.cpp \
    gameview.cpp \
    paddle.cpp

HEADERS += \
    ball.h \
    gameentity.h \
    gamemanager.h \
    gameview.h \
    paddle.h
