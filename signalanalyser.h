#ifndef SIGNALANALYSER_H
#define SIGNALANALYSER_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <math.h>

class SignalAnalyser : public QObject
{
    Q_OBJECT
public:
    explicit SignalAnalyser(QObject *parent = nullptr);

    //functions

    //variables
    QVector<double> time, signalValues;

private:
    double countMeanAbsAmplitude();
    double countAbsVariance();
    double countMeanEnergy();
    double countEffectiveValue();
    double countMaximumValue();
    double countFrequencyMedian();
    double countMeanFrequency();
    double countSpectralPowerDensity();

};

#endif // SIGNALANALYSER_H
