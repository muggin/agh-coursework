#ifndef BLOCKPLOT_H
#define BLOCKPLOT_H

#include "qcustomplot.h"
#include "../Algorithm/Chromosom.h"
#include "extqcpstatisticalbox.h"
#include <QWidget>
#include <QVector>
#include <QMessageBox>

#define XINT 20

class BlockPlot : public QCustomPlot
{
    Q_OBJECT
private:
    QVector<QColor> cVect; //!< Wektor przechowujący kolory bloczkow podczas rysowania wykresu
public:
    /**
     * Standardowy konstruktor każdej klasy dziedziczącej po QWidget
     * \param parent Rodzic QWidgetu.
     */
    explicit BlockPlot(QWidget *parent = 0);
    virtual ~BlockPlot();

signals:


public slots:
    /**
     * Slot bedący odpowiedzialny za ponowne rysowanie wykresu w przypadku zmiany danych.
     */
    void onDataChanged(Database* );
    /**
     * Slot odpowiedzialny za wyświetlanie informacji o konkretnym bloczku w postaci Tooltip-u.
     */
    void onBlockSelected(bool);


};

#endif // BLOCKPLOT_H
