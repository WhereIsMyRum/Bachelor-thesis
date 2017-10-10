#include "serialportreader.h"

SerialPortReader::SerialPortReader()
{
    dataRegExp = new QRegExp("\\d{1,3}\\.\\d{2}");
    timeRegExp = new QRegExp("\\d{1,20}s");
    firstMeasurement = true;
    faultyDataDetected = false;
}

void SerialPortReader::ReadSerial(QByteArray serialData, PlotDataMaintainer* plotDataMaintainer)
{
    serialDataString = new QString(QString::fromStdString(serialData.toStdString()));
    QStringList dataListToAppend = serialDataString->split("\r\n");
    while(dataListToAppend.contains("")) dataListToAppend.removeAt(dataListToAppend.indexOf(""));

    if(faultyDataDetected)
    {
        faultyData.append(dataListToAppend.first());
        dataListToAppend.removeFirst();

        if(faultyData.contains("\r\n"))
        {
            QStringList *tempList = new QStringList(faultyData.split("\r\n"));
            dataListToAppend.insert(0, tempList->at(1));
            dataListToAppend.insert(0, tempList->at(0));
        }
        else dataListToAppend.insert(0, faultyData);

        faultyDataDetected = false;
    }
    if(!dataListToAppend.isEmpty() && !dataRegExp->exactMatch(dataListToAppend.last()) && !timeRegExp->exactMatch(dataListToAppend.last()))
    {
        faultyDataDetected = true;
        faultyData = dataListToAppend.last();
        dataListToAppend.removeLast();
    }

    while(dataListToAppend.length() > 0 && !dataListToAppend.isEmpty())
    {
        if(firstMeasurement && !dataListToAppend.first().contains("s")) dataListToAppend.removeFirst();
        if(firstMeasurement && dataListToAppend.first().contains("s"))
        {
            QString temp = dataListToAppend.first();
            firstTimeRead = (temp.remove("s").toDouble())/1000; firstMeasurement = false;
        }
        if(timeRegExp->exactMatch(dataListToAppend.first()))
        {
            plotDataMaintainer->x.append(((dataListToAppend.first().remove('s').toDouble())/1000-firstTimeRead));
            dataTimeBuffor.append(QString::number(plotDataMaintainer->x.last()));
            dataTimeBuffor.append("\r\n");
            dataListToAppend.removeFirst();

            if(plotDataMaintainer->x.constLast()>4500)
            {
                plotDataMaintainer->x.removeFirst();
                plotDataMaintainer->y.removeFirst();
                emit plotRangeExceeded(plotDataMaintainer->x.value(plotDataMaintainer->x.length()-1)-plotDataMaintainer->x.value(plotDataMaintainer->x.length()-2));
                //ui->customPlot->xAxis->moveRange(x.value(x.length()-1)-x.value(x.length()-2));
            }
        }
        else if(dataRegExp->exactMatch(dataListToAppend.first()))
        {
            dataBuffor.append(dataListToAppend.first());
            dataBuffor.append("\r\n");
            plotDataMaintainer->y.append(dataListToAppend.first().toDouble());
            dataListToAppend.removeFirst();
        }
    }
}

void SerialPortReader::setFirstMeasurement(bool value)
{
    firstMeasurement = value;
}

void SerialPortReader::setFaultyDataDetected(bool value)
{
    faultyDataDetected = value;
}

QString SerialPortReader::getDataBuffor() const
{
    return dataBuffor;
}

void SerialPortReader::clearDataBuffor()
{
    dataBuffor.clear();
}

QString SerialPortReader::getDataTimeBuffor() const
{
    return dataTimeBuffor;
}

void SerialPortReader::clearDataTimeBuffor()
{
    dataTimeBuffor.clear();
}
