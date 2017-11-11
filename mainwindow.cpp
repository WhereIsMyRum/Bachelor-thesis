#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    arduino = new QSerialPort(this);
    fileWriterInstance = new FileWriter("C:/QtProjects/Inzynierka/Measurements/");
    serialPortReaderInstance = new SerialPortReader();
    plotter = new Plotter(this);
    signalAnalyser = new SignalAnalyser(this);

    std::vector<double> labels;

    signalClassifier = new ClassifiersClass(fileWriterInstance->ReadTrainingData("C:/QtProjects/Inzynierka/extracted_features.txt", labels),labels); // get vector of matrices containing training samples with labels;

    /*signalAnalyser->signalValues.append(0);	signalAnalyser->signalValues.append(0.104528463267653);	signalAnalyser->signalValues.append(0.207911690817759);
    signalAnalyser->signalValues.append(0.309016994374947);	signalAnalyser->signalValues.append(0.406736643075800);	signalAnalyser->signalValues.append(0.500000000000000);
    signalAnalyser->signalValues.append(0.587785252292473);	signalAnalyser->signalValues.append(0.669130606358858);	signalAnalyser->signalValues.append(0.743144825477394);
    signalAnalyser->signalValues.append(0.809016994374948);	signalAnalyser->signalValues.append(0.866025403784439);	signalAnalyser->signalValues.append(0.913545457642601);
    signalAnalyser->signalValues.append(0.951056516295154);	signalAnalyser->signalValues.append(0.978147600733806);	signalAnalyser->signalValues.append(0.994521895368273);
    signalAnalyser->signalValues.append(1);	signalAnalyser->signalValues.append(0.994521895368273);	signalAnalyser->signalValues.append(0.978147600733806);
    signalAnalyser->signalValues.append(0.951056516295154);	signalAnalyser->signalValues.append(0.913545457642601);	signalAnalyser->signalValues.append(0.866025403784439);
    signalAnalyser->signalValues.append(0.809016994374948);	signalAnalyser->signalValues.append(0.743144825477394);	signalAnalyser->signalValues.append(0.669130606358858);
    signalAnalyser->signalValues.append(0.587785252292473);	signalAnalyser->signalValues.append(0.500000000000000);	signalAnalyser->signalValues.append(0.406736643075800);
    signalAnalyser->signalValues.append(0.309016994374947);	signalAnalyser->signalValues.append(0.207911690817759);	signalAnalyser->signalValues.append(0.104528463267653);
    signalAnalyser->signalValues.append(1.22464679914735e-16);	signalAnalyser->signalValues.append(-0.104528463267654);	signalAnalyser->signalValues.append(-0.207911690817760);
    signalAnalyser->signalValues.append(-0.309016994374947);	signalAnalyser->signalValues.append(-0.406736643075800);	signalAnalyser->signalValues.append(-0.500000000000000);
    signalAnalyser->signalValues.append(-0.587785252292473);

    signalAnalyser->signalValues.append(-0.669130606358858);	signalAnalyser->signalValues.append(-0.743144825477394);	signalAnalyser->signalValues.append(-0.809016994374947);	signalAnalyser->signalValues.append(-0.866025403784439);	signalAnalyser->signalValues.append(-0.913545457642601);	signalAnalyser->signalValues.append(-0.951056516295154);	signalAnalyser->signalValues.append(-0.978147600733806);
    signalAnalyser->signalValues.append(-0.994521895368273);	signalAnalyser->signalValues.append(-1);                 	signalAnalyser->signalValues.append(-0.994521895368273);	signalAnalyser->signalValues.append(-0.978147600733806);	signalAnalyser->signalValues.append(-0.951056516295154);	signalAnalyser->signalValues.append(-0.913545457642601);	signalAnalyser->signalValues.append(-0.866025403784439);	signalAnalyser->signalValues.append(-0.809016994374948);
    signalAnalyser->signalValues.append(-0.743144825477394);	signalAnalyser->signalValues.append(-0.669130606358858);	signalAnalyser->signalValues.append(-0.587785252292473);	signalAnalyser->signalValues.append(-0.500000000000000);	signalAnalyser->signalValues.append(-0.406736643075800);	signalAnalyser->signalValues.append(-0.309016994374948);	signalAnalyser->signalValues.append(-0.207911690817759);
    signalAnalyser->signalValues.append(-0.104528463267653);	signalAnalyser->signalValues.append(-2.44929359829471e-16);	signalAnalyser->signalValues.append(0.104528463267654);     signalAnalyser->signalValues.append(0.207911690817760);     signalAnalyser->signalValues.append(0.309016994374948);     signalAnalyser->signalValues.append(0.406736643075801);	signalAnalyser->signalValues.append(0.500000000000000);
    signalAnalyser->signalValues.append(0.587785252292473);	signalAnalyser->signalValues.append(0.669130606358859);         signalAnalyser->signalValues.append(0.743144825477394);     signalAnalyser->signalValues.append(0.809016994374947);     signalAnalyser->signalValues.append(0.866025403784438);     signalAnalyser->signalValues.append(0.913545457642601); signalAnalyser->signalValues.append(0.951056516295154);
    signalAnalyser->signalValues.append(0.978147600733806);	signalAnalyser->signalValues.append(0.994521895368273);         signalAnalyser->signalValues.append(1);                     signalAnalyser->signalValues.append(0.994521895368274);     signalAnalyser->signalValues.append(0.978147600733806);     signalAnalyser->signalValues.append(0.951056516295154);	signalAnalyser->signalValues.append(0.913545457642602);	signalAnalyser->signalValues.append(0.866025403784439);
    signalAnalyser->signalValues.append(0.809016994374948);	signalAnalyser->signalValues.append(0.743144825477395);         signalAnalyser->signalValues.append(0.669130606358860);     signalAnalyser->signalValues.append(0.587785252292473);     signalAnalyser->signalValues.append(0.500000000000000);     signalAnalyser->signalValues.append(0.406736643075801);	signalAnalyser->signalValues.append(0.309016994374948);
    signalAnalyser->signalValues.append(0.207911690817759);	signalAnalyser->signalValues.append(0.104528463267654);         signalAnalyser->signalValues.append(3.67394039744206e-16);  signalAnalyser->signalValues.append(-0.104528463267654);	signalAnalyser->signalValues.append(-0.207911690817758);	signalAnalyser->signalValues.append(-0.309016994374947);	signalAnalyser->signalValues.append(-0.406736643075800);
    signalAnalyser->signalValues.append(-0.499999999999999);	signalAnalyser->signalValues.append(-0.587785252292471);	signalAnalyser->signalValues.append(-0.669130606358858);	signalAnalyser->signalValues.append(-0.743144825477394);	signalAnalyser->signalValues.append(-0.809016994374946);	signalAnalyser->signalValues.append(-0.866025403784438);	signalAnalyser->signalValues.append(-0.913545457642601);
    signalAnalyser->signalValues.append(-0.951056516295153);	signalAnalyser->signalValues.append(-0.978147600733805);	signalAnalyser->signalValues.append(-0.994521895368273);	signalAnalyser->signalValues.append(-1);                    signalAnalyser->signalValues.append(-0.994521895368273);	signalAnalyser->signalValues.append(-0.978147600733806);	signalAnalyser->signalValues.append(-0.951056516295154);	signalAnalyser->signalValues.append(-0.913545457642602);
    signalAnalyser->signalValues.append(-0.866025403784438);	signalAnalyser->signalValues.append(-0.809016994374948);	signalAnalyser->signalValues.append(-0.743144825477395);	signalAnalyser->signalValues.append(-0.669130606358859);	signalAnalyser->signalValues.append(-0.587785252292474);	signalAnalyser->signalValues.append(-0.500000000000001);	signalAnalyser->signalValues.append(-0.406736643075801);
    signalAnalyser->signalValues.append(-0.309016994374948);	signalAnalyser->signalValues.append(-0.207911690817761);	signalAnalyser->signalValues.append(-0.104528463267655);	signalAnalyser->signalValues.append(-4.89858719658941e-16);	signalAnalyser->signalValues.append(0.104528463267652);     signalAnalyser->signalValues.append(0.207911690817760);	signalAnalyser->signalValues.append(0.309016994374947);
    signalAnalyser->signalValues.append(0.406736643075800);	signalAnalyser->signalValues.append(0.499999999999999);	        signalAnalyser->signalValues.append(0.587785252292473);     signalAnalyser->signalValues.append(0.669130606358858);     signalAnalyser->signalValues.append(0.743144825477394);     signalAnalyser->signalValues.append(0.809016994374947);	signalAnalyser->signalValues.append(0.866025403784439);
    signalAnalyser->signalValues.append(0.913545457642600);	signalAnalyser->signalValues.append(0.951056516295153);	        signalAnalyser->signalValues.append(0.978147600733806);     signalAnalyser->signalValues.append(0.994521895368273);     signalAnalyser->signalValues.append(1);                     signalAnalyser->signalValues.append(0.994521895368274);	signalAnalyser->signalValues.append(0.978147600733806);	signalAnalyser->signalValues.append(0.951056516295154);
    signalAnalyser->signalValues.append(0.913545457642602);	signalAnalyser->signalValues.append(0.866025403784439);         signalAnalyser->signalValues.append(0.809016994374948);     signalAnalyser->signalValues.append(0.743144825477394);
    signalAnalyser->signalValues.append(0.669130606358858);	signalAnalyser->signalValues.append(0.587785252292474);         signalAnalyser->signalValues.append(0.500000000000000);     signalAnalyser->signalValues.append(0.406736643075800);     signalAnalyser->signalValues.append(0.309016994374948);     signalAnalyser->signalValues.append(0.207911690817759);	signalAnalyser->signalValues.append(0.104528463267655);	signalAnalyser->signalValues.append(6.12323399573677e-16);
    */

    /*signalAnalyser->signalValues.append(0);
    signalAnalyser->signalValues.append(5);
    signalAnalyser->signalValues.append(10);
    signalAnalyser->signalValues.append(7);
    signalAnalyser->signalValues.append(13);
    signalAnalyser->signalValues.append(4);
    signalAnalyser->signalValues.append(9);
    signalAnalyser->signalValues.append(3);*/
    //qDebug() << signalAnalyser->getSignalParams();

    plotter->setWindowFlag(Qt::Window);
    plotter->setVisible(false);

    QObject::connect(plotter,SIGNAL(closeWindow()),this,SLOT(on_closeWindowButton_clicked()));
    //this->setFixedSize(850,450);

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
                arduinoLeonardoPortName = serialPortInfo.portName();
                arduino->setPortName(arduinoLeonardoPortName);
                arduino->open(QSerialPort::ReadOnly);
                arduino->setBaudRate(QSerialPort::Baud115200);
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
    if(ui->baselineLineEdit->text() != "" && ui->fileNameLineEdit->text() != "")
    {
        arduino->clear();

        myDataFileName = fileWriterInstance->MakeNewFile(ui->fileNameLineEdit->text());                                                           //pobierz nazwe pliku do zapisu z funkcji MakeNewFile()

        myRawDataFileName = myDataFileName;
        myRawDataFileName.replace(".txt","_raw.txt");

        myTimeFileName = myDataFileName;
        myTimeFileName.replace(".txt","_time.txt");

        QDateTime dateAndTime;                                                                             //wstaw date i czas w pierwszej linii pomiaru
        fileWriterInstance->WriteToFile(myDataFileName,dateAndTime.currentDateTime().toString());
        fileWriterInstance->WriteToFile(myDataFileName, "Baseline modifier: " + ui->baselineLineEdit->text());

        plotter->makePlot();
        plotter->setVisible(true);
        plotter->showMaximized();

        QObject::connect(arduino,SIGNAL(readyRead()),this,SLOT(readSerial()));                             //polacz sygnal z portu ze slotem do odczytu z portu
        QObject::connect(serialPortReaderInstance,SIGNAL(plotRangeExceeded(double)),this,SLOT(shiftPlot(double)));
        QObject::connect(plotter,SIGNAL(stopMeasurement()),this,SLOT(on_stopMeasurementButton_clicked()));

        ui->stopMeasurementButton->setEnabled(true);
        ui->startMeasurementButton->setEnabled(false);
        ui->exitButton->setEnabled(false);
        ui->disconnectDeviceButton->setEnabled(false);

        statusBar()->showMessage("Measurement in progress...");
    }
    else
    {
        QMessageBox::warning(this,"Error","Make sure to enter baseline modifier and file name.");
    }
}

