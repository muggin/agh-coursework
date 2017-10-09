#ifndef STATISTICSPLOTWIDGET_H
#define STATISTICSPLOTWIDGET_H

#include <QWidget>
#include <QVector>
#include "qcustomplot.h"

class StatisticsPlotWidget : public QCustomPlot
{
    Q_OBJECT
public:
    explicit StatisticsPlotWidget(QWidget *parent = 0);
    QVector<double> epoch, popFitness, bestFitness;
    void clearPlot();
    void updatePlot();

signals:

public slots:

};

#endif // STATISTICSPLOTWIDGET_H
