#include "languagereadingfile.h"
#include <QFile>
#include <QTextStream>

LanguageReadingFile::LanguageReadingFile(QString file){
    m_filename = file;
}

LanguageReadingFile::~LanguageReadingFile()
{

}

void LanguageReadingFile::write(QTreeWidget* tree){
    QFile file(m_filename);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);   // we will serialize the data into the file
        for (int i=0;i<tree->topLevelItemCount();++i){
            out << tree->topLevelItem(i)->text(0) <<" "<< tree->topLevelItem(i)->text(1) <<"\n";
        }
    }
    file.close();
}

QMap<QString,int> LanguageReadingFile::read()
{
    QFile file(m_filename);
    QMap<QString,int> maplist;
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList  fields = line.split(" ");
            if (fields.length()==2)
                maplist[fields[0]] = fields[1].toInt();
        }
    }
    file.close();
    return maplist;
}