//Zakończenie pomiaru
void MainWindow::on_stopMeasurementButton_clicked()
{
    QObject::disconnect(arduino,SIGNAL(readyRead()),this,SLOT(readSerial()));                         //rozlacz port ze slotem do odczytu z portu
    QObject::disconnect(serialPortReaderInstance,SIGNAL(plotRangeExceeded(double)),this,SLOT(shiftPlot(double)));
    QObject::disconnect(plotter,SIGNAL(stopMeasurement()),this,SLOT(on_stopMeasurementButton_clicked()));

    ui->startMeasurementButton->setEnabled(true);
    ui->exitButton->setEnabled(true);
    ui->stopMeasurementButton->setEnabled(false);
    ui->disconnectDeviceButton->setEnabled(true);

    fileWriterInstance->WriteToFile(myDataFileName,serialPortReaderInstance->getDataBuffor());
    fileWriterInstance->WriteToFile(myRawDataFileName, serialPortReaderInstance->getRawDataBuffor());
    fileWriterInstance->WriteToFile(myTimeFileName,serialPortReaderInstance->getDataTimeBuffor());

    serialPortReaderInstance->setFirstMeasurement(true);
    serialPortReaderInstance->setFaultyDataDetected(false);
    serialPortReaderInstance->clearDataBuffor();
    serialPortReaderInstance->clearRawDataBuffor();
    serialPortReaderInstance->clearDataTimeBuffor();

    plotter->y_raw.clear();
    plotter->y_sig.clear();
    plotter->x.clear();
    statusBar()->showMessage("Measurement terminated.",2000);



}

