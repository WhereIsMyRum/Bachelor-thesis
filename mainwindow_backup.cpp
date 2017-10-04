#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    arduino = new QSerialPort(this);
    this->setFixedSize(750,355);
    MainWindow::makePlot();
    firstMeasurement = true;

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
                arduino->setBaudRate(QSerialPort::Baud9600);
                arduino->setDataBits(QSerialPort::Data8);
                arduino->setFlowControl(QSerialPort::NoFlowControl);
                arduino->setParity(QSerialPort::NoParity);
                arduino->setStopBits(QSerialPort::OneStop);
                ui->startMeasurementButton->setEnabled(true);
            }
        }
        ui->connectDeviceButton->setEnabled(false);
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

    statusBar()->showMessage("Measurement in progress...");

}

//Zakończenie pomiaru
void MainWindow::on_stopMeasurementButton_clicked()
{
    QObject::disconnect(arduino,SIGNAL(readyRead()),this,SLOT(readSerial()));                         //rozlacz port ze slotem do odczytu z portu

    ui->startMeasurementButton->setEnabled(true);
    ui->exitButton->setEnabled(true);
    ui->stopMeasurementButton->setEnabled(false);

    WriteToFile::Write(MyDataFileName,dataBuffor);
    WriteToFile::Write(MyTimeFileName,dataTimeBuffor);

    firstMeasurement = true;
    dataBuffor.clear();
    dataTimeBuffor.clear();

    statusBar()->showMessage("Measurement terminated.",4000);

}

//Wyłączenie aplikacji
void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}


//Funkcja odpowiadająca za odczyt danych z portu szeregowego
void MainWindow::readSerial()
{
    QByteArray serialData = arduino->readLine();
    QString *temp1 = new QString(QString::fromStdString(serialData.toStdString()));

    serialData = arduino->readLine();
    QString *temp2 = new QString(QString::fromStdString(serialData.toStdString()));

    if(temp1->contains("s") )
    {

        dataBuffor.append(*temp2);

        temp1->remove("s");
        dataTimeBuffor.append(*temp1);

    }

    else
    {
        dataBuffor.append(*temp1);

        temp2->remove("s");
        dataTimeBuffor.append(*temp2);
    }

    if(!firstMeasurement)
    {
        y.append(temp1->toDouble());
        x.append(temp2->toDouble()-firstTimeRead);

        if(x.constLast()>1000)
        {
            ui->customPlot->xAxis->moveRange(x.value(x.length()-1)-x.value(x.length()-2));
            x.removeFirst();
            y.removeFirst();
        }
    }

    if(firstMeasurement)
    {
        firstTimeRead = temp2->toDouble();
        x.clear();y.clear();
        firstMeasurement = false;
    }

    MainWindow::updatePlot();
    /*
    ui->textEdit->setPlainText(temp);
    dataBuffor.append(temp);
    //WriteToFile::Write(MyFileName, temp);*/
}

void MainWindow::makePlot()
{
    ui->customPlot->addGraph();
    ui->customPlot->xAxis->setLabel("t[s]");
    ui->customPlot->yAxis->setLabel("U[mV]");
    ui->customPlot->xAxis->setRange(0,2000);
    ui->customPlot->yAxis->setRange(0,2000);
    ui->customPlot->replot();
}

void MainWindow::updatePlot()
{
    //qDebug() << "I'm here";
    ui->customPlot->graph(0)->setData(x,y);
    ui->customPlot->replot();
    //ui->customPlot->rescaleAxes();
    ui->customPlot->update();
}

