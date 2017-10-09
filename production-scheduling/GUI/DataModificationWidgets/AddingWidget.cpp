#include "AddingWidget.h"

AddingWidget::AddingWidget(QWidget *parent) :
    QWidget(parent)
{
    jobCombo = new QComboBox();
    machineCombo = new QComboBox();
    durationSpin = new QSpinBox();

    this->setGeometry(0, 0, 500, 200);

    fillJobsCombo();

    durationSpin->setMinimum(0);
    durationSpin->setMaximum(300);

    QObject::connect(jobCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(fillMachinesCombo()));

    QHBoxLayout *mainLayout = new QHBoxLayout();

    QVBoxLayout *leftSide = new QVBoxLayout();
    QVBoxLayout *rightSide = new QVBoxLayout();

    QVBoxLayout *jobLay = new QVBoxLayout();
    QVBoxLayout *machineLay = new QVBoxLayout();

    QGroupBox *jobGrp = new QGroupBox("Job");
    QGroupBox *machineGrp = new QGroupBox("Machine");
    QGroupBox *taskGrp = new QGroupBox("Task");

    QPushButton *addJobBtn = new QPushButton("Add");
    QPushButton *addMachineBtn = new QPushButton("Add");
    QPushButton *addTaskBtn = new QPushButton("Add");

    QObject::connect(addJobBtn, SIGNAL(clicked()), this, SLOT(addJob()));
    QObject::connect(addMachineBtn, SIGNAL(clicked()), this, SLOT(addMachine()));
    QObject::connect(addTaskBtn, SIGNAL(clicked()), this, SLOT(addTask()));

    QFormLayout *taskLay = new QFormLayout;
    taskLay->addRow(tr("&Job:"), jobCombo);
    taskLay->addRow(tr("&Machine:"), machineCombo);
    taskLay->addRow(tr("&Duration:"), durationSpin);
    taskLay->addWidget(addTaskBtn);

    taskGrp->setLayout(taskLay);

    jobLay->addWidget(addJobBtn);
    machineLay->addWidget(addMachineBtn);

    jobGrp->setLayout(jobLay);
    machineGrp->setLayout(machineLay);

    leftSide->addWidget(jobGrp);
    leftSide->addWidget(machineGrp);

    rightSide->addWidget(taskGrp);

    mainLayout->addLayout(leftSide);
    mainLayout->addLayout(rightSide);

    this->setLayout(mainLayout);

}

void AddingWidget::fillMachinesCombo(){
    machineCombo->clear();
    machineCombo->addItem("Select...");
    durationSpin->setValue(0);

    if(((DataWidget*)(this->parentWidget()))->getDatabase()==NULL)
        return;

    if(jobCombo->currentIndex()>0){

        const Job &currJob = ((DataWidget*)(this->parentWidget()))->getDatabase()->getConstJobs()[jobCombo->currentText().toInt()];
        const vector <Machine*> &allMachines = ((DataWidget*)(this->parentWidget()))->getDatabase()->getConstMachines();
        for(unsigned int i=0; i<allMachines.size(); i++){
            if( !currJob.isMachineUsed(allMachines[i]->getId()) )
                machineCombo->addItem(QString::number(allMachines[i]->getId()));
        }
    }
}

void AddingWidget::fillJobsCombo(){
    jobCombo->clear();
    machineCombo->clear();
    jobCombo->addItem("Select...");
    machineCombo->addItem("Select...");
    durationSpin->setValue(0);

    if(((DataWidget*)(this->parentWidget()))->getDatabase()==NULL)
        return;

    int jobCount = ((DataWidget*)(this->parentWidget()))->getDatabase()->getJobsAmount();
    for(int i=0; i<jobCount; i++)
        jobCombo->addItem(QString::number(i));
}

void AddingWidget::addJob(){
    emit addJobSig();
    fillJobsCombo();
    fillMachinesCombo();
}

void AddingWidget::addMachine(){
    emit addMachineSig();
    fillJobsCombo();
    fillMachinesCombo();
}

void AddingWidget::addTask(){
    if(jobCombo->currentIndex()>0 && machineCombo->currentIndex()>0){
        emit addTaskSig(jobCombo->currentText().toInt(),machineCombo->currentText().toInt(),durationSpin->value());
        fillMachinesCombo();
    }
}
