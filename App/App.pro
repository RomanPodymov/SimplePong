TEMPLATE = app

QT += core gui widgets

CONFIG += c++17 warn_on

SOURCES += \
    ball.cpp \
    main.cpp \
    gameentity.cpp \
    gamemanager.cpp \
    gameview.cpp \
    mainwidget.cpp \
    paddle.cpp \
    paddleopponent.cpp

HEADERS += \
    ball.h \
    gameentity.h \
    gamemanager.h \
    gameview.h \
    mainwidget.h \
    paddle.h \
    paddleopponent.h

TRANSLATIONS += \
    Translations/Translations_MainWidget_en.ts \
    Translations/Translations_MainWidget_cs.ts

RESOURCES += \
    mainwidgetresources.qrc
