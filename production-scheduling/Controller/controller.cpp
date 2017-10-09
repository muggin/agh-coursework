#include "controller.h"

Controller::Controller(Algorithm * algorithm, MainWindow * window, Database * database, QObject *parent) : QObject(parent)
{
    this->algorithm = algorithm;
    this->database = database;
    this->settingsWidget = window->ui->mAlgorithmWidget;
    this->statisticsWidget = window->ui->mStatisticWidget;
    this->blockPlotWidget = window->ui->mBlockPlot;
    this->dataWidget=window->ui->mDataWidget;
    this->dataWidget->setDatabase(this->database);



    connect(this->dataWidget,SIGNAL(newDataStructure(DataStructure*)),this->database,SLOT(onNewDataStructure(DataStructure*)));
    connect(this->database,SIGNAL(databaseChanged(Database*)),this->blockPlotWidget,SLOT(onDataChanged(Database*)));
    connect(settingsWidget, SIGNAL(runAlgorithm()), this->database, SLOT(completeJobs()));
    connect(settingsWidget, SIGNAL(runAlgorithm()), statisticsWidget, SLOT(clearStatistics()));
    connect(settingsWidget, SIGNAL(runAlgorithm()), window, SLOT(onRunAlgorithm()));
    connect(settingsWidget, SIGNAL(runAlgorithm(const AlgorithmSettings &)), algorithm, SLOT(onRunAlgorithm(const AlgorithmSettings &)));
    connect(algorithm, SIGNAL(newBestChromosom(Database*)), blockPlotWidget, SLOT(onDataChanged(Database*)));

    connect(algorithm, SIGNAL(newBestChromosom(Database*)), blockPlotWidget, SLOT(onDataChanged(Database*)));
    connect(algorithm, SIGNAL(newStatistics(const AlgorithmStatistics &)), statisticsWidget, SLOT(updateStatistics(const AlgorithmStatistics &)));
}

