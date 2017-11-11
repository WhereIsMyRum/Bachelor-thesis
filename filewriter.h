#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QDirIterator>
#include <QStringList>
#include <QDir>
#include <QFileInfo>
#include <dlib/matrix.h>

class FileWriter : public QWidget
{
public:
    FileWriter(QString);
public slots:
    void WriteToFile(QString fileName, QString data);
    QString MakeNewFile(QString fileName);
    std::vector<dlib::matrix<double,8,1>> ReadTrainingData(const QString pathToTrainingData, std::vector<double>& labels);

public:
    QString pathToSaveDirectory;

};

#endif // FILEWRITER_H
