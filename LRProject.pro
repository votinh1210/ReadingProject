#-------------------------------------------------
#
# Project created by QtCreator 2016-01-31T15:49:15
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LRProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    languagereadingfile.cpp \
    goldendictLib/bgl_babylon.cc \
    goldendictLib/dictionary.cc \
    goldendictLib/gddebug.cc \
    goldendictLib/htmlescape.cc \
    goldendictLib/iconv.cc \
    goldendictLib/ufile.cc \
    goldendictLib/config.cc \
    goldendictLib/fsencoding.cc \
    goldendictLib/langcoder.cc \
    goldendictLib/mutex.cc \
    goldendictLib/wstring.cc \
    goldendictLib/atomic_rename.cc \
    goldendictLib/wstring_qt.cc \
    goldendictLib/folding.cc \
    goldendictLib/language.cc

HEADERS  += mainwindow.h \
    languagereadingfile.h \
    goldendictLib/bgl_babylon.hh \
    goldendictLib/dictionary.hh \
    goldendictLib/gddebug.hh \
    goldendictLib/htmlescape.hh \
    goldendictLib/iconv.hh \
    goldendictLib/ufile.hh \
    goldendictLib/config.hh \
    goldendictLib/ex.hh \
    goldendictLib/fsencoding.hh \
    goldendictLib/langcoder.hh \
    goldendictLib/mutex.hh \
    goldendictLib/qt4x5.hh \
    goldendictLib/sptr.hh \
    goldendictLib/wstring.hh \
    goldendictLib/atomic_rename.hh \
    goldendictLib/wstring_qt.hh \
    goldendictLib/folding.hh \
    goldendictLib/inc_case_folding.hh \
    goldendictLib/inc_diacritic_folding.hh

FORMS   += mainwindow.ui

ICON = LRProject.ico

win32:LIBS += -liconv
