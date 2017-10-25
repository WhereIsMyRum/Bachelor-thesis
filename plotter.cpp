#include "plotter.h"
#include "ui_plotter.h"

Plotter::Plotter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plotter)
{
    ui->setupUi(this);
    ui->closeWindowButton->setEnabled(false);
    QObject::connect(parent,SIGNAL(shiftSecondPlot(double)),this,SLOT(shiftPLot(double)));
}

Plotter::~Plotter()
{
    delete ui;
}


void Plotter::makePlot()
{
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue));

    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::red));


    ui->customPlot->xAxis->setLabel("t[s]");
    ui->customPlot->yAxis->setLabel("U[mV]");
    ui->customPlot->xAxis->setRange(0,20);
    ui->customPlot->yAxis->setRange(0,6);
    ui->customPlot->replot();
}

void Plotter::updatePlot()
{
    ui->customPlot->graph(0)->setData(x,y_sig);
    ui->customPlot->graph(1)->setData(x,y_raw);

    ui->customPlot->replot(QCustomPlot::rpQueued);
   //ui->customPlot->update();

}


void Plotter::on_stopMeasurementButton_clicked()
{
    ui->closeWindowButton->setEnabled(true);
    emit stopMeasurement();
}

void Plotter::shiftPLot(double valueToBeShifted)
{
    ui->customPlot->xAxis->moveRange(valueToBeShifted);
}

void Plotter::on_closeWindowButton_clicked()
{
    emit closeWindow();
}
