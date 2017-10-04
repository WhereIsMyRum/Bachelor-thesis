#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QThread>
#include <QPlainTextEdit>
#include <QList>
#include <QString>
#include <QException>
#include <QDateTime>
#include <QVector>
#include <QSignalBlocker>

#include "writetofile.h"
#include "qcustomplot.h"


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

    void readSerial();
    void makePlot();
    void updatePlot();


private:
    Ui::MainWindow *ui;
    quint16 arduino_leonardo_vendor_id;
    quint16 arduino_leonardo_product_id;
    QString arduino_leonardo_port_name;
    QSerialPort *arduino;
    QList<QString> devicesList;
    QString MyDataFileName;
    QString MyTimeFileName;
    QString dataBuffor;
    QString dataTimeBuffor;
    QStringList dataList;
    QVector<double> x,y;
    QSignalBlocker *blockSignal;
    QString faultyData;
    //QVector<double> freqTab;
    bool firstMeasurement;
    bool faultyDataDetected;
    double firstTimeRead;
};

#endif // MAINWINDOW_H
