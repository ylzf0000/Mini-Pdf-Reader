#-------------------------------------------------
#
# Project created by QtCreator 2018-04-13T15:32:41
#
#-------------------------------------------------

QT       += core gui

# Use Precompiled headers (PCH)
PRECOMPILED_HEADER  = stdafx.h

QMAKE_CXXFLAGS += /MP

TRANSLATIONS += client_en.ts
TRANSLATIONS += client_cn.ts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mini-Pdf-Reader
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    program.cpp \
    pdflistitemdelegate.cpp \
    pdflistmodel.cpp \
    pdflistview.cpp \
    pdfprinttool.cpp \
    FzPdf/mupdftool.cpp

HEADERS += \
        mainwindow.h \
    stdafx.h \
    program.h \
    pdflistitemdelegate.h \
    pdflistmodel.h \
    pdflistview.h \
    pdfprinttool.h \
    FzPdf/fz_header.h \
    FzPdf/mupdftool.h

FORMS += \
        mainwindow.ui

# MuPdf

INCLUDEPATH += $$PWD/thirdparty/mupdf/include
DEPENDPATH += $$PWD/thirdparty/mupdf/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/thirdparty/mupdf/lib/release/ -llibmupdf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/thirdparty/mupdf/lib/debug/ -llibmupdf

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/thirdparty/mupdf/lib/release/libmupdf.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/thirdparty/mupdf/lib/debug/libmupdf.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/thirdparty/mupdf/lib/release/ -llibresources
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/thirdparty/mupdf/lib/debug/ -llibresources

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/thirdparty/mupdf/lib/release/libresources.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/thirdparty/mupdf/lib/debug/libresources.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/thirdparty/mupdf/lib/release/ -llibthirdparty
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/thirdparty/mupdf/lib/debug/ -llibthirdparty

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/thirdparty/mupdf/lib/release/libthirdparty.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/thirdparty/mupdf/lib/debug/libthirdparty.lib

RESOURCES += \
    res.qrc
