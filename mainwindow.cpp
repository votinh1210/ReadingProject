#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QSettings>
#include <QDesktopServices>
#include <QTextStream>
#include <QMessageBox>
#include <QClipboard>
//#include <QxtGlobalShortcut>
#include "languagereadingfile.h"


/*
 * Constructor
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("LR - Love Reading"));
    m_activeDict = 0;

    gdAskMessage = RegisterWindowMessage( L"MESSAGE" );
	( static_cast< QHotkeyApplication * >( qApp ) )->setMainWindow( this );
    installHotKeys();
    m_babylon = NULL;
    QDirIterator it(QDir::currentPath(), QStringList() << "*.bgl", QDir::Files);
    while (it.hasNext()){
        if (m_babylon){
            delete m_babylon;
            m_babylon = NULL;
        }
        QString filename = it.next();
        readMemoryFile(filename.left(filename.lastIndexOf(".")) + QString(".minh"));//read memory
        m_babylon = new Babylon(filename.toUtf8().constData());//update babylon filename
        convert();//read babylon file
        ui->comboBox->addItem(m_dicts.last().name);
        qDebug()<<filename.left(filename.lastIndexOf(".")) + QString(".minh");
    }
}

/*
 * Destructor
*/
MainWindow::~MainWindow()
{
    if (m_babylon){
        delete m_babylon;
        m_babylon = NULL;
    }
    delete ui;
}


bool MainWindow::convert()
{
    if( !m_babylon->open() )
    {
        printf( "Error openning %s\n", m_babylon->filename().c_str() );
        return false;
    }
    std::string sourceCharset, targetCharset;
    //m_babylon->read();
    if( !m_babylon->read(sourceCharset, targetCharset) )
    {
        printf( "Error reading %s\n", m_babylon->filename().c_str() );
        return false;
    }

    Dictionary dict;
    dict.name = QString(m_babylon->title().c_str());
    dict.filename = QString(m_babylon->filename().c_str());

    bgl_entry entry;
    entry = m_babylon->readEntry();

    qDebug()<<m_babylon->sourceLang();
    QMap<QString,QString> wordsList;
    while( !entry.headword.empty() )
    {
        //m_builder->addHeadword( entry.headword.c_str(), entry.definition.c_str(), entry.alternates );

        //dictionaryList.append(QString(entry.headword.c_str()));
        wordsList[QString(entry.headword.c_str())] = QString(entry.definition.c_str());
        entry = m_babylon->readEntry();
        //count++;
        //if (count > 10) break;
    }
    m_babylon->close();
    dict.dict = wordsList;
    m_dicts.append(dict);

    return true;
}

/*
 * Menu action triggered
*/
void MainWindow::on_actionOpen_triggered()
{
    QString fileText = QFileDialog::getOpenFileName(this, "Open E-book", "E:/Documents", "Text File (*.txt *.srt *.lrt)");
    if (fileText.isEmpty()) return;
    ui->treeWidget->clear();
    if (fileText.split(".").last()=="lrt"){//get extension
        LanguageReadingFile file(fileText);
        QMap<QString,int> map = file.read();

        for (QMap<QString,int>::iterator it=map.begin(); it!=map.end(); ++it){
            if (m_memoryList[m_activeDict].indexOf(it.key())>=0) continue;

            QTreeWidgetItem *item = new QTreeWidgetItem;
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            item->setText(0,it.key());
            item->setData(1, Qt::DisplayRole, it.value());
            ui->treeWidget->addTopLevelItem(item);
        }
        updateNumbers();
    }
    else readFile(fileText);
}

void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionAbout_LR_triggered()
{
    QMessageBox::about(this, tr("About"), tr("LR - Love Reading is a part of Language Reading project.\n"
                                             "Created by DINH Vu Minh.\n"
                                             "For any feedback and suggestion, please contact minh.yuip@gmail.com."));
}

