#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
      ui->setupUi(this);
      ui->tabWidget->setCurrentIndex(0);
}


MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::onRunAlgorithm()
{
    ui->tabWidget->setCurrentIndex(2);
}
