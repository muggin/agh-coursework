#include "statisticsplotwidget.h"

StatisticsPlotWidget::StatisticsPlotWidget(QWidget *parent) : QCustomPlot(parent)
{

    this->xAxis->setLabel("Epoch");
    this->xAxis->setRangeLower(0);
    this->xAxis->setAutoTickCount(3);
    this->xAxis->setAutoTickLabels(true);
    this->yAxis->setLabel("Fitness");
    this->yAxis->setRangeLower(0);
    this->yAxis->setAutoTickCount(4);
    this->yAxis->setAutoTickLabels(true);

    // create graph and assign data to it:
    this->addGraph();
    this->graph(0)->setPen(QPen(Qt::red));
    this->graph(0)->setName("Population");

    this->addGraph();
    this->graph(1)->setName("Best");

    this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    this->replot();
    this->setFixedHeight(175);
    this->setFixedWidth(300);

}

void StatisticsPlotWidget::clearPlot() {
    this->epoch.clear();
    this->bestFitness.clear();
    this->popFitness.clear();
    this->graph(0)->setData(epoch, popFitness);
    this->graph(1)->setData(epoch, bestFitness);
    this->replot(QCustomPlot::rpImmediate);

}

void StatisticsPlotWidget::updatePlot() {
    this->graph(0)->addData(epoch, popFitness);
    this->graph(0)->rescaleAxes();
    this->graph(1)->addData(epoch, bestFitness);
    this->replot(QCustomPlot::rpImmediate);
}
