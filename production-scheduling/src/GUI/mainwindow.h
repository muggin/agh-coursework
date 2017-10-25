#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QWidget>
#include <QTabWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include "settingswidget.h"
#include "statisticswidget.h"
#include "ui_mainwindow.h"

/*namespace Ui {
class MainWindow;
}*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public:
    Ui::MainWindow *ui;
public slots:
    void onRunAlgorithm();
};

#endif // MAINWINDOW_H
