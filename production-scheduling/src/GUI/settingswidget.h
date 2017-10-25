#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

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
#include <QVariant>
#include "qspinboxenhenced.h"
#include "../Algorithm/SettingsStructures.h"
#include "../GeneticOperators/CrossoverOperators/CrossoverOnePoint.h"
#include "../GeneticOperators/CrossoverOperators/CrossoverTwoPoint.h"
#include "../GeneticOperators/MutationOperators/MutationSwappingPoint.h"
#include "../GeneticOperators/MutationOperators/MutationSwappingSegment.h"
#include "../GeneticOperators/MutationOperators/MutationReverse.h"
#include "../GeneticOperators/MutationOperators/MutationInversion.h"
#include "../GeneticOperators/MutationOperators/MutationDisplacement.h"
#include "../GeneticOperators/SelectionOperators/SelectionRank.h"
#include "../GeneticOperators/SelectionOperators/SelectionTournament.h"

#define DOUBLE_SPIN_MIN 0.0
#define DOUBLE_SPIN_MAX 1.0
#define DOUBLE_SPIN_STEP 0.05
#define SPIN_MIN 50
#define SPIN_MAX 100000
#define SPIN_STEP 25
#define START_POPULATION_SIZE 100
#define START_EPOCH_NUMBER 1000
#define START_CROSS_PROBABILITY 0.85
#define START_MUT_PROBABILITY 0.15

class SettingsWidget : public QWidget
{
    Q_OBJECT

signals:
    void runAlgorithm();
    void runAlgorithm(const AlgorithmSettings & settings);

private slots:
    void runButtonClicked();


private:
    QHBoxLayout *widgetLayout;  //!< Glowny layout widgetu SettingsWidget
    QFormLayout *algorithmGroupLayout;  //!< Layout groupboxa algorithmGroup
    QFormLayout *operatorGroupLayout;   //!< Layout groupboxa operatorGroup
    QFormLayout *populationGroupLayout; //!< Layout groupboxa populationGroup
    QGroupBox *algorithmGroup;  //!< Groupbox przechowuje pola zwiazane z ogolnymi ustawieniami algorytmu
    QGroupBox *operatorGroup;   //!< Groupbox przechowuje pola zwiazane z ustawieniami operatorow
    QGroupBox *populationGroup; //!< Groupbox przechowuje pola zwiazane z ustawieniami populacji
    QLabel *epochCountLabel;    //!<
    QLabel *noImprovementLabel;
    QLabel *repairChromosomLabel;
    QLabel *crossOperatorLabel;
    QLabel *crossProbabilityLabel;
    QLabel *mutOperatorLabel;
    QLabel *mutProbabilityLabel;
    QLabel *selOperatorLabel;
    QLabel *popSizeLabel;
    QLabel *newPopSizeLabel;
    QSpinBoxEnhenced *epochCountEdit;
    QSpinBoxEnhenced *noImprovementEdit;
    QDoubleSpinBox *crossProbabilityEdit;
    QDoubleSpinBox *mutProbabilityEdit;
    QSpinBoxEnhenced *popSizeEdit;
    QSpinBoxEnhenced *newPopSizeEdit;
    QComboBox *crossOperatorBox;
    QComboBox *mutOperatorBox;
    QComboBox *selOperatorBox;
    QCheckBox *repairChromosomCheck;
    QPushButton *runButton;

public:
    explicit SettingsWidget(QWidget *parent = 0);
    ~SettingsWidget();

};

#endif // SETTINGSDIALOG_H
