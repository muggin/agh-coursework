#include "settingswidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent)
{
    this->widgetLayout = new QHBoxLayout(this);
    this->algorithmGroupLayout = new QFormLayout();
    this->operatorGroupLayout = new QFormLayout();
    this->populationGroupLayout = new QFormLayout();

    this->algorithmGroup = new QGroupBox("Algorithm Settings");
    this->operatorGroup = new QGroupBox("Operator Settings");
    this->populationGroup = new QGroupBox("Population Settings");

    this->epochCountLabel = new QLabel("Max epochs");
    this->noImprovementLabel = new QLabel("Max no-improvement");
    this->repairChromosomLabel = new QLabel("Repair chromosoms");
    this->crossOperatorLabel = new QLabel("Crossover operator");
    this->crossProbabilityLabel = new QLabel("Crossover probability");
    this->mutOperatorLabel = new QLabel("Mutation opeartor");
    this->mutProbabilityLabel = new QLabel("Mutation probability");
    this->selOperatorLabel = new QLabel("Selection operator");
    this->popSizeLabel = new QLabel("Population size");
    this->newPopSizeLabel = new QLabel("New population size");

    this->epochCountEdit = new QSpinBoxEnhenced();
    epochCountEdit->setRange(SPIN_MIN, SPIN_MAX);
    epochCountEdit->setSingleStep(SPIN_STEP);
    epochCountEdit->setValue(START_EPOCH_NUMBER);

    this->noImprovementEdit = new QSpinBoxEnhenced();
    noImprovementEdit->setRange(SPIN_MIN, SPIN_MAX);
    noImprovementEdit->setSingleStep(SPIN_STEP);
    noImprovementEdit->setValue(START_EPOCH_NUMBER);
    connect(epochCountEdit, SIGNAL(valueChanged(int)), noImprovementEdit, SLOT(setNewMaximum(int)));

    this->crossProbabilityEdit = new QDoubleSpinBox();
    crossProbabilityEdit->setRange(DOUBLE_SPIN_MIN, DOUBLE_SPIN_MAX);
    crossProbabilityEdit->setSingleStep(DOUBLE_SPIN_STEP);
    crossProbabilityEdit->setValue(START_CROSS_PROBABILITY);

    this->mutProbabilityEdit = new QDoubleSpinBox();
    mutProbabilityEdit->setRange(DOUBLE_SPIN_MIN, DOUBLE_SPIN_MAX);
    mutProbabilityEdit->setSingleStep(DOUBLE_SPIN_STEP);
    mutProbabilityEdit->setValue(START_MUT_PROBABILITY);

    this->popSizeEdit = new QSpinBoxEnhenced();
    popSizeEdit->setRange(SPIN_MIN, SPIN_MAX);
    popSizeEdit->setSingleStep(SPIN_STEP);
    popSizeEdit->setValue(START_POPULATION_SIZE);

    this->newPopSizeEdit = new QSpinBoxEnhenced();
    newPopSizeEdit->setRange(SPIN_MIN, SPIN_MAX);
    newPopSizeEdit->setSingleStep(SPIN_STEP);
    newPopSizeEdit->setValue(START_POPULATION_SIZE);
    connect(popSizeEdit, SIGNAL(valueChanged(int)), newPopSizeEdit, SLOT(setNewMinimum(int)));

    this->crossOperatorBox = new QComboBox();
    QVariant crossOption1 = qVariantFromValue((void *) new CrossoverOnePoint());
    crossOperatorBox->addItem("One Point", crossOption1);
    QVariant crossOption2 = qVariantFromValue((void *) new CrossoverTwoPoint());
    crossOperatorBox->addItem("Two Point", crossOption2);

    this->mutOperatorBox = new QComboBox();
    QVariant mutOption1 = qVariantFromValue((void *) new MutationSwappingPoint());
    mutOperatorBox->addItem("Point Swap", mutOption1);
    QVariant mutOption2 = qVariantFromValue((void *) new MutationSwappingSegment());
    mutOperatorBox->addItem("Segment Swap", mutOption2);
    QVariant mutOption3 = qVariantFromValue((void *) new MutationReverse());
    mutOperatorBox->addItem("Reverse", mutOption3);
    QVariant mutOption4 = qVariantFromValue((void *) new MutationInversion());
    mutOperatorBox->addItem("Inversion", mutOption4);
    QVariant mutOption5 = qVariantFromValue((void *) new MutationDisplacement());
    mutOperatorBox->addItem("Displacement", mutOption5);

    this->selOperatorBox = new QComboBox();
    QVariant selOption1 = qVariantFromValue((void *) new SelectionTournament());
    selOperatorBox->addItem("Tournament", selOption1);
    QVariant selOption2 = qVariantFromValue((void *) new SelectionRank());
    selOperatorBox->addItem("Rank", selOption2);

    this->repairChromosomCheck = new QCheckBox();

    this->runButton = new QPushButton("Run algorithm");
    connect(this->runButton, SIGNAL(clicked()), this, SLOT(runButtonClicked()));

    algorithmGroupLayout->addRow(epochCountLabel, epochCountEdit);
    algorithmGroupLayout->addRow(noImprovementLabel, noImprovementEdit);

    operatorGroupLayout->addRow(crossOperatorLabel, crossOperatorBox);
    operatorGroupLayout->addRow(crossProbabilityLabel, crossProbabilityEdit);
    operatorGroupLayout->addRow(mutOperatorLabel, mutOperatorBox);
    operatorGroupLayout->addRow(mutProbabilityLabel, mutProbabilityEdit);
    operatorGroupLayout->addRow(selOperatorLabel, selOperatorBox);

    populationGroupLayout->addRow(popSizeLabel, popSizeEdit);
    populationGroupLayout->addRow(newPopSizeLabel, newPopSizeEdit);
    populationGroupLayout->addRow(repairChromosomLabel, repairChromosomCheck);

    algorithmGroup->setLayout(algorithmGroupLayout);
    operatorGroup->setLayout(operatorGroupLayout);
    populationGroup->setLayout(populationGroupLayout);

    widgetLayout->addWidget(algorithmGroup);
    widgetLayout->addWidget(populationGroup);
    widgetLayout->addWidget(operatorGroup);
    widgetLayout->addWidget(runButton);


    this->setLayout(widgetLayout);
    this->setFixedHeight(sizeHint().height());
    this->setFixedWidth(sizeHint().width());
}