/*
 * Read file with path in parameter
*/
void MainWindow::readFile(QString fileText){
    QFile file(fileText);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        QList<QString> dictionaryList = m_dicts[m_activeDict].dict.keys();
        while(!in.atEnd()) {
            QString line = in.readLine();
            line.replace("\'"," ");
            line.remove(QRegExp(QString::fromUtf8("[0123456789`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]")));
            QStringList  fields = line.split(" ");
            for (int i=0;i<fields.length();++i){
                if (fields[i].length()<3) continue;
                fields[i] = fields[i].toLower();
                if (m_memoryList[m_activeDict].indexOf(fields[i])>=0) continue;
                if (dictionaryList.indexOf(fields[i])<0) continue;
                QTreeWidgetItem* item;
                item = new QTreeWidgetItem();
                item->setFlags(item->flags() | Qt::ItemIsEditable);
                item->setText(0, fields[i]);
                item->setData(1,Qt::DisplayRole,1);
                QList<QTreeWidgetItem *> items = ui->treeWidget->findItems(fields[i],Qt::MatchFixedString);
                if (items.length()>0){
                    int f = items[0]->data(1,Qt::DisplayRole).toInt();
                    int index = ui->treeWidget->indexOfTopLevelItem(items[0]);
                    item->setData(1, Qt::DisplayRole,++f);
                    ui->treeWidget->takeTopLevelItem(index);
                }
                ui->treeWidget->addTopLevelItem(item);
            }
            if (ui->treeWidget->topLevelItemCount()>=100) break;
        }
        updateNumbers();
    }
    file.close();
}

void MainWindow::on_bKnow_clicked()
{
    QString filename = m_dicts[m_activeDict].filename;
    QFile file(filename.left(filename.lastIndexOf("."))+".minh");
    if (file.open(QIODevice::Append))
    {
        QTextStream out(&file);   // we will serialize the data into the file
        QList<QTreeWidgetItem *> items = ui->treeWidget->selectedItems();
        for (int i=0;i<items.length();++i){
            if (items[i]->isDisabled()) continue;
            out << items[i]->text(0) << "\n";
            m_memoryList[m_activeDict].push_back(items[i]->text(0));
            int index = ui->treeWidget->indexOfTopLevelItem(items[i]);
            m_deletedItems.push_back(items[i]);
            m_deletedIndexes.push_back(index);
            m_previousCommands.push_back(I_KNOW);
            ui->treeWidget->takeTopLevelItem(index);
            updateNumbers();
        }
    }
    file.close();
}

/*this function will not be used at the moment*/
void MainWindow::on_bLoad_clicked()
{
    m_memoryPath = QFileDialog::getOpenFileName(this, "Load Memory", "E:/Documents", "Reading file (*.txt *.srt *.lrt)");
    if (m_memoryPath.isEmpty()) return;//TODO: message box is shown
    readMemoryFile(m_memoryPath);
    updateNumbers();
}

void MainWindow::readMemoryFile(QString fileText){
    QFile file(fileText);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        QList<QString> list;
        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList  fields = line.split("\n");
            if (fields[0]!="")
                list.append(fields[0]);
        }
        m_memoryList.append(list);
    }
    file.close();
}

void MainWindow::readDictionary(QString fileText){
    QFile file(fileText);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        Dictionary dict;
        dict.name = in.readLine();
        in.readLine();//read version

        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList  fields = line.split(" ");
            dict.dict[fields[0]] = line.remove(fields[0]+" ");
        }
        m_dicts.append(dict);
        ui->comboBox->addItem(m_dicts.last().name);
    }
    file.close();
}

void MainWindow::on_bTranslate_clicked()
{
    if (ui->treeWidget->selectedItems().length()==0) return;
    QString link = QString("https://translate.google.com/#fr/vi/")+ui->treeWidget->selectedItems()[0]->text(0);
    QUrl url(link);
    QDesktopServices::openUrl(url);
}

void MainWindow::on_bUndo_clicked()
{
    if (m_previousCommands.length()==0) return;
    CommandState command = m_previousCommands.last();
    if (command==NOTHING) return;
    undoCommand(command);
    m_previousCommands.removeLast();
    m_deletedIndexes.removeLast();
    m_deletedItems.removeLast();
}

void MainWindow::undoCommand(CommandState com){
    int index = m_deletedIndexes.last();
    QTreeWidgetItem *item = m_deletedItems.last();
    if (com==I_KNOW){
        ui->treeWidget->insertTopLevelItem(index, item);
        m_memoryList[m_activeDict].removeLast();
        updateNumbers();

        QString filename = m_dicts[m_activeDict].filename;

        QFile file(filename.left(filename.lastIndexOf("."))+".minh");
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&file);   // we will serialize the data into the file
            for (int i=0;i<m_memoryList[m_activeDict].length();++i){
                out << m_memoryList[m_activeDict][i] << "\n";
            }
        }
        file.close();
    }
    else if (com==REMOVE){
        ui->treeWidget->insertTopLevelItem(index, item);
        updateNumbers();
    }
}

