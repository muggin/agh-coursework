#ifndef EXTQCPSTATISTICALBOX_H
#define EXTQCPSTATISTICALBOX_H

#include "qcustomplot.h"
#include <QMessageBox>
#include <QString>

class ExtQCPStatisticalBox : public QCPStatisticalBox
{
    Q_OBJECT

public:
    /**
     * Standardowy konstruktor klasy dziedziczącej po QCPStatisticalBox.
     * \param keyAxis Oś zawierająca dziedzinę funkcji.
     * \param valueAxis Oś zawierająca wartości funkcji.
     */
    ExtQCPStatisticalBox (QCPAxis *keyAxis, QCPAxis *valueAxis);

public slots:
    /**
     * Slot odpowiedzialny za wyświetlanie informacji o konkretnym bloczku w postaci QMessageBoxa.
     */
    void blockinfo(bool);

};

#endif // EXTQCPSTATISTICALBOX_H
