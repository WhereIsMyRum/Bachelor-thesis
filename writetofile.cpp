#include "writetofile.h"

QString WriteToFile::dir;

QString WriteToFile::MakeNewFile()
{
    dir = "C:/QtProjects/inz2/Measurements/";
    QStringList txtFilesList;
    QString newFileName = "test1.txt";
    int i = 2;
    bool fileExists = true;

    QDirIterator it(dir, QStringList() << "*.txt", QDir::Files, QDirIterator::Subdirectories);      //tworzenie listy plikow *.txt w folderze
    while(it.hasNext()) txtFilesList.append(it.next().remove(dir));                                 //


    while(fileExists)                                                                               //sprawdz czy plik o nazwie test(i).txt istnieje
    {                                                                                               //jesli tak, zwieksz (i) o 1 i sprawdz znowu
        fileExists = txtFilesList.contains(newFileName);
        if(fileExists)
        {
            newFileName = "test";
            newFileName.append(QString("%1").arg(i));
            newFileName.append(".txt");
            i++;
        }
    }
    dir.append(newFileName);                                                                        //Dodaj nazwe pliku do absolute patha

    return dir;
}

void WriteToFile::Write(const QString Filename, const QString data)
{
    QFile mFile(Filename);

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

