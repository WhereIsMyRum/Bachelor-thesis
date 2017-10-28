#include "signalanalyser.h"

SignalAnalyser::SignalAnalyser(QObject *parent) : QObject(parent)
{

}

double SignalAnalyser::countMeanAbsAmplitude()
{
    double sumOfAllVectorValues;
    foreach(double singleSignalValue, signalValues)
    {
        sumOfAllVectorValues += std::abs(singleSignalValue);
    }

    return sumOfAllVectorValues/signalValues.length();
}

double SignalAnalyser::countAbsVariance()
{
    double signalAverage = countMeanAbsAmplitude();
    double signalVariance;

    foreach(double singleSignalValue, signalValues)
    {
        signalVariance += std::pow((std::abs(singleSignalValue) - signalAverage),2.0);
    }

    return signalVariance/signalValues.length();
}

double SignalAnalyser::countMeanEnergy()
{
    double sumOfSquaredSamples;

    foreach(double singleSignalValue, signalValues)
    {
        signalMeanEnergy += std::pow(singleSignalValue,2.0);
    }

    return signalMeanEnergy/signalValues.length();
}

double SignalAnalyser::countEffectiveValue()
{
    return std::sqrt(countMeanEnergy());
}
