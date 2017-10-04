#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    arduino = new QSerialPort(this);
    this->setFixedSize(850,450);
    MainWindow::makePlot();
    firstMeasurement = true;
    faultyDataDetected = false;

}

MainWindow::~MainWindow()
{
    if(arduino->isOpen())
    {
        arduino->close();
    }
    delete ui;
}

//Nawiązywanie połączenia z arduino.
void MainWindow::on_findDevicesButton_clicked()
{
    if(QSerialPortInfo::availablePorts().length()  == 0)
    {
        statusBar()->showMessage("No availalble device found.", 2000);
    }
    else
    {
        statusBar()->showMessage("Devices detected.",2000);
        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())               //zapelnianie devicesListWidget nazwami wykrytych urzadzen.
        {
            bool itemNotOnList = true;
            for(int i = 0; i < ui->devicesListWidget->count(); i++)                                     //sprawdz, czy dane urzadzenie nie znajduje sie juz na liscie
            {
                QString item = ui->devicesListWidget->item(i)->text();

                if(item == serialPortInfo.manufacturer()) itemNotOnList = false;
            }
            if(itemNotOnList)                                                                           //jesli sie nie znajduje, umiesc je.
            {
                 ui->devicesListWidget->addItem(serialPortInfo.manufacturer());
                 devicesList.append(serialPortInfo.manufacturer());
            }
        }
        ui->connectDeviceButton->setEnabled(true);
     }
}

void MainWindow::on_connectDeviceButton_clicked()
{
    //ustaw połaczenie z danym urzadzeniem polaczonym serial portem
    if(ui->devicesListWidget->currentItem() != 0)                                                      //Wykonaj ten fragment tylko, jesli na liscie zaznaczona
    {                                                                                                  //zostala jakas pozycja
        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
        {
            if(serialPortInfo.manufacturer() == ui->devicesListWidget->currentItem()->text())          //Znajdz wsrod podlaczonych urzadzen to, które zostało zaznaczone
            {                                                                                          //na deviceListWidget przez uzytkownika
                arduino_leonardo_port_name = serialPortInfo.portName();
                arduino->setPortName(arduino_leonardo_port_name);
                arduino->open(QSerialPort::ReadOnly);
                arduino->setBaudRate(QSerialPort::Baud38400);
                arduino->setDataBits(QSerialPort::Data8);
                arduino->setFlowControl(QSerialPort::NoFlowControl);
                arduino->setParity(QSerialPort::NoParity);
                arduino->setStopBits(QSerialPort::OneStop);

                statusBar()->showMessage("Device connected.", 2000);
            }
        }
        ui->startMeasurementButton->setEnabled(true);
        ui->connectDeviceButton->setEnabled(false);
        ui->disconnectDeviceButton->setEnabled(true);
    }
    else                                                                                               //jesli nie zaznaczono zadnej pozycji na liscie - wyswietl MessageBoxa
    {
        QMessageBox::warning(this,"Error","Make sure to select a device!");
    }

}

//Rozpoczęcie pomiaru
void MainWindow::on_startMeasurementButton_clicked()
{
    arduino->clear();

    MyDataFileName = WriteToFile::MakeNewFile();                                                           //pobierz nazwe pliku do zapisu z funkcji MakeNewFile()
    MyTimeFileName = MyDataFileName;
    MyTimeFileName.replace(".txt","_time.txt");

    QDateTime dateAndTime;                                                                             //wstaw date i czas w pierwszej linii pomiaru
    WriteToFile::Write(MyDataFileName,dateAndTime.currentDateTime().toString());

    QObject::connect(arduino,SIGNAL(readyRead()),this,SLOT(readSerial()));                             //polacz sygnal z portu ze slotem do odczytu z portu

    ui->stopMeasurementButton->setEnabled(true);
    ui->startMeasurementButton->setEnabled(false);
    ui->exitButton->setEnabled(false);
    ui->disconnectDeviceButton->setEnabled(false);

    statusBar()->showMessage("Measurement in progress...");

}

