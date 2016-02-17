#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QKeyEvent>
#include "goldendictLib/bgl_babylon.hh"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* event);

private slots:
    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_actionAbout_LR_triggered();

    void on_bKnow_clicked();

    void on_bTranslate_clicked();

    void on_bLoad_clicked();

    void on_bUndo_clicked();

    void on_bRemove_clicked();

    void on_bRemoveInFile_clicked();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_actionSave_triggered();

    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);

    void on_bGoogle_clicked();

    void on_bPaste_clicked();

    void on_lineEdit_returnPressed();

    void on_actionAdd_a_dictionary_triggered();

private:

    enum CommandState{
        NOTHING,
        I_KNOW,
        REMOVE
    };

    //methods
    void readFile(QString fileText);
    void readMemoryFile(QString fileText);
    void undoCommand(CommandState com);
    void removeWordFromFile(QString word, QString fileText);
    bool convert();


    //attributes
    int m_count;
    QString m_memoryPath;
    QList<QString> m_memoryList;
    QList<QTreeWidgetItem *> m_deletedItems;
    QList<int> m_deletedIndexes;//to remember the position of item in the list
    QList<CommandState> m_previousCommands;
    CommandState m_command;
    Babylon *m_babylon;
    QList<QString> m_dictionaryList;
    QMap<QString,QString> m_dict;

    //ui
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
