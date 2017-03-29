#-------------------------------------------------
#
# Project created by QtCreator 2015-07-28T17:57:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = big_homework
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filterdialog.cpp \
    filtertopicdialog.cpp \
    linelinelayout.cpp \
    circlelinelayout.cpp \
    topicdialog.cpp \
    topicgraph.cpp \
    paperconferenceauthorgraph.cpp \
    pointcolor.cpp \
    hellolayout.cpp \
    moreforpaperdialog.cpp \
    docdialog.cpp \
    searchresultdialog.cpp \
    informationdialog.cpp \
    mypoint.cpp \
    mypointedge.cpp \
    dialog.cpp \
    forcelayout.cpp \
    nobezierdialog.cpp \
    weightlayout.cpp \
    cartoondialog.cpp

HEADERS  += \
    graph.h \
    node.h \
    filterdialog.h \
    filtertopicdialog.h \
    undirectededge.h \
    directededge.h \
    paperconferenceauthornode.h \
    topicnode.h \
    topicgraph.h \
    topicdialog.h \
    paperconferenceauthorgraph.h \
    circlelinelayout.h \
    docnode.h \
    edge.h \
    informationdialog.h \
    linelinelayout.h \
    mainwindow.h \
    pointcolor.h \
    hellolayout.h \
    moreforpaperdialog.h \
    docdialog.h \
    searchresultdialog.h \
    mypoint.h \
    mypointedge.h \
    dialog.h \
    forcelayout.h \
    nobezierdialog.h \
    weightlayout.h \
    cartoondialog.h

FORMS    += mainwindow.ui \
    informationdialog.ui \
    topicdialog.ui \
    filterdialog.ui \
    filtertopicdialog.ui \
    moreforpaperdialog.ui \
    docdialog.ui \
    searchresultdialog.ui \
    dialog.ui \
    nobezierdialog.ui \
    cartoondialog.ui

RESOURCES += \
    my_background.qrc
