#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenuBar();
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::createMenuBar()
{
    //file menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newFile);
    fileMenu->addAction(openFile);
    fileMenu->addAction(saveFile);
    fileMenu->addAction(saveAs);
    fileMenu->addSeparator();
    fileMenu->addAction(exitProgram);

    //edit menu
    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cut);
    editMenu->addAction(copy);
    editMenu->addAction(paste);

    //window menu
    windowMenu = menuBar()->addMenu(tr("&Window"));
    windowMenu->addAction(closeFile);
    windowMenu->addAction(closeAll);
    windowMenu->addSeparator();
    windowMenu->addAction(tile);
    windowMenu->addAction(cascade);
    windowMenu->addSeparator();
    windowMenu->addAction(nextFile);
    windowMenu->addAction(previousFile);

    //help menu
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutProgram);
    helpMenu->addAction(aboutQt);
}

void MainWindow::createActions()
{
    //file menu
    newFile = new QAction(tr("&New"), this);
    openFile = new QAction(tr("&Open"), this);
    saveFile = new QAction(tr("&Save"), this);
    saveAs = new QAction(tr("Save &As"), this);
    exitProgram = new QAction(tr("E&xit"), this);

    //edit menu
    cut = new QAction(tr("Cu&t"), this);
    copy = new QAction(tr("&Copy"), this);
    paste = new QAction(tr("&Paste"), this);

    //window menu
    closeFile = new QAction(tr("Cl&ose"), this);
    closeAll = new QAction(tr("Close &All"), this);
    tile = new QAction(tr("&Tile"), this);
    cascade = new QAction(tr("&Cascade"), this);
    nextFile = new QAction(tr("Ne&xt"), this);
    previousFile = new QAction(tr("Pre&vious"), this);

    //help menu
    aboutProgram = new QAction(tr("&About"), this);
    aboutQt = new QAction(tr("About &Qt"), this);
}
