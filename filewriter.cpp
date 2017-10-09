#include "filewriter.h"

FileWriter::FileWriter(QString usersPath)
{
    pathToSaveDirectory = usersPath;
}

QString FileWriter::MakeNewFile()
{
    pathToSaveDirectory = "C:/QtProjects/inz2/Measurements/";
    QStringList txtFilesList;
    QString newFileName = "test1.txt";
    int newFileNumber = 2;
    bool fileExists = true;

    QDirIterator it(pathToSaveDirectory, QStringList() << "*.txt", QDir::Files, QDirIterator::Subdirectories);      //tworzenie listy plikow *.txt w folderze
    while(it.hasNext()) txtFilesList.append(it.next().remove(pathToSaveDirectory));                                 //


    while(fileExists)                                                                               //sprawdz czy plik o nazwie test(i).txt istnieje
    {                                                                                               //jesli tak, zwieksz (i) o 1 i sprawdz znowu
        fileExists = txtFilesList.contains(newFileName);
        if(fileExists)
        {
            newFileName = "test";
            newFileName.append(QString("%1").arg(newFileNumber));
            newFileName.append(".txt");
            newFileNumber++;
        }
    }
    pathToSaveDirectory.append(newFileName);                                                                        //Dodaj nazwe pliku do absolute patha

    return pathToSaveDirectory;
}

void FileWriter::WriteToFile(const QString fileName, const QString data)
{
    QFile mFile(fileName);

    if(!mFile.open(QIODevice::WriteOnly | QIODevice::Append))                                       //Sprawdz czy mozna otworzyc plik do zapisu
    {
        qDebug() << "Could not open file for writting";
        return;
    }

    QTextStream out(&mFile);                                                                        //Zapisz dane do pliku
    out << data;                                                                                    //

    mFile.flush();
    mFile.close();

}

