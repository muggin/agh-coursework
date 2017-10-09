#ifndef DELETINGWIDGET_H
#define DELETINGWIDGET_H

#include <QWidget>
#include "DataWidget.h"
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QGroupBox>
#include <QFormLayout>

class DataWidget;

class DeletingWidget : public QWidget
{
    Q_OBJECT

private:
    QComboBox *jobCombo;
    QComboBox *machineCombo;
    QComboBox *taskJobCombo;
    QComboBox *taskMachineCombo;

public:
    explicit DeletingWidget(QWidget *parent = 0);

signals:
    void deleteJobSig(int);
    void deleteMachineSig(int);
    void deleteTaskSig(int,int);


public slots:
    void fillJobsCombos();
    void fillMachineCombo();
    void fillTaskMachineCombo();
    void deleteJob();
    void deleteMachine();
    void deleteTask();

};

#endif // DELETINGWIDGET_H
