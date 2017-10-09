#include "EditingWidget.h"


EditingWidget::EditingWidget(QWidget *parent) :
    QWidget(parent)
{
    jobCombo = new QComboBox();
    machineCombo = new QComboBox();
    taskCombo = new QComboBox();
    positionCombo = new QComboBox();
    durationSpin = new QSpinBox();

    durationSpin->setMaximum(300);
    durationSpin->setMinimum(0);

    this->setGeometry(0, 0, 500, 200);

    fillJobCombo();
    QObject::connect(jobCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(fillTaskCombo()));
    QObject::connect(taskCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(fillMachineCombo()));
    QObject::connect(taskCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(fillPositionCombo()));

    QHBoxLayout *mainLayout = new QHBoxLayout();

    QVBoxLayout *leftSide = new QVBoxLayout();
    QVBoxLayout *rightSide = new QVBoxLayout();

    QVBoxLayout *jobLay = new QVBoxLayout();
    QVBoxLayout *taskLay = new QVBoxLayout();

    QGroupBox *jobGrp = new QGroupBox("Job");
    QGroupBox *taskDataGrp = new QGroupBox("Task data");
    QGroupBox *taskGrp = new QGroupBox("Task");

    QPushButton *saveBtn = new QPushButton("Save");

    QObject::connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveChanges()));

    QFormLayout *taskDataLay = new QFormLayout;
    taskDataLay->addRow(tr("&Machine:"), machineCombo);
    taskDataLay->addRow(tr("&Duration:"), durationSpin);
    taskDataLay->addRow(tr("&Position:"), positionCombo);
    taskDataLay->addWidget(saveBtn);

    taskDataGrp->setLayout(taskDataLay);

    jobLay->addWidget(jobCombo);

    taskLay->addWidget(taskCombo);

    jobGrp->setLayout(jobLay);
    taskGrp->setLayout(taskLay);

    leftSide->addWidget(jobGrp);
    leftSide->addWidget(taskGrp);

    rightSide->addWidget(taskDataGrp);

    mainLayout->addLayout(leftSide);
    mainLayout->addLayout(rightSide);

    this->setLayout(mainLayout);

}

void EditingWidget::fillJobCombo(){
    jobCombo->clear();
    jobCombo->addItem("Select...");
    taskCombo->clear();
    taskCombo->addItem("Select...");
    machineCombo->clear();
    machineCombo->addItem("Select...");
    positionCombo->clear();
    positionCombo->addItem("Select...");
    durationSpin->setValue(0);

    if(((DataWidget*)(this->parentWidget()))->getDatabase()==NULL)
        return;

    const vector <Job> &jobs = ((DataWidget*)(this->parentWidget()))->getDatabase()->getConstJobs();
    for(unsigned int i=0; i<jobs.size(); i++)
        jobCombo->addItem(QString::number(i));
}

void EditingWidget::fillTaskCombo(){
    taskCombo->clear();
    taskCombo->addItem("Select...");
    machineCombo->clear();
    machineCombo->addItem("Select...");
    positionCombo->clear();
    positionCombo->addItem("Select...");
    durationSpin->setValue(0);

    if(((DataWidget*)(this->parentWidget()))->getDatabase()==NULL)
        return;

    if(jobCombo->currentIndex()>0){
        const vector <Task> &tasks = ((DataWidget*)(this->parentWidget()))->getDatabase()->getConstJobs()[jobCombo->currentText().toInt()].getConstTaskList();
        for(unsigned int i=0; i<tasks.size(); i++)
            taskCombo->addItem(QString::number(i));
    }
}

void EditingWidget::fillMachineCombo(){
    machineCombo->clear();
    machineCombo->addItem("Select...");
    positionCombo->clear();
    positionCombo->addItem("Select...");
    durationSpin->setValue(0);

    if(((DataWidget*)(this->parentWidget()))->getDatabase()==NULL)
        return;

    if(jobCombo->currentIndex()>0 && taskCombo->currentIndex()>0){
        const Job &currJob = ((DataWidget*)(this->parentWidget()))->getDatabase()->getConstJobs()[jobCombo->currentText().toInt()];
        const vector <Machine*> &allMachines = ((DataWidget*)(this->parentWidget()))->getDatabase()->getConstMachines();

        machineCombo->addItem(QString::number(currJob.getConstTaskList()[taskCombo->currentText().toInt()].getMachine()->getId()));
        durationSpin->setValue(currJob.getConstTaskList()[taskCombo->currentText().toInt()].getTime());

        for(unsigned int i=0; i<allMachines.size(); i++){
            if( !currJob.isMachineUsed(allMachines[i]->getId()))
                machineCombo->addItem(QString::number(allMachines[i]->getId()));
        }
        machineCombo->setCurrentIndex(1);
    }
}

void EditingWidget::fillPositionCombo(){
    positionCombo->clear();
    positionCombo->addItem("Select...");

    if(((DataWidget*)(this->parentWidget()))->getDatabase()==NULL)
        return;

    int selected = 0;
    if(jobCombo->currentIndex()>0){
        const vector <Task> &tasks = ((DataWidget*)(this->parentWidget()))->getDatabase()->getConstJobs()[jobCombo->currentText().toInt()].getConstTaskList();
        for(unsigned int i=0; i<tasks.size(); i++){
            positionCombo->addItem(QString::number(i));
            if(i==taskCombo->currentText().toInt())
                selected = i+1;
        }
        positionCombo->setCurrentIndex(selected);
    }
}

void EditingWidget::saveChanges(){

    if(machineCombo->currentIndex()>1)
        emit editChangeSig(jobCombo->currentText().toInt(),taskCombo->currentText().toInt(),taskCombo->currentText().toInt(),positionCombo->currentText().toInt(),machineCombo->currentText().toInt(),durationSpin->value());
    else
        emit editChangeSig(jobCombo->currentText().toInt(),taskCombo->currentText().toInt(),taskCombo->currentText().toInt(),positionCombo->currentText().toInt(),-1,durationSpin->value());
    fillTaskCombo();
}
