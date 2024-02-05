#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("MathCurves");
    mSpinInterval = ui->spinInterval;
    update_ui();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_ui()
{
    this->ui->spinScale->setValue(this->ui->renderArea->getScale());
    this->ui->spinInterval->setValue(this->ui->renderArea->getInterval());
    this->ui->spinCount->setValue(this->ui->renderArea->getStepCount());
    this->ui->renderArea->update();
}

void MainWindow::on_btnAstroid_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Astroid);
    this->ui->renderArea->repaint();
    this->mSpinInterval->setEnabled(true);
    update_ui();
}


void MainWindow::on_btnCloud_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Cloud);
    this->ui->renderArea->repaint();
    this->mSpinInterval->setEnabled(true);
    update_ui();
}


void MainWindow::on_btnHuygens_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HuygensCycloid);
    this->ui->renderArea->repaint();
    this->mSpinInterval->setEnabled(true);
    update_ui();
}


void MainWindow::on_btnHypo_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HypoCycloid);
    this->ui->renderArea->repaint();
    this->mSpinInterval->setEnabled(true);
    update_ui();
}


void MainWindow::on_btnHeart_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Heart);
    this->ui->renderArea->repaint();
    this->mSpinInterval->setEnabled(true);
    update_ui();
}


void MainWindow::on_Fancy_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Fancy);
    this->ui->renderArea->repaint();
    this->mSpinInterval->setEnabled(true);
    update_ui();
}


void MainWindow::on_btnStarfish_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Starfish);
    this->ui->renderArea->repaint();
    this->mSpinInterval->setEnabled(true);
    update_ui();
}


void MainWindow::on_btnFSierpinski_clicked()
{
    this->ui->renderArea->setShape(RenderArea::FSierpinski);
    this->ui->renderArea->repaint();
    this->mSpinInterval->setDisabled(true);
    update_ui();
}


void MainWindow::on_btnFMandelbrot_clicked()
{
    this->ui->renderArea->setShape(RenderArea::FMondelbrot);
    this->ui->renderArea->repaint();
    this->mSpinInterval->setDisabled(true);
    update_ui();
}


void MainWindow::on_btnFJulia_clicked()
{
    this->ui->renderArea->setShape(RenderArea::FJulia);
    this->ui->renderArea->repaint();
    this->mSpinInterval->setDisabled(true);
    update_ui();
}


void MainWindow::on_btnFTree_clicked()
{
    this->ui->renderArea->setShape(RenderArea::FTree);
    this->ui->renderArea->repaint();
    this->mSpinInterval->setDisabled(true);
    update_ui();
}


void MainWindow::on_btnFDragon_clicked()
{
    this->ui->renderArea->setShape(RenderArea::FDragon);
    this->ui->renderArea->repaint();
    this->mSpinInterval->setDisabled(true);
    update_ui();
}


void MainWindow::on_spinScale_valueChanged(double scale)
{
    this->ui->renderArea->setScale(scale);
}


void MainWindow::on_spinInterval_valueChanged(double interval)
{
    this->ui->renderArea->setInterval(interval);
}


void MainWindow::on_spinCount_valueChanged(int count)
{
    this->ui->renderArea->setStepCount(count);
}


void MainWindow::on_btnBackground_clicked()
{
    QColor color = QColorDialog::getColor(this->ui->renderArea->getBackgroundColor(), this, "Select Color");
    this->ui->renderArea->setBackgroundColor(color);
    update_ui();
}


void MainWindow::on_btnLineColor_clicked()
{
    QColor color = QColorDialog::getColor(this->ui->renderArea->getShapeColor(), this, "Select Color");
    this->ui->renderArea->setShapeColor(color);
    update_ui();
}

