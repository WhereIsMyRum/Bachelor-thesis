#ifndef SERIALPORTREADER_H
#define SERIALPORTREADER_H

#include <QByteArray>
#include <QRegExp>
#include <QStringList>
#include <QVector>
#include <QDebug>
#include <QObject>
#include "plotter.h"
#include "signalanalyser.h"

<<<<<<< HEAD
=======
#define WINDOW_LENGTH 700.0
>>>>>>> 41ef6e05a6db6a2eed92cbc4e0c310936ed49426

class SerialPortReader : public QObject
{

    Q_OBJECT

public:
    SerialPortReader();
    void ReadSerial(QByteArray serialData, Plotter *plotter, SignalAnalyser *analyser);

    void setFirstMeasurement(bool value);
    void setFaultyDataDetected(bool value);

    QString getDataBuffor() const;
    void clearDataBuffor();

    QString getDataTimeBuffor() const;
    void clearDataTimeBuffor();

    QString getRawDataBuffor() const;
    void clearRawDataBuffor();

private:
    QString *serialDataString;
    QString faultyData;
    QString dataBuffor;
    QString rawDataBuffor;
    QString dataTimeBuffor;

    QStringList *dataListToAppend;

    bool firstMeasurement;
    bool faultyDataDetected;
    double firstTimeRead;

    QRegExp *dataRegExp;
    QRegExp *timeRegExp;
    QRegExp *dataRawRegExp;

signals:
    void plotRangeExceeded(double);


};

#endif
