#ifndef SIGNALANALYSER_H
#define SIGNALANALYSER_H

#define WINDOW_LENGTH 700.0
#define SAMPLING_FREQ 1000

#include <QObject>
#include <QVector>
#include <QDebug>
#include <cmath>
#include <algorithm>
#include <complex>

class SignalAnalyser : public QObject
{
    Q_OBJECT
public:
    explicit SignalAnalyser(QObject *parent = nullptr);

    //functions
    QVector<double> getSignalParams();
    //variables
    QVector<double> signalValues, frequencyVector, signalParams;

private:
    double countMeanAbsAmplitude();
    double countAbsVariance(const double &signalAverage);
    double countMeanEnergy();
    double countEffectiveValue(const double &meanEnergy);
    double countMaximumValue();
    double countMedianValueOfNonZeroValue();
    double countMedianFrequency(QVector<std::complex<double>> &inputDFT);
    double countMeanFrequency(QVector<std::complex<double>> &inputDFT);

    void getFrequencyVector();
    QVector<std::complex<double>> computeDFT(const QVector<double> &inputSignal);


};

#endif // SIGNALANALYSER_H
