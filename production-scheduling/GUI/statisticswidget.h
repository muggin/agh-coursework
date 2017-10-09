#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QLayout>
#include "statisticsplotwidget.h"
#include "../Algorithm/StatisticsStructure.h"

#define LINE_EDIT_WIDTH_MAX 65

class StatisticsWidget : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *widgetLayout;
    QFormLayout *algStatisticsLayout;
    QFormLayout *popStatisticsLayout;
    QGroupBox *algStatisticsGroup;
    QGroupBox *popStatisticsGroup;
    QGroupBox *plotStatisticsGroup;
    QLabel *epochLabel;
    QLabel *popFitnessLabel;
    QLabel *meanCrossCountLabel;
    QLabel *meanMutCountLabel;
    QLabel *lastImprovementLabel;
    QLabel *bestFitnessLabel;
    QLabel *meanInvalidSolutionsLabel;
    QLineEdit *epochEdit;
    QLineEdit *popFitnessEdit;
    QLineEdit *meanCrossCountEdit;
    QLineEdit *meanMutCountEdit;
    QLineEdit *lastImprovementEdit;
    QLineEdit *bestFitnessEdit;
    QLineEdit *meanInvalidSolutionsEdit;
    StatisticsPlotWidget *statPlot;

public:
    explicit StatisticsWidget(QWidget *parent = 0);
    ~StatisticsWidget();
signals:

public slots:
    void clearStatistics();
    void updateStatistics(const AlgorithmStatistics & statistics);
};

#endif // STATISTICSWIDGET_H
