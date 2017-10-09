#-------------------------------------------------
#
# Project created by QtCreator 2014-06-02T15:14:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Projekt-Harmonogramowanie
TEMPLATE = app


SOURCES += main.cpp \
    Algorithm/Algorithm.cpp \
    Algorithm/Chromosom.cpp \
    Controller/controller.cpp \
    DataModification/Database.cpp \
    DataModification/Job.cpp \
    DataModification/Machine.cpp \
    DataModification/Task.cpp \
    GeneticOperators/CrossoverOperators/CrossoverOnePoint.cpp \
    GeneticOperators/CrossoverOperators/CrossoverOperator.cpp \
    GeneticOperators/CrossoverOperators/CrossoverTwoPoint.cpp \
    GeneticOperators/MutationOperators/MutationInversion.cpp \
    GeneticOperators/MutationOperators/MutationOperator.cpp \
    GeneticOperators/MutationOperators/MutationReverse.cpp \
    GeneticOperators/MutationOperators/MutationSwappingPoint.cpp \
    GeneticOperators/MutationOperators/MutationSwappingSegment.cpp \
    GeneticOperators/SelectionOperators/SelectionOperator.cpp \
    GeneticOperators/SelectionOperators/SelectionTournament.cpp \
    GUI/blockplot.cpp \
    GUI/extqcpstatisticalbox.cpp \
    GUI/mainwindow.cpp \
    GUI/qcustomplot.cpp \
    GUI/qspinboxenhenced.cpp \
    GUI/settingswidget.cpp \
    GUI/statisticsplotwidget.cpp \
    GUI/statisticswidget.cpp \
    GeneticOperators/MutationOperators/MutationDisplacement.cpp \
    GeneticOperators/SelectionOperators/SelectionRank.cpp \
    GUI/DataModificationWidgets/AddingWidget.cpp \
    GUI/DataModificationWidgets/DataWidget.cpp \
    GUI/DataModificationWidgets/DeletingWidget.cpp \
    GUI/DataModificationWidgets/EditingWidget.cpp

HEADERS  += Algorithm/Algorithm.h \
    Algorithm/Chromosom.h \
    Algorithm/SettingsStructures.h \
    Algorithm/StatisticsStructure.h \
    Controller/controller.h \
    DataModification/Database.h \
    DataModification/Job.h \
    DataModification/Machine.h \
    DataModification/Task.h \
    GeneticOperators/CrossoverOperators/CrossoverOnePoint.h \
    GeneticOperators/CrossoverOperators/CrossoverOperator.h \
    GeneticOperators/CrossoverOperators/CrossoverTwoPoint.h \
    GeneticOperators/MutationOperators/MutationInversion.h \
    GeneticOperators/MutationOperators/MutationOperator.h \
    GeneticOperators/MutationOperators/MutationReverse.h \
    GeneticOperators/MutationOperators/MutationSwapping.h \
    GeneticOperators/MutationOperators/MutationSwappingPoint.h \
    GeneticOperators/MutationOperators/MutationSwappingSegment.h \
    GeneticOperators/SelectionOperators/SelectionOperator.h \
    GeneticOperators/SelectionOperators/SelectionRoulette.h \
    GeneticOperators/SelectionOperators/SelectionTournament.h \
    GUI/blockplot.h \
    GUI/extqcpstatisticalbox.h \
    GUI/mainwindow.h \
    GUI/qcustomplot.h \
    GUI/qspinboxenhenced.h \
    GUI/settingswidget.h \
    GUI/statisticsplotwidget.h \
    GUI/statisticswidget.h \
    GUI/ui_mainwindow.h \
    DataModificationWidgets/DataStructure.h \
    GeneticOperators/MutationOperators/MutationDisplacement.h \
    GeneticOperators/SelectionOperators/SelectionRank.h \
    GUI/DataModificationWidgets/AddingWidget.h \
    GUI/DataModificationWidgets/DataStructure.h \
    GUI/DataModificationWidgets/DataWidget.h \
    GUI/DataModificationWidgets/DeletingWidget.h \
    GUI/DataModificationWidgets/EditingWidget.h

FORMS += \
    mainwindow.ui

UI_DIR=../Harmonogramowanie/GUI
