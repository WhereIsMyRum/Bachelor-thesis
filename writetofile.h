#ifndef WRITETOFILE_H
#define WRITETOFILE_H

#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QDirIterator>
#include <QStringList>
#include <QDir>
#include <QFileInfo>

class WriteToFile
{
public:
    WriteToFile();
public slots:
    static void Write(QString Filename, QString data);
    static QString MakeNewFile();
public:
    static QString dir;

};

#endif // WRITETOFILE_H
