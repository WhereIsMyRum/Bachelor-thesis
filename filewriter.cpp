#include "filewriter.h"

FileWriter::FileWriter(QString usersPath)
{
    pathToSaveDirectory = usersPath;
}

QString FileWriter::MakeNewFile(QString fileName)
{
    QStringList txtFilesList;
    QString newFileName = fileName + ".txt";
    QString tempPathToSaveDirectory = pathToSaveDirectory;
    int newFileNumber = 2;
    bool fileExists = true;

    QDirIterator it(pathToSaveDirectory, QStringList() << "*.txt", QDir::Files, QDirIterator::Subdirectories);      //tworzenie listy plikow *.txt w folderze
    while(it.hasNext()) txtFilesList.append(it.next().remove(pathToSaveDirectory));                                 //

    qDebug() << txtFilesList;
    while(fileExists)                                                                               //sprawdz czy plik o nazwie test(i).txt istnieje
    {                                                                                               //jesli tak, zwieksz (i) o 1 i sprawdz znowu
        fileExists = txtFilesList.contains(newFileName);
        if(fileExists)
        {
            newFileName = fileName;
            newFileName.append(QString("%1").arg(newFileNumber));
            newFileName.append(".txt");
            newFileNumber++;
        }
    }
    tempPathToSaveDirectory.append(newFileName);                                                                        //Dodaj nazwe pliku do absolute patha

    return tempPathToSaveDirectory;
}

void FileWriter::WriteToFile(const QString fileName, const QString data)
{
    QFile mFile(fileName);

    if(!mFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))                                       //Sprawdz czy mozna otworzyc plik do zapisu
    {
        QMessageBox::warning(this,"Error","Could not open file for writting!");
        return;
    }

    QTextStream out(&mFile);                                                                        //Zapisz dane do pliku
    out << data << endl;                                                                            //

    mFile.flush();
    mFile.close();
}

std::vector<dlib::matrix<double,8,1>> FileWriter::ReadTrainingData(const QString pathToTrainingData, std::vector<double>& labels)
{
    QFile trainingDataFile(pathToTrainingData);
    QStringList trainingDataVectorsList;
    std::vector<dlib::matrix<double,8,1>> dataVector;

    if(!trainingDataFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,"Error","Could not read from training data file!");
        std::vector<dlib::matrix<double,8,1>> emptyMatrix;
        return emptyMatrix;
    }

    QTextStream trainingDataTextStream(&trainingDataFile);
    while(!trainingDataTextStream.atEnd())
    {
        trainingDataVectorsList.append(trainingDataTextStream.readLine());
    }

    for(int i = 0; i < trainingDataVectorsList.length(); i++)
    {
        dlib::matrix<double,8,1> dataMatrix;
        QVector<double> dataQVector;
        QStringList singleDataList = trainingDataVectorsList.at(i).split(";");
        for(int j = 0; j < singleDataList.length(); j++)
        {
            if(j == 8) labels.push_back(singleDataList.at(j).toDouble());
            else dataQVector.append(singleDataList.at(j).toDouble());qDebug();
        }

        dataMatrix = dataQVector.at(0), dataQVector.at(1), dataQVector.at(2), dataQVector.at(3),  dataQVector.at(4),
                        dataQVector.at(5),  dataQVector.at(6),  dataQVector.at(7);

        dataVector.push_back(dataMatrix);
    }

    trainingDataFile.flush();
    trainingDataFile.close();

    return dataVector;
}

