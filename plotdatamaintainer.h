#ifndef PLOTDATAMAINTAINER_H
#define PLOTDATAMAINTAINER_H

#include <QVector>


class PlotDataMaintainer
{
public:
    PlotDataMaintainer();
    QVector<double> x_sig;
    QVector<double> y_sig;
    QVector<double> y_raw;

};

#endif // PLOTDATAMAINTAINER_H
