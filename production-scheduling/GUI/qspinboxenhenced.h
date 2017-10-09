#ifndef QSPINBOXENHENCED_H
#define QSPINBOXENHENCED_H

#include <QSpinBox>

class QSpinBoxEnhenced : public QSpinBox
{
    Q_OBJECT
public:
    explicit QSpinBoxEnhenced(QWidget *parent = 0);

signals:

public slots:
    void setNewMinimum(int value);
    void setNewMaximum(int value);

};

#endif // QSPINBOXENHENCED_H
