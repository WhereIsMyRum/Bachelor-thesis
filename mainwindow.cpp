#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    arduino = new QSerialPort(this);
    fileWriterInstance = new FileWriter("C:/QtProjects/inz2/Measurements/");
    serialPortReaderInstance = new SerialPortReader();
    plotDataMaintainer = new PlotDataMaintainer();

    this->setFixedSize(850,450);
    MainWindow::makePlot();

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

    MyDataFileName = fileWriterInstance->MakeNewFile();                                                           //pobierz nazwe pliku do zapisu z funkcji MakeNewFile()
    MyTimeFileName = MyDataFileName;
    MyTimeFileName.replace(".txt","_time.txt");

    QDateTime dateAndTime;                                                                             //wstaw date i czas w pierwszej linii pomiaru
    fileWriterInstance->WriteToFile(MyDataFileName,dateAndTime.currentDateTime().toString());

    QObject::connect(arduino,SIGNAL(readyRead()),this,SLOT(readSerial()));                             //polacz sygnal z portu ze slotem do odczytu z portu
    QObject::connect(serialPortReaderInstance,SIGNAL(plotRangeExceeded(double)),this,SLOT(shiftPlot(double)));

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

    fileWriterInstance->WriteToFile(MyDataFileName,dataBuffor);
    fileWriterInstance->WriteToFile(MyTimeFileName,dataTimeBuffor);

    MainWindow::makePlot();

    serialPortReaderInstance->setFirstMeasurement(true);
    serialPortReaderInstance->setFaultyDataDetected(false);
    dataBuffor.clear();
    dataTimeBuffor.clear();
    plotDataMaintainer->x.clear();
    plotDataMaintainer->y.clear();
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
    serialPortReaderInstance->ReadSerial(dataBuffor, dataTimeBuffor, arduino->readAll(), plotDataMaintainer);

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

    }ada
    else freqTab.append(freq);*/

    ui->customPlot->graph(0)->setData(plotDataMaintainer->x,plotDataMaintainer->y);
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

void MainWindow::shiftPlot(double valueToBeShifted)
{
    ui->customPlot->xAxis->moveRange(valueToBeShifted);
}
