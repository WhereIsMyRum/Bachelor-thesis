#include "serialportreader.h"



SerialPortReader::SerialPortReader()
{
    dataRegExp = new QRegExp("\\d{1,3}\\.\\d{2}");
    dataRawRegExp = new QRegExp("\\d{1,3}\\.\\d{2}r"); //tylko do sygnału surowego
    timeRegExp = new QRegExp("\\d{1,20}t");
    firstMeasurement = true;
    faultyDataDetected = false;
}

void SerialPortReader::ReadSerial(QByteArray serialData, PlotDataMaintainer* plotDataMaintainer, Plotter *plotter)
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
    if(!dataListToAppend.isEmpty() && !dataRegExp->exactMatch(dataListToAppend.last()) && !timeRegExp->exactMatch(dataListToAppend.last()) && !dataRawRegExp->exactMatch(dataListToAppend.last()))
    {
        faultyDataDetected = true;
        faultyData = dataListToAppend.last();
        dataListToAppend.removeLast();
    }

    while(dataListToAppend.length() > 0 && !dataListToAppend.isEmpty())
    {
        if(firstMeasurement && !dataListToAppend.first().contains("t")) dataListToAppend.removeFirst();
        if(firstMeasurement && dataListToAppend.first().contains("t"))
        {
            QString temp = dataListToAppend.first();
            firstTimeRead = (temp.remove("t").toDouble())/1000; firstMeasurement = false;
        }
        if(timeRegExp->exactMatch(dataListToAppend.first()))
        {
            plotDataMaintainer->x_sig.append(((dataListToAppend.first().remove('t').toDouble())/1000-firstTimeRead));
            plotter->x.append(((dataListToAppend.first().remove('t').toDouble())/1000-firstTimeRead));
            dataTimeBuffor.append(QString::number(plotDataMaintainer->x_sig.last()));
            dataTimeBuffor.append("\r\n");
            dataListToAppend.removeFirst();

            if(plotDataMaintainer->x_sig.constLast()>4500)
            {
                plotDataMaintainer->x_sig.removeFirst();
                plotter->x.removeFirst();
                plotter->y.removeFirst();
                if(!plotDataMaintainer->y_sig.empty()) plotDataMaintainer->y_sig.removeFirst();
                if(!plotDataMaintainer->y_raw.empty()) plotDataMaintainer->y_raw.removeFirst();
                emit plotRangeExceeded(plotDataMaintainer->x_sig.value(plotDataMaintainer->x_sig.length()-1)-plotDataMaintainer->x_sig.value(plotDataMaintainer->x_sig.length()-2));
                //emit plotRangeExceeded(plotter->x.value(plotter->x.length()-1)-plotter->x.value(plotter->x.length()-2));
                //ui->customPlot->xAxis->moveRange(x.value(x.length()-1)-x.value(x.length()-2));
            }
        }
        else if(dataRegExp->exactMatch(dataListToAppend.first()))
        {
            dataBuffor.append(dataListToAppend.first());
            dataBuffor.append("\r\n");
            plotDataMaintainer->y_sig.append(dataListToAppend.first().toDouble());
            plotter->y.append(dataListToAppend.first().toDouble());
            dataListToAppend.removeFirst();
        }
        else if(dataRawRegExp->exactMatch(dataListToAppend.first()))
        {
            dataListToAppend.first().remove('r');
            rawDataBuffor.append(dataListToAppend.first());
            rawDataBuffor.append("\r\n");
            plotDataMaintainer->y_raw.append(dataListToAppend.first().toDouble());
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

QString SerialPortReader::getRawDataBuffor() const
{
    return rawDataBuffor;
}

void SerialPortReader::clearRawDataBuffor()
{
    rawDataBuffor.clear();
}

