#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "../Algorithm/Algorithm.h"
#include "../Algorithm/SettingsStructures.h"
#include "../GUI/mainwindow.h"
#include "../GUI/blockplot.h"
#include "../DataModification/Database.h"


class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(Algorithm * algorithm, MainWindow * window, Database * database, QObject *parent = 0);

signals:

public slots:

private:
    Algorithm * algorithm;
    Database * database;
    DataWidget* dataWidget;
    SettingsWidget * settingsWidget;
    StatisticsWidget * statisticsWidget;
    BlockPlot * blockPlotWidget;


};

#endif // CONTROLLER_H
