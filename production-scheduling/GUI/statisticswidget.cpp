#include "statisticswidget.h"
#include <qapplication.h>

StatisticsWidget::StatisticsWidget(QWidget *parent) : QWidget(parent)
{
    this->widgetLayout = new QHBoxLayout();
    this->popStatisticsLayout = new QFormLayout();
    this->algStatisticsLayout = new QFormLayout();

    this->algStatisticsGroup = new QGroupBox("Algorithm Statistics");
    this->popStatisticsGroup = new QGroupBox("Population Statistics");
    this->plotStatisticsGroup = new QGroupBox("Fitness Plot");

    this->epochLabel = new QLabel("Current epoch");
    this->meanCrossCountLabel = new QLabel("Crossover count (mean)");
    this->meanMutCountLabel = new QLabel("Mutation count (mean)");
    this->meanInvalidSolutionsLabel = new QLabel("Invalid solutions (mean)");

    this->popFitnessLabel = new QLabel("Population fitness");
    this->bestFitnessLabel = new QLabel("Best fitness");
    this->lastImprovementLabel = new QLabel("Last improvement");

    this->epochEdit = new QLineEdit();
    this->epochEdit->setReadOnly(true);
    this->epochEdit->setToolTip("Podpowiedz dla pola.");
    this->epochEdit->setMaximumWidth(LINE_EDIT_WIDTH_MAX);


    this->popFitnessEdit = new QLineEdit();
    this->popFitnessEdit->setReadOnly(true);
    this->popFitnessEdit->setMaximumWidth(LINE_EDIT_WIDTH_MAX);

    this->meanCrossCountEdit = new QLineEdit();
    this->meanCrossCountEdit->setReadOnly(true);
    this->meanCrossCountEdit->setMaximumWidth(LINE_EDIT_WIDTH_MAX);

    this->meanMutCountEdit = new QLineEdit();
    this->meanMutCountEdit->setReadOnly(true);
    this->meanMutCountEdit->setMaximumWidth(LINE_EDIT_WIDTH_MAX);

    this->lastImprovementEdit = new QLineEdit();
    this->lastImprovementEdit->setReadOnly(true);
    this->lastImprovementEdit->setMaximumWidth(LINE_EDIT_WIDTH_MAX);

    this->bestFitnessEdit = new QLineEdit();
    this->bestFitnessEdit->setReadOnly(true);
    this->bestFitnessEdit->setMaximumWidth(LINE_EDIT_WIDTH_MAX);

    this->meanInvalidSolutionsEdit = new QLineEdit();
    this->meanInvalidSolutionsEdit->setReadOnly(true);
    this->meanInvalidSolutionsEdit->setMaximumWidth(LINE_EDIT_WIDTH_MAX);

    this->algStatisticsLayout->addRow(epochLabel, epochEdit);
    this->algStatisticsLayout->addRow(meanCrossCountLabel, meanCrossCountEdit);
    this->algStatisticsLayout->addRow(meanMutCountLabel, meanMutCountEdit);
    this->algStatisticsLayout->addRow(meanInvalidSolutionsLabel, meanInvalidSolutionsEdit);

    this->popStatisticsLayout->addRow(popFitnessLabel, popFitnessEdit);
    this->popStatisticsLayout->addRow(bestFitnessLabel, bestFitnessEdit);
    this->popStatisticsLayout->addRow(lastImprovementLabel, lastImprovementEdit);

    this->statPlot = new StatisticsPlotWidget(this);

    this->algStatisticsGroup->setLayout(algStatisticsLayout);
    this->popStatisticsGroup->setLayout(popStatisticsLayout);

    this->widgetLayout->addWidget(algStatisticsGroup);
    this->widgetLayout->addWidget(popStatisticsGroup);
    this->widgetLayout->addWidget(statPlot);
    this->setLayout(widgetLayout);
    this->setFixedHeight(sizeHint().height());
    this->setFixedWidth(sizeHint().width());
}

StatisticsWidget::~StatisticsWidget()
{

}

void StatisticsWidget::clearStatistics() {
    statPlot->clearPlot();
}

void StatisticsWidget::updateStatistics(const AlgorithmStatistics & statistics)
{
    epochEdit->setText(QString::number(statistics.epoch.back()));
    meanCrossCountEdit->setText(QString::number((double)statistics.crossoverCount / statistics.epoch.back()));
    meanMutCountEdit->setText(QString::number((double)statistics.mutationCount / statistics.epoch.back()));
    meanInvalidSolutionsEdit->setText(QString::number((double)statistics.invalidSolutions / statistics.epoch.back()));
    popFitnessEdit->setText(QString::number(statistics.populationFitness.back()));
    bestFitnessEdit->setText(QString::number(statistics.bestFitness.back()));
    lastImprovementEdit->setText(QString::number(statistics.lastImprovement));
    statPlot->epoch = QVector<double>::fromStdVector(statistics.epoch);
    statPlot->bestFitness = QVector<double>::fromStdVector(statistics.bestFitness);
    statPlot->popFitness = QVector<double>::fromStdVector(statistics.populationFitness);
    statPlot->updatePlot();

    QApplication::processEvents();
}