SettingsWidget::~SettingsWidget()
{
    QVariant option;
    CrossoverOperator * crossOperator;
    MutationOperator * mutOperator;
    SelectionOperator * selOperator;
    int selOperatorCount = selOperatorBox->count();
    int mutOperatorCount = mutOperatorBox->count();
    int crossOperatorCount = crossOperatorBox->count();

    for (int i = 0; i < selOperatorCount; i++) {
        option = selOperatorBox->itemData(i);
        selOperator = (SelectionOperator *)option.value<void *>();
        delete selOperator;
    }

    for (int i = 0; i < mutOperatorCount; i++) {
        option = mutOperatorBox->itemData(i);
        mutOperator = (MutationOperator *)option.value<void *>();
        delete mutOperator;
    }

    for (int i = 0; i < crossOperatorCount; i++) {
        option = crossOperatorBox->itemData(i);
        crossOperator = (CrossoverOperator *)option.value<void *>();
        delete crossOperator;
    }
    printf("Destruktor called.");
    fflush(NULL);
}

void SettingsWidget::runButtonClicked()
{
    AlgorithmSettings settings;
    settings.maxEpochs = epochCountEdit->value();
    settings.maxEpochsWithoutChange = noImprovementEdit->value();
    settings.repairChromosom = (repairChromosomCheck->checkState() == 0) ? false : true;
    settings.populationSize = popSizeEdit->value();
    settings.newPopulationSize = newPopSizeEdit->value();
    settings.crossoverProbability = crossProbabilityEdit->value();
    settings.mutationProbability = mutProbabilityEdit->value();

    QVariant crossOperator = crossOperatorBox->currentData();
    settings.crossoverOperator = (CrossoverOperator *) crossOperator.value<void *>();

    QVariant mutOperator = mutOperatorBox->currentData();
    settings.mutationOperator = (MutationOperator *) mutOperator.value<void *>();

    QVariant selOperator = selOperatorBox->currentData();
    settings.selectionOperator = (SelectionOperator *) selOperator.value<void *>();

    emit runAlgorithm();
    emit runAlgorithm(settings);
}
