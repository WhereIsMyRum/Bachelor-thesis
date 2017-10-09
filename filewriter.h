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

class FileWriter
{
public:
    FileWriter(QString);
public slots:
    void WriteToFile(QString fileName, QString data);
    QString MakeNewFile();
public:
    QString pathToSaveDirectory;

};

#endif // FILEWRITER_H
