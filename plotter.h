#ifndef PLOTTER_H
#define PLOTTER_H

#include <QVector>

class Plotter
{
public:

    Plotter();
    void makePlot();
    void updatePlot();

    QVector<double> x,y;
};

#endif // PLOTTER_H
