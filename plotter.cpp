#include "plotter.h"
#include "ui_plotter.h"

Plotter::Plotter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plotter)
{
    ui->setupUi(this);
    Plotter::makePlot();
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


    ui->customPlot->xAxis->setLabel("t[s]");
    ui->customPlot->yAxis->setLabel("U[mV]");
    ui->customPlot->xAxis->setRange(0,5000);
    ui->customPlot->yAxis->setRange(0,2000);
    ui->customPlot->replot();
}

void Plotter::updatePlot()
{
    ui->customPlot->graph(0)->setData(x,y);
    ui->customPlot->replot();
    ui->customPlot->update();
}


void Plotter::on_stopMeasurementButton_clicked()
{
    emit stopMeasurement();
}

void Plotter::shiftPLot(double valueToBeShifted)
{
    ui->customPlot->xAxis->moveRange(valueToBeShifted);
}
