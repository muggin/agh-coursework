#include "DeletingWidget.h"

DeletingWidget::DeletingWidget(QWidget *parent) :
    QWidget(parent)
{
    jobCombo = new QComboBox(this);
    machineCombo = new QComboBox(this);
    taskJobCombo = new QComboBox(this);
    taskMachineCombo = new QComboBox(this);

    this->setGeometry(0, 0, 500, 200);

    fillJobsCombos();
    fillMachineCombo();
    fillTaskMachineCombo();

    QObject::connect(taskJobCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(fillTaskMachineCombo()));

    QHBoxLayout *mainLayout = new QHBoxLayout();

    QVBoxLayout *leftSide = new QVBoxLayout();
    QVBoxLayout *rightSide = new QVBoxLayout();

    QVBoxLayout *jobLay = new QVBoxLayout();
    QVBoxLayout *machineLay = new QVBoxLayout();

    QGroupBox *jobGrp = new QGroupBox("Job");
    QGroupBox *machineGrp = new QGroupBox("Machine");
    QGroupBox *taskGrp = new QGroupBox("Task");

    QPushButton *delJobBtn = new QPushButton("Delete");
    QPushButton *delMachineBtn = new QPushButton("Delete");
    QPushButton *delTaskBtn = new QPushButton("Delete");

    QObject::connect(delJobBtn, SIGNAL(clicked()), this, SLOT(deleteJob()));
    QObject::connect(delMachineBtn, SIGNAL(clicked()), this, SLOT(deleteMachine()));
    QObject::connect(delTaskBtn, SIGNAL(clicked()), this, SLOT(deleteTask()));

    QFormLayout *taskLay = new QFormLayout;
    taskLay->addRow(tr("&Job:"), taskJobCombo);
    taskLay->addRow(tr("&Machine:"), taskMachineCombo);
    taskLay->addWidget(delTaskBtn);

    taskGrp->setLayout(taskLay);

    jobLay->addWidget(jobCombo);
    jobLay->addWidget(delJobBtn);

    machineLay->addWidget(machineCombo);
    machineLay->addWidget(delMachineBtn);

    jobGrp->setLayout(jobLay);
    machineGrp->setLayout(machineLay);

    leftSide->addWidget(jobGrp);
    leftSide->addWidget(machineGrp);

    rightSide->addWidget(taskGrp);

    mainLayout->addLayout(leftSide);
    mainLayout->addLayout(rightSide);

    this->setLayout(mainLayout);
}

void DeletingWidget::fillJobsCombos(){
    jobCombo->clear();
    taskJobCombo->clear();
    jobCombo->addItem("Select...");
    taskJobCombo->addItem("Select...");

    if(((DataWidget*)(this->parentWidget()))->getDatabase()==NULL)
        return;

    int jobCount = ((DataWidget*)(this->parentWidget()))->getDatabase()->getJobsAmount();
    for(int i=0; i<jobCount; i++){
        jobCombo->addItem(QString::number(i));
        taskJobCombo->addItem(QString::number(i));
    }
}

void DeletingWidget::fillMachineCombo(){
    machineCombo->clear();
    machineCombo->addItem("Select...");

    if(((DataWidget*)(this->parentWidget()))->getDatabase()==NULL)
        return;

    const vector <Machine*> &allMachines = ((DataWidget*)(this->parentWidget()))->getDatabase()->getConstMachines();
    for(unsigned int i=0; i<allMachines.size(); i++)
        machineCombo->addItem(QString::number(allMachines[i]->getId()));
}

void DeletingWidget::fillTaskMachineCombo(){
    taskMachineCombo->clear();
    taskMachineCombo->addItem("Select...");

    if(((DataWidget*)(this->parentWidget()))->getDatabase()==NULL)
        return;

    if(taskJobCombo->currentIndex()>0){
        const Job &currJob = ((DataWidget*)(this->parentWidget()))->getDatabase()->getConstJobs()[taskJobCombo->currentText().toInt()];
        const vector <Task> &allTasks = currJob.getConstTaskList();
        for(unsigned int i=0; i<allTasks.size(); i++){
           taskMachineCombo->addItem( QString::number(allTasks[i].getMachine()->getId()) );
        }
    }
}

void DeletingWidget::deleteJob(){
    if(jobCombo->currentIndex()>0){
        emit deleteJobSig(jobCombo->currentText().toInt());
        fillJobsCombos();
    }

}

void DeletingWidget::deleteMachine(){
    if(machineCombo->currentIndex()>0){
        emit deleteMachineSig(machineCombo->currentText().toInt());
        fillMachineCombo();
        fillTaskMachineCombo();
    }
}

void DeletingWidget::deleteTask(){
    if(taskJobCombo->currentIndex()>0 && taskMachineCombo->currentIndex()>0){
        emit deleteTaskSig(taskJobCombo->currentText().toInt(),taskMachineCombo->currentText().toInt());
        fillTaskMachineCombo();
    }
}