//Zakończenie pomiaru
void MainWindow::on_stopMeasurementButton_clicked()
{
    QObject::disconnect(arduino,SIGNAL(readyRead()),this,SLOT(readSerial()));                         //rozlacz port ze slotem do odczytu z portu

    ui->startMeasurementButton->setEnabled(true);
    ui->exitButton->setEnabled(true);
    ui->stopMeasurementButton->setEnabled(false);
    ui->disconnectDeviceButton->setEnabled(true);

    WriteToFile::Write(MyDataFileName,dataBuffor);
    WriteToFile::Write(MyTimeFileName,dataTimeBuffor);

    MainWindow::makePlot();

    firstMeasurement = true;
    faultyDataDetected = false;
    dataBuffor.clear();
    dataTimeBuffor.clear();
    x.clear();
    y.clear();
    statusBar()->showMessage("Measurement terminated.",2000);

}

//Wyłączenie aplikacji
void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}


//Funkcja odpowiadająca za odczyt danych z portu szeregowego
void MainWindow::readSerial()
{
    QByteArray serialData = arduino->readAll();
    QString *temp1 = new QString(QString::fromStdString(serialData.toStdString()));
    QRegExp *rx1 = new QRegExp("\\d{1,3}\\.[0-9]{2}");
    QRegExp *rx2 = new QRegExp("\\d{1,20}s");
    QStringList dataListToAppend = temp1->split("\r\n");
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

    if(!dataListToAppend.isEmpty() && !rx1->exactMatch(dataListToAppend.last()) && !rx2->exactMatch(dataListToAppend.last()))
    {
        faultyDataDetected = true;
        faultyData = dataListToAppend.last();
        dataListToAppend.removeLast();
    }

    while(dataListToAppend.length() > 0 && !dataListToAppend.isEmpty())
    {
        if(firstMeasurement && dataListToAppend.first().contains("s"))
        {
            QString temp = dataListToAppend.first();
            firstTimeRead = (temp.remove("s").toDouble())/1000; firstMeasurement = false;
        }
        if(rx2->exactMatch(dataListToAppend.first()))
        {
            x.append(((dataListToAppend.first().remove('s').toDouble())/1000-firstTimeRead));
            dataTimeBuffor.append(QString::number(x.last()));
            dataTimeBuffor.append("\r\n");
            dataListToAppend.removeFirst();

            if(x.constLast()>4500)
            {
                ui->customPlot->xAxis->moveRange(x.value(x.length()-1)-x.value(x.length()-2));
                x.removeFirst();
                y.removeFirst();
            }
        }
        else if(rx1->exactMatch(dataListToAppend.first()))
        {
            dataBuffor.append(dataListToAppend.first());
            dataBuffor.append("\r\n");
            y.append(dataListToAppend.first().toDouble());
            dataListToAppend.removeFirst();
        }
    }
    MainWindow::updatePlot();
}

void MainWindow::makePlot()
{
    ui->customPlot->addGraph();
    ui->customPlot->xAxis->setLabel("t[s]");
    ui->customPlot->yAxis->setLabel("U[mV]");
    ui->customPlot->xAxis->setRange(0,5000);
    ui->customPlot->yAxis->setRange(0,2000);
    ui->customPlot->replot();
}

void MainWindow::updatePlot()
{

    /*double freq = 1/((x.last()-x.value(x.length()-2))/1000);
    qDebug() << freq;
    if(freqTab.length() == 5)
    {
        freqTab.removeFirst();
        freqTab.append(freq);
        freq = freqTab.at(0);
        freq += freqTab.at(1);
        freq += freqTab.at(2);
        freq += freqTab.at(3);
        freq += freqTab.at(4);
        //qDebug() << freq/5;

    } sprawdzenie gita
    else freqTab.append(freq);*/

    ui->customPlot->graph(0)->setData(x,y);
    ui->customPlot->replot();
    ui->customPlot->update();
}


void MainWindow::on_disconnectDeviceButton_clicked()
{
    arduino->reset();

    ui->connectDeviceButton->setEnabled(true);
    ui->disconnectDeviceButton->setEnabled(false);

    statusBar()->showMessage("Device disconnected.", 2000);
}
