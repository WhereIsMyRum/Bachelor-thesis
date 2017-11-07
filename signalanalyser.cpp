#include "signalanalyser.h"

SignalAnalyser::SignalAnalyser(QObject *parent) : QObject(parent)
{
    getFrequencyVector();
}

QVector<double> SignalAnalyser::getSignalParams()
{
    QVector<std::complex<double>> signalDFT;

    signalParams.append(SignalAnalyser::countMeanAbsAmplitude());
    signalParams.append(SignalAnalyser::countAbsVariance(signalParams.at(0)));
    signalParams.append(SignalAnalyser::countMeanEnergy());
    signalParams.append(SignalAnalyser::countEffectiveValue(signalParams.at(2)));
    signalParams.append(SignalAnalyser::countMaximumValue());
    signalParams.append(SignalAnalyser::countMedianValueOfNonZeroValue());

    signalDFT = SignalAnalyser::computeFFT(signalValues);

    signalParams.append(SignalAnalyser::countMeanFrequency(signalDFT));
    signalParams.append(SignalAnalyser::countMedianFrequency(signalDFT));

    return signalParams;

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

double SignalAnalyser::countAbsVariance(const double &signalAverage)
{
    double signalVariance;

    foreach(double singleSignalValue, signalValues)
    {
        signalVariance += std::pow((std::abs(singleSignalValue) - signalAverage),2.0);
    }

    return signalVariance/signalValues.length();
}

double SignalAnalyser::countMeanEnergy()
{
    double signalMeanEnergy;

    foreach(double singleSignalValue, signalValues)
    {
        signalMeanEnergy += std::pow(singleSignalValue,2.0);
    }

    return signalMeanEnergy/signalValues.length();
}

double SignalAnalyser::countEffectiveValue(const double &meanEnergy)
{
    return std::sqrt(meanEnergy);
}

double SignalAnalyser::countMaximumValue()
{
    return *std::max_element(signalValues.constBegin(),signalValues.constEnd());

}

double SignalAnalyser::countMedianValueOfNonZeroValue()
{
    QVector<double> medianVector = signalValues;

    medianVector.removeAll(0);

    qSort(medianVector);

    if(medianVector.length()%2 == 0)
    {
        return  (medianVector.at((medianVector.length()/2) - 1) + medianVector.at((medianVector.length()/2)))/2.0;
    }
    else
    {
        return  medianVector.at(std::ceil(medianVector.length()/2));
    }
}


double SignalAnalyser::countMeanFrequency(QVector<std::complex<double> > &inputDFT)
{
    QVector<double> powerVector;
    double powerSum = 0;
    double powerMultByFreqSum = 0;
    double meanFreq;

    foreach(std::complex<double> singleSignalValue, inputDFT)
    {
        powerVector.append(std::pow(std::abs(singleSignalValue),2));
    }

    for(int i = 0; i < powerVector.length(); i++)
    {
        powerSum += powerVector.at(i);
        powerMultByFreqSum += powerVector.at(i)*frequencyVector.at(i);
    }

    meanFreq = powerMultByFreqSum/powerSum;

    return meanFreq;
}

double SignalAnalyser::countMedianFrequency(QVector<std::complex<double> > &inputDFT)
{
    QVector<double> powerVector;
    double powerVectorSum = 0;
    double tempSum = 0;
    int i = 1;

    foreach(std::complex<double> singleSignalValue, inputDFT)
    {
        powerVector.append(std::pow(std::abs(singleSignalValue),2));
        powerVectorSum += powerVector.last();
    }

    powerVectorSum = powerVectorSum/2;

    while(tempSum < powerVectorSum)
    {
        tempSum = 0;
        i++;
        for(int j = 0; j < i; j++)
        {
            tempSum += powerVector.at(j);
        }
    }
    return frequencyVector.at(i);
}

void SignalAnalyser::getFrequencyVector()
{
    double frequencyDiff = SAMPLING_FREQ/WINDOW_LENGTH;
    for(double i = 0; i < SAMPLING_FREQ/2; i += frequencyDiff)
    {
        frequencyVector.append(i);
    }
}

QVector<std::complex<double>> SignalAnalyser::computeDFT(const QVector<double> &inputSignal)
{
    QVector<std::complex<double>> signalDFT;

    const std::size_t n = inputSignal.length();
    for(std::size_t k = 0; k < n; k++)
    {
        std::complex<double> sum(0.0,0.0);
        for(size_t t = 0; t < n; t++)
        {
            std::complex<double> angle(0.0, M_PI/n * -2 * k * t);
            sum += inputSignal[t] * std::exp(angle);
        }
        signalDFT.push_back(sum);
        signalDFT.last() = (signalDFT.last()/(WINDOW_LENGTH/2))*2.0;
    }

    signalDFT = signalDFT.mid(0, WINDOW_LENGTH/2);

    return signalDFT;
}

QVector<std::complex<double>> SignalAnalyser::computeFFT(const QVector<double> &inputSignal)
{

    QVector<std::complex<double>> signalFFT;

    for(int i = 0; i < inputSignal.length(); i++)
    {
        signalFFT.append(inputSignal[i]);
    }

    FFT(signalFFT);

    signalFFT = signalFFT.mid(0,WINDOW_LENGTH/2);
    for(int i = 0; i < signalFFT.length(); i++)
    {
        signalFFT[i] = (signalFFT[i]/(WINDOW_LENGTH/2)) * 2.0;
    }

    return signalFFT;

}

void SignalAnalyser::FFT(QVector<std::complex<double>>& signalFFT)
{
    const size_t N = signalFFT.length();
    if(N < 2) {}

    else
    {

        QVector<std::complex<double>> even = sliceQVector(signalFFT, 0,N/2, 2);
        QVector<std::complex<double>> odd = sliceQVector(signalFFT, 1, N/2,2);

        FFT(even);
        FFT(odd);

        for(size_t k = 0; k < N/2; k++)
        {
            std::complex<double> t =  std::polar(1.0, -2 * M_PI * k/N) * odd[k];
            signalFFT[k] = even[k] + t;
            signalFFT[k+N/2] = even[k] - t;
        }
    }
}

QVector<std::complex<double> > SignalAnalyser::sliceQVector(const QVector<std::complex<double> > &inputSignal, std::size_t start, std::size_t size, std::size_t stride)
{
    QVector<std::complex<double>> slicedVector;
    for(int i = 0; i < size; i++)
    {
        slicedVector.append(inputSignal[start + i*stride]);
    }
    return slicedVector;
}


<<<<<<< HEAD
=======


>>>>>>> d064b4a0416da593fa603ab062ce803c07d43a3c


