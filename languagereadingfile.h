#ifndef LANGUAGEREADINGFILE_H
#define LANGUAGEREADINGFILE_H

#include <QTreeWidget>

class LanguageReadingFile
{
public:
    LanguageReadingFile(QString file);
    ~LanguageReadingFile();
    void write(QTreeWidget *tree);
    QMap<QString, int> read();

private:
    QString m_filename;



};

#endif // LANGUAGEREADINGFILE_H
