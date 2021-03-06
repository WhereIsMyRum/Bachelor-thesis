#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QThread>
#include <QList>
#include <QException>
#include <QDateTime>
#include <QSignalBlocker>

#include "filewriter.h"
#include "qcustomplot.h"
#include "serialportreader.h"
#include "classifiersclass.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    void on_findDevicesButton_clicked();
    void on_startMeasurementButton_clicked();
    void on_stopMeasurementButton_clicked();
    void on_exitButton_clicked();
    void on_connectDeviceButton_clicked();
    void on_disconnectDeviceButton_clicked();
    void on_closeWindowButton_clicked();

    void readSerial();
    void shiftPlot(double);

private:
    Ui::MainWindow *ui;

    QString arduinoLeonardoPortName;
    QString myDataFileName;
    QString myRawDataFileName;
    QString myTimeFileName;

    QStringList dataList;

    QSerialPort *arduino;

    //QVector<double> freqTab;

    QByteArray dataBytes;

    FileWriter *fileWriterInstance;
    SerialPortReader *serialPortReaderInstance;
    Plotter *plotter;
    SignalAnalyser *signalAnalyser;
    ClassifiersClass *signalClassifier;

signals:
    void shiftSecondPlot(double);
};

#endif // MAINWINDOW_H