void MainWindow::on_bRemove_clicked()
{
    QList<QTreeWidgetItem *> items = ui->treeWidget->selectedItems();
    for (int i=0;i<items.length();++i){
        int index = ui->treeWidget->indexOfTopLevelItem(items[i]);
        m_deletedItems.push_back(items[i]);
        m_deletedIndexes.push_back(index);
        m_previousCommands.push_back(REMOVE);
        ui->treeWidget->takeTopLevelItem(index);
        updateNumbers();
    }
}
/*not use at the moment*/
void MainWindow::removeWordFromFile(QString word, QString fileText){
    QFile file(fileText);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString s;
        QTextStream in(&file);
        while(!in.atEnd()) {
            QString line = in.readLine();
            if (line!=word)
                s.append(line+"\n");
        }
        file.resize(0);
        in<<s;
    }
    file.close();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Escape: {
            QList<QTreeWidgetItem *> items = ui->treeWidget->selectedItems();
            for (int i=0;i<items.length();++i){
                if (items[i]->text(0).contains(" ")){
                    QStringList sl = items[i]->text(0).split(" ");
                    //todo: split to 2 line
                }
            }
            break;
        }
        case Qt::Key_T: on_bTranslate_clicked(); break;
        case Qt::Key_Z: on_bUndo_clicked(); break;
        case Qt::Key_Delete: on_bRemove_clicked(); break;
        case Qt::Key_X: on_bKnow_clicked(); break;
    }
}
/*this function used for testing purpose*/
void MainWindow::on_bRemoveInFile_clicked()
{
    removeWordFromFile("enghien", m_memoryPath);
}

void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if (column == 0){
        ui->textBrowser->setHtml(m_dicts[m_activeDict].dict[item->text(0)]);
        item->setDisabled(true);
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString fileText = QFileDialog::getSaveFileName(this, "Save", "E:/Documents", "Language Reading Text (*.lrt)");
    if (fileText.isEmpty()) return;
    LanguageReadingFile file(fileText);
    file.write(ui->treeWidget);
}

void MainWindow::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    if (item->text(0).contains(" ") && column==0){
        int index = ui->treeWidget->indexOfTopLevelItem(item);
        ui->treeWidget->takeTopLevelItem(index);
        QStringList fields = item->text(0).split(" ");
        for (int i=0; i<fields.length(); ++i){
            QTreeWidgetItem *it = new QTreeWidgetItem;
            it->setFlags(it->flags() | Qt::ItemIsEditable);
            it->setText(0,fields[i]);
            it->setData(1, Qt::DisplayRole, item->data(1,Qt::DisplayRole));
            ui->treeWidget->insertTopLevelItem(index, it);
        }
        updateNumbers();
    }
}

void MainWindow::on_bGoogle_clicked()
{
    if (ui->treeWidget->selectedItems().length()==0) return;
    QString link = QString("https://www.google.fr/#q=")+ui->treeWidget->selectedItems()[0]->text(0);
    QUrl url(link);
    QDesktopServices::openUrl(url);
}

void MainWindow::on_bPaste_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString text = clipboard->text();
    ui->treeWidget->clear();
    text.replace("\'"," ");
    text.replace("\’"," ");
    text.replace("\n"," ");
    text.remove("…");
    text.remove(QRegExp(QString::fromUtf8("[0123456789`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]")));
    QStringList  fields = text.split(" ");
    QList<QString> dictionaryList = m_dicts[m_activeDict].dict.keys();
    for (int i=0;i<fields.length();++i){
        if (fields[i].length()<3) continue;
        fields[i] = fields[i].toLower();
        if (m_memoryList[m_activeDict].indexOf(fields[i])>=0) continue;
        if (dictionaryList.indexOf(fields[i])<0) continue;
        QTreeWidgetItem* item;
        item = new QTreeWidgetItem();
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        item->setText(0, fields[i]);
        item->setData(1,Qt::DisplayRole,1);
        QList<QTreeWidgetItem *> items = ui->treeWidget->findItems(fields[i],Qt::MatchFixedString);
        if (items.length()>0){
            int f = items[0]->data(1,Qt::DisplayRole).toInt();
            int index = ui->treeWidget->indexOfTopLevelItem(items[0]);
            item->setData(1, Qt::DisplayRole,++f);
            ui->treeWidget->takeTopLevelItem(index);

        }

        ui->treeWidget->addTopLevelItem(item);

    }
    updateNumbers();
}

