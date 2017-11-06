#include "serialportreader.h"



SerialPortReader::SerialPortReader()
{
    dataRegExp = new QRegExp("\\d{1,3}\\.\\d{2}d");
    dataRawRegExp = new QRegExp("\\d{1,3}\\.\\d{2}r"); //tylko do sygnału surowego
    timeRegExp = new QRegExp("\\d{1,20}t");
    firstMeasurement = true;
    faultyDataDetected = false;
}

void SerialPortReader::ReadSerial(QByteArray serialData, Plotter *plotter, SignalAnalyser *analyser)
{
    serialDataString = new QString(QString::fromStdString(serialData.toStdString()));
    QStringList dataListToAppend = serialDataString->split("\r\n");
    while(dataListToAppend.contains("")) dataListToAppend.removeAt(dataListToAppend.indexOf(""));

    while(dataListToAppend.length() > 0 && !dataListToAppend.isEmpty())
    {
        if(firstMeasurement && !dataListToAppend.first().contains("t")) dataListToAppend.removeFirst();
        if(firstMeasurement && dataListToAppend.first().contains("t"))
        {
            QString temp = dataListToAppend.first();
            firstTimeRead = (temp.remove("t").toDouble())/1000000; firstMeasurement = false;
        }
        if(timeRegExp->exactMatch(dataListToAppend.first()))
        {
            plotter->x.append(((dataListToAppend.first().remove('t').toDouble())/1000000-firstTimeRead));
            dataTimeBuffor.append(QString::number(plotter->x.last()));
            dataTimeBuffor.append("\r\n");
            dataListToAppend.removeFirst();

            if(plotter->x.constLast()>15)
            {
                plotter->x.removeFirst();

                if(!plotter->y_sig.empty()) plotter->y_sig.removeFirst();
                if(!plotter->y_sig.empty()) plotter->y_raw.removeFirst();

                emit plotRangeExceeded(plotter->x.value(plotter->x.length()-1)-plotter->x.value(plotter->x.length()-2));
            }
        }
        else if(dataRegExp->exactMatch(dataListToAppend.first()))
        {
            dataListToAppend.first().remove('d');
            dataBuffor.append(dataListToAppend.first());
            dataBuffor.append("\r\n");
            plotter->y_sig.append(dataListToAppend.first().toDouble());
            dataListToAppend.removeFirst();

        }
        else if(dataRawRegExp->exactMatch(dataListToAppend.first()))
        {
            dataListToAppend.first().remove('r');
            rawDataBuffor.append(dataListToAppend.first());
            rawDataBuffor.append("\r\n");

            plotter->y_raw.append(dataListToAppend.first().toDouble()-2.4);
            analyser->signalValues.append(dataListToAppend.first().toDouble()-2.4);

            dataListToAppend.removeFirst();

            if(analyser->signalValues.length() == WINDOW_LENGTH)
            {
                analyser->getSignalParams();
                analyser->signalValues.clear();
            }
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

