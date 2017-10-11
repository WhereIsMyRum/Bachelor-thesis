#ifndef SERIALPORTREADER_H
#define SERIALPORTREADER_H

#include <QByteArray>
#include <QRegExp>
#include <QStringList>
#include <QVector>
#include <QDebug>
#include <QObject>
#include "plotdatamaintainer.h"

class SerialPortReader : public QObject
{

    Q_OBJECT

public:
    SerialPortReader();
    void ReadSerial(QByteArray serialData, PlotDataMaintainer* plotDataMaintainer);

    void setFirstMeasurement(bool value);
    void setFaultyDataDetected(bool value);

    QString getDataBuffor() const;
    void clearDataBuffor();

    QString getDataTimeBuffor() const;
    void clearDataTimeBuffor();

    QString getRawDataBuffor() const;
    void clearRawDataBuffor();

    int numberOfCalls; //usun

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