void MainWindow::on_lineEdit_returnPressed()
{
    bool found=false;
    ui->textBrowser->clear();
    for (int i=0;i<m_dicts.length();++i){
        QString lookup = m_dicts[i].dict[ui->lineEdit->text()];
        if (lookup != ""){



            ui->textBrowser->insertHtml(lookup);
            found = true;
        }
    }

    if (!found){
        QMessageBox::StandardButton answer = QMessageBox::question(this, tr("Google it?"),"Word not found, google it?");
        if (answer == QMessageBox::Yes){
            QString link = QString("https://www.google.com/#q=")+ui->lineEdit->text();
            QUrl url(link);
            QDesktopServices::openUrl(url);
        }
    }
    else{
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        item->setText(0,ui->lineEdit->text());
        item->setData(1, Qt::DisplayRole, 1);
        ui->treeWidget->addTopLevelItem(item);
    }
}

void MainWindow::on_actionAdd_a_dictionary_triggered()
{
    QString fileText = QFileDialog::getOpenFileName(this, "Open", "E:/Documents", "Text File (*.*)");
    if (fileText.isEmpty()) return;
    m_babylon = new Babylon(fileText.toUtf8().constData());
    convert();
    ui->comboBox->addItem(m_dicts.last().name);
}

void MainWindow::installHotKeys()
{
    hotkeyWrapper.reset(); // Remove the old one

    try
    {
        hotkeyWrapper = new HotkeyWrapper( this );
    }
    catch( HotkeyWrapper::exInit & )
    {
        QMessageBox::critical( this, "GoldenDict",
                               tr( "Failed to initialize hotkeys monitoring mechanism.<br>"
                                   "Make sure your XServer has RECORD extension turned on." ) );

        return;
    }

    hotkeyWrapper->setGlobalKey( Qt::Key_C,
                                 Qt::Key_C,
                                 Qt::ControlModifier,
                                 0 );

    hotkeyWrapper->setGlobalKey( Qt::Key_C,
                                 Qt::Key_C,
                                 Qt::ControlModifier,
                                 1 );


    connect( hotkeyWrapper.get(), SIGNAL( hotkeyActivated( int ) ),
             this, SLOT( hotKeyActivated( int ) ) );

}

void MainWindow::hotKeyActivated( int hk )
{
    //QString text = QApplication::clipboard()->text();
    this->showNormal();
    this->raise();
    this->activateWindow();
	on_bPaste_clicked();
    //QMessageBox::question(this, tr("Google it?"),"Word not found, google it? ");

}

bool MainWindow::handleGDMessage( MSG * message, long * result )
{
  if( message->message != gdAskMessage )
    return false;
  *result = 0;

  if( !isGoldenDictWindow( message->hwnd ) )
    return true;
	/*
  ArticleView * view = getCurrentArticleView();
  if( !view )
    return true;

  LPGDDataStruct lpdata = ( LPGDDataStruct ) message->lParam;

  QString str = view->wordAtPoint( lpdata->Pt.x, lpdata->Pt.y );

  memset( lpdata->cwData, 0, lpdata->dwMaxLength * sizeof( WCHAR ) );
  str.truncate( lpdata->dwMaxLength - 1 );
  str.toWCharArray( lpdata->cwData );
*/
  *result = 1;
  return true;
}

bool MainWindow::isGoldenDictWindow( HWND hwnd )
{
  return hwnd == (HWND)winId() || hwnd == (HWND)ui->centralWidget->winId();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    m_activeDict = index;
    //todo: function update
    updateNumbers();
}

void MainWindow::updateNumbers(){
    if (m_activeDict<m_memoryList.length())
        ui->label_2->setText(QString::number(ui->treeWidget->topLevelItemCount()) +
                             "/" +
                             QString::number(m_memoryList[m_activeDict].length()));//update word number
}
