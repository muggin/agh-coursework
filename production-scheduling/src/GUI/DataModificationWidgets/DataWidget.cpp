#include "DataWidget.h"

DataWidget::DataWidget(QWidget *parent) :
    QWidget(parent)
{
    this->mydt=NULL;
    this->resize(600, 200);

    this->addWidget = new AddingWidget(this);
    this->editWidget = new EditingWidget(this);
    this->delWidget = new DeletingWidget(this);



    // nowe connecty
    QObject::connect(addWidget, SIGNAL(addJobSig()), this, SLOT(onAddJob()));
    QObject::connect(addWidget, SIGNAL(addMachineSig()), this, SLOT(onAddMachine()));
    QObject::connect(addWidget, SIGNAL(addTaskSig(int,int,int)), this, SLOT(onAddTask(int,int,int)));


    QObject::connect(delWidget, SIGNAL(deleteJobSig(int)), this, SLOT(onDeleteJob(int)));
    QObject::connect(delWidget, SIGNAL(deleteMachineSig(int)), this, SLOT(onDeleteMachine(int)));
    QObject::connect(delWidget, SIGNAL(deleteTaskSig(int,int)), this, SLOT(onDeleteTask(int,int)));

    QObject::connect(editWidget, SIGNAL(editChangeSig(int,int,int,int,int,int)), this, SLOT(onEditChange(int,int,int,int,int,int)));



    QStackedLayout *pageLayout = new QStackedLayout();
    pageLayout->addWidget(addWidget);
    pageLayout->addWidget(delWidget);
    pageLayout->addWidget(editWidget);

    QGroupBox *dataGrp = new QGroupBox("Mode", this);
    QGroupBox *fileGrp = new QGroupBox("File", this);
    QGroupBox *dbGrp = new QGroupBox("Database", this);

    QHBoxLayout *mainLayout = new QHBoxLayout();

    QVBoxLayout *dataLayout = new QVBoxLayout();
    QVBoxLayout *fileLayout = new QVBoxLayout();
    QVBoxLayout *dbLayout = new QVBoxLayout();

    QPushButton *addBtn = new QPushButton("Add");
    QPushButton *delBtn = new QPushButton("Delete");
    QPushButton *editBtn = new QPushButton("Edit");

    QButtonGroup *btnGroup = new QButtonGroup(this);
    btnGroup->addButton(addBtn, 0);
    btnGroup->addButton(delBtn, 1);
    btnGroup->addButton(editBtn, 2);
    
    QObject::connect(btnGroup, SIGNAL(buttonClicked(int)), pageLayout, SLOT(setCurrentIndex(int)));

    dataLayout->addWidget(addBtn);
    dataLayout->addWidget(delBtn);
    dataLayout->addWidget(editBtn);

    QPushButton *loadBtn = new QPushButton("Load");
    QPushButton *saveBtn = new QPushButton("Save");

    QObject::connect(loadBtn, SIGNAL(clicked()), this, SLOT(loadDataFromFile()));
    QObject::connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveDataToFile()));

    fileLayout->addWidget(loadBtn);
    fileLayout->addWidget(saveBtn);

    QPushButton *generateDataBtn = new QPushButton("Generate");
    QPushButton *resetBtn = new QPushButton("Reset");
    QPushButton *clearBtn = new QPushButton("Clear");

    QObject::connect(generateDataBtn, SIGNAL(clicked()), this, SLOT(generateRandomData()));
    QObject::connect(resetBtn, SIGNAL(clicked()), this, SLOT(resetDatabase()));
    QObject::connect(clearBtn, SIGNAL(clicked()), this, SLOT(clearDatabase()));

    dbLayout->addWidget(generateDataBtn);
    dbLayout->addWidget(resetBtn);
    dbLayout->addWidget(clearBtn);

    dataGrp->setLayout(dataLayout);
    fileGrp->setLayout(fileLayout);
    dbGrp->setLayout(dbLayout);

    mainLayout->addWidget(dataGrp);
    mainLayout->addWidget(fileGrp);
    mainLayout->addWidget(dbGrp);
    mainLayout->addLayout(pageLayout);

    this->setLayout(mainLayout);


    this->show();
}

void DataWidget::loadDataFromFile(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"C://", tr("Text File (*.txt)"));
    if(fileName!=""){
        DataStructure* dt=new DataStructure;
        dt->opType=dt->DB_FILE_LOAD;
        dt->dtfile=fileName.toStdString();
        emit newDataStructure(dt);
        updateWidgets();
    }
}

void DataWidget::saveDataToFile(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"C://", tr("Text File (*.txt)"));
    if(fileName!=""){
        DataStructure* dt=new DataStructure;
        dt->opType=dt->DB_FILE_SAVE;
        dt->dtfile=fileName.toStdString();
        emit newDataStructure(dt);
    }
}

void DataWidget::generateRandomData(){

    DataStructure* dt=new DataStructure;
    dt->opType=dt->DB_GEN_RND;
    emit newDataStructure(dt);
    updateWidgets();
}

void DataWidget::resetDatabase(){
    DataStructure* dt=new DataStructure;
    dt->opType=dt->DB_RESET;
    emit newDataStructure(dt);
    updateWidgets();

}

void DataWidget::clearDatabase(){
    DataStructure* dt=new DataStructure;
    dt->opType=dt->DB_CLEAR;
    emit newDataStructure(dt);
    updateWidgets();
}

void DataWidget::updateWidgets(){
    addWidget->fillJobsCombo();
    delWidget->fillJobsCombos();
    delWidget->fillMachineCombo();
    editWidget->fillJobCombo();
}


void DataWidget::onAddJob()
{
    DataStructure* dt=new DataStructure;
    dt->opType=dt->DB_JOB_ADD;
    emit newDataStructure(dt);
    updateWidgets();
}

void DataWidget::onAddMachine()
{
    DataStructure* dt=new DataStructure;
    dt->opType=dt->DB_MACHINE_ADD;
    emit newDataStructure(dt);
    updateWidgets();
}

void DataWidget::onAddTask(int jobID,int machineID,int duration)
{
    DataStructure* dt=new DataStructure;
    dt->opType=dt->DB_TASK_ADD;
    dt->jobID=jobID;
    dt->machineID=machineID;
    dt->tasktime=duration;
    emit newDataStructure(dt);

}

void DataWidget::onDeleteJob(int jobID)
{
    DataStructure* dt=new DataStructure;
    dt->opType=dt->DB_DELETE_JOB;
    dt->jobID=jobID;
    emit newDataStructure(dt);
}

void DataWidget::onDeleteMachine(int machineID)
{
    DataStructure* dt=new DataStructure;
    dt->opType=dt->DB_DELETE_MACHINE;
    dt->machineID=machineID;
    emit newDataStructure(dt);
}

void DataWidget::onDeleteTask(int jobID,int machineID)
{
    DataStructure* dt=new DataStructure;
    dt->opType=dt->DB_DELETE_TASK;
    dt->jobID=jobID;
    dt->machineID=machineID;
    emit newDataStructure(dt);
}

void DataWidget::onEditChange(int jobID,int taskID,int curPos,int newPos,int machineID,int duration)
{

    DataStructure* dt=new DataStructure;
    dt->opType=dt->DB_EDIT;
    dt->jobID=jobID;
    dt->taskID=taskID;
    dt->oldpos=curPos;
    dt->newpos=newPos;
    dt->machineID=machineID;
    dt->tasktime=duration;
    emit newDataStructure(dt);
}

void DataWidget::setDatabase(Database * dt)
{
    this->mydt=dt;
}

const Database* DataWidget::getDatabase()
{
    return mydt;
}
