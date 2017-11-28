QT += core script sql
QT -= gui

CONFIG += c++11

TARGET = Monita_Formula_Service
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mysql.cpp \
    config.cpp \
    redis.cpp \
    monita_log.cpp \
    worker.cpp

HEADERS += \
    mysql.h \
    utama.h \
    config.h \
    redis.h \
    monita_log.h \
    worker.h

INCLUDEPATH += /usr/local/include/hiredis
LIBS += -L/usr/local/lib -lhiredis
