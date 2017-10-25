#include "qspinboxenhenced.h"

QSpinBoxEnhenced::QSpinBoxEnhenced(QWidget *parent) : QSpinBox(parent)
{

}

void QSpinBoxEnhenced::setNewMinimum(int value)
{
    this->setMinimum(value);
}

void QSpinBoxEnhenced::setNewMaximum(int value)
{
    this->setMaximum(value);
}
