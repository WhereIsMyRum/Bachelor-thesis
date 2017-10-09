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
    void ReadSerial(QString& dataBuffor, QString& dataTimeBuffor, QByteArray serialData, PlotDataMaintainer* plotDataMaintainer);

    void setFirstMeasurement(bool value);
    void setFaultyDataDetected(bool value);

private:
    QString *serialDataString;
    QString faultyData;
    QStringList *dataListToAppend;

    bool firstMeasurement;
    bool faultyDataDetected;
    double firstTimeRead;

    QRegExp *dataRegExp;
    QRegExp *timeRegExp;

signals:
    void plotRangeExceeded(double);


};

#endif
