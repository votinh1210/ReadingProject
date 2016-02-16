/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionAbout_LR;
    QAction *actionExit;
    QAction *actionSave;
    QAction *actionOpen_LR_file;
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QHBoxLayout *allLayout;
    QTreeWidget *treeWidget;
    QVBoxLayout *rightLayout;
    QLabel *label;
    QVBoxLayout *commandLayout;
    QPushButton *bKnow;
    QPushButton *bRemove;
    QPushButton *bUndo;
    QPushButton *bTranslate;
    QPushButton *bGoogle;
    QPushButton *bPaste;
    QPushButton *bRemoveInFile;
    QPushButton *bSave;
    QPushButton *bLoad;
    QLabel *label_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(657, 517);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionAbout_LR = new QAction(MainWindow);
        actionAbout_LR->setObjectName(QStringLiteral("actionAbout_LR"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionOpen_LR_file = new QAction(MainWindow);
        actionOpen_LR_file->setObjectName(QStringLiteral("actionOpen_LR_file"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setAutoFillBackground(false);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(1, 1, 651, 461));
        allLayout = new QHBoxLayout(layoutWidget);
        allLayout->setSpacing(6);
        allLayout->setContentsMargins(11, 11, 11, 11);
        allLayout->setObjectName(QStringLiteral("allLayout"));
        allLayout->setSizeConstraint(QLayout::SetMaximumSize);
        allLayout->setContentsMargins(0, 0, 0, 0);
        treeWidget = new QTreeWidget(layoutWidget);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        treeWidget->setSortingEnabled(true);

        allLayout->addWidget(treeWidget);

        rightLayout = new QVBoxLayout();
        rightLayout->setSpacing(6);
        rightLayout->setObjectName(QStringLiteral("rightLayout"));
        rightLayout->setSizeConstraint(QLayout::SetMaximumSize);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        rightLayout->addWidget(label);

        commandLayout = new QVBoxLayout();
        commandLayout->setSpacing(6);
        commandLayout->setObjectName(QStringLiteral("commandLayout"));
        commandLayout->setSizeConstraint(QLayout::SetMaximumSize);
        bKnow = new QPushButton(layoutWidget);
        bKnow->setObjectName(QStringLiteral("bKnow"));

        commandLayout->addWidget(bKnow);

        bRemove = new QPushButton(layoutWidget);
        bRemove->setObjectName(QStringLiteral("bRemove"));

        commandLayout->addWidget(bRemove);

        bUndo = new QPushButton(layoutWidget);
        bUndo->setObjectName(QStringLiteral("bUndo"));

        commandLayout->addWidget(bUndo);

        bTranslate = new QPushButton(layoutWidget);
        bTranslate->setObjectName(QStringLiteral("bTranslate"));

        commandLayout->addWidget(bTranslate);

        bGoogle = new QPushButton(layoutWidget);
        bGoogle->setObjectName(QStringLiteral("bGoogle"));

        commandLayout->addWidget(bGoogle);

        bPaste = new QPushButton(layoutWidget);
        bPaste->setObjectName(QStringLiteral("bPaste"));

        commandLayout->addWidget(bPaste);

        bRemoveInFile = new QPushButton(layoutWidget);
        bRemoveInFile->setObjectName(QStringLiteral("bRemoveInFile"));

        commandLayout->addWidget(bRemoveInFile);

        bSave = new QPushButton(layoutWidget);
        bSave->setObjectName(QStringLiteral("bSave"));

        commandLayout->addWidget(bSave);

        bLoad = new QPushButton(layoutWidget);
        bLoad->setObjectName(QStringLiteral("bLoad"));

        commandLayout->addWidget(bLoad);


        rightLayout->addLayout(commandLayout);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        rightLayout->addWidget(label_2);

        rightLayout->setStretch(0, 1);
        rightLayout->setStretch(1, 3);
        rightLayout->setStretch(2, 1);

        allLayout->addLayout(rightLayout);

        allLayout->setStretch(0, 2);
        allLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 657, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionOpen_LR_file);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionExit);
        menuAbout->addAction(actionAbout_LR);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionAbout_LR->setText(QApplication::translate("MainWindow", "About LR", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save to LR file", 0));
        actionOpen_LR_file->setText(QApplication::translate("MainWindow", "Open LR file", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "Translation (pro)", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "Frequency", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Newword", 0));
        label->setText(QApplication::translate("MainWindow", "Please open a reading file to begin", 0));
        bKnow->setText(QApplication::translate("MainWindow", "I know this word (Ctrl+K)", 0));
        bRemove->setText(QApplication::translate("MainWindow", "Remove", 0));
        bUndo->setText(QApplication::translate("MainWindow", "Undo (Ctrl+U)", 0));
        bTranslate->setText(QApplication::translate("MainWindow", "Translate (Ctrl+T)", 0));
        bGoogle->setText(QApplication::translate("MainWindow", "Google (Ctrl+G)", 0));
        bPaste->setText(QApplication::translate("MainWindow", "Paste from Clipboard", 0));
        bRemoveInFile->setText(QApplication::translate("MainWindow", "Remove a word from memory (pro)", 0));
        bSave->setText(QApplication::translate("MainWindow", "Save analyse (pro)", 0));
        bLoad->setText(QApplication::translate("MainWindow", "Load virtual memory (pro)", 0));
        label_2->setText(QApplication::translate("MainWindow", "Load virtual memory to begin", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuAbout->setTitle(QApplication::translate("MainWindow", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