//Wyłączenie aplikacji
void MainWindow::on_exitButton_clicked()
{
    qApp->exit();
}


//Funkcja odpowiadająca za odczyt danych z portu szeregowego
void MainWindow::readSerial()
{
    dataBytes.append(arduino->readAll());
    if(dataBytes.endsWith("\n"))
    {
        serialPortReaderInstance->ReadSerial(dataBytes, plotter, signalAnalyser, ui->baselineLineEdit->text().toDouble());
        dataBytes.clear();
        plotter->updatePlot();
    }

    if(!signalAnalyser->signalParams.empty())
    {

        plotter->updateSignalParams(signalAnalyser->signalParams);

        dlib::matrix<double,8,1> sampleDataMatrix;
        sampleDataMatrix = signalAnalyser->signalParams.at(0), signalAnalyser->signalParams.at(1), signalAnalyser->signalParams.at(2), signalAnalyser->signalParams.at(3),
                            signalAnalyser->signalParams.at(4), signalAnalyser->signalParams.at(5), signalAnalyser->signalParams.at(6), signalAnalyser->signalParams.at(7);

<<<<<<< HEAD
        if(signalClassifier->classifySignalUsingSVM(sampleDataMatrix)) {plotter->showContractionLabel();qDebug()<< "true";}
        else {plotter->hideContractionLabel();qDebug() << "false";}
        //qDebug() << "KRR: " << signalClassifier->classifySignalUsingKRR(sampleDataMatrix);

=======
        qDebug() << "SVM: " << signalClassifier->classifySignalUsingSVM(sampleDataMatrix);
        qDebug() << "KRR: " << signalClassifier->classifySignalUsingKRR(sampleDataMatrix);
>>>>>>> cc8001d5ff288d587c7c248e029b91ae221acddd

        signalAnalyser->signalParams.clear();
    }

}

void MainWindow::on_disconnectDeviceButton_clicked()
{
    arduino->close();

    ui->connectDeviceButton->setEnabled(true);
    ui->startMeasurementButton->setEnabled(false);
    ui->disconnectDeviceButton->setEnabled(false);

    statusBar()->showMessage("Device disconnected.", 2000);
}

void MainWindow::shiftPlot(double valueToBeShifted)
{
    emit shiftSecondPlot(valueToBeShifted);
}

void MainWindow::on_closeWindowButton_clicked()
{
    plotter->setVisible(false);
}
