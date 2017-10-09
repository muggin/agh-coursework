#ifndef DATAWIDGET_H
#define DATAWIDGET_H

#include <QWidget>
#include <QObject>
#include "AddingWidget.h"
#include "EditingWidget.h"
#include "DeletingWidget.h"
#include "DataStructure.h"
#include <QGroupBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QButtonGroup>
#include <QFileDialog>
#include "../../DataModification/Database.h"

class AddingWidget;
class DeletingWidget;
class EditingWidget;

class DataWidget : public QWidget
{
    Q_OBJECT
private:
    const Database* mydt;
    AddingWidget *addWidget;
    EditingWidget *editWidget;
    DeletingWidget *delWidget;

public:
    explicit DataWidget(QWidget *parent = 0);
    void setDatabase(Database *);
    const Database* getDatabase();

signals:
    void newDataStructure(DataStructure* );
private slots:
    void loadDataFromFile();
    void saveDataToFile();
    void generateRandomData();
    void resetDatabase();
    void clearDatabase();
    void updateWidgets();
    void onAddJob();
    void onAddMachine();
    void onAddTask(int,int,int);
    void onDeleteJob(int);
    void onDeleteMachine(int);
    void onDeleteTask(int,int);
    void onEditChange(int,int,int,int,int,int);

};

#endif // DATAWIDGET_H
