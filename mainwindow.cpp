#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/images/icon.png"));
    setWindowTitle(tr("MDI editor"));
    createActions();
    createMenuBar();
    createToolBar();

    mdiArea = new QMdiArea;
    setCentralWidget(mdiArea);
    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(updateActions()));//update the actions to the activated open file

}

MainWindow::~MainWindow()
{
    
}

void MainWindow::createMenuBar()
{
    //file menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    //edit menu
    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    //window menu
    windowMenu = menuBar()->addMenu(tr("&Window"));
    windowMenu->addAction(closeAction);
    windowMenu->addAction(closeAllAction);
    windowMenu->addSeparator();
    windowMenu->addAction(tileAction);
    windowMenu->addAction(cascadeAction);
    windowMenu->addSeparator();
    windowMenu->addAction(nextAction);
    windowMenu->addAction(previousAction);

    //help menu
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBar()
{
    //file boolbar
    fileTool = addToolBar(tr("&File"));
    fileTool->addAction(newAction);
    fileTool->addAction(openAction);
    fileTool->addAction(saveAction);

    //edit boolbar
    editTool = addToolBar(tr("&Edit"));
    editTool->addAction(cutAction);
    editTool->addAction(copyAction);
    editTool->addAction(pasteAction);
}

void MainWindow::createActions()
{
    //file menu
    newAction = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAction->setShortcut(QKeySequence::New);
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    openAction = new QAction(QIcon(":/images/open.png"), tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    saveAction = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));
    saveAsAction = new QAction(tr("Save &As"), this);
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAS()));
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exitProgram()));

    //edit menu
    cutAction = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    cutAction->setShortcut(QKeySequence::Cut);
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));
    copyAction = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));
    pasteAction = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

    //window menu
    closeAction = new QAction(tr("Cl&ose"), this);
    closeAction->setShortcut(QKeySequence::Close);
    connect(closeAction, SIGNAL(triggered()), this, SLOT(closeFile()));
    closeAllAction = new QAction(tr("Close &All"), this);
    connect(closeAllAction, SIGNAL(triggered()), this, SLOT(closeAll()));
    tileAction = new QAction(tr("&Tile"), this);
    connect(tileAction, SIGNAL(triggered()), this, SLOT(tile()));
    cascadeAction = new QAction(tr("&Cascade"), this);
    connect(cascadeAction, SIGNAL(triggered()), this, SLOT(cascade()));
    nextAction = new QAction(tr("Ne&xt"), this);
    nextAction->setShortcut(QKeySequence::NextChild);
    connect(nextAction, SIGNAL(triggered()), this, SLOT(nextFile()));
    previousAction = new QAction(tr("Pre&vious"), this);
    previousAction->setShortcut(QKeySequence::PreviousChild);
    connect(previousAction, SIGNAL(triggered()), this, SLOT(previousFile()));

    //help menu
    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutProgram()));
    aboutQtAction = new QAction(tr("About &Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::updateActions()
{

}

//the following functions are the slot of the actions
void MainWindow::newFile()
{

}

void MainWindow::openFile()
{

}

void MainWindow::saveFile()
{

}

void MainWindow::saveAS()
{

}

void MainWindow::exitProgram()
{

}

void MainWindow::cut()
{

}

void MainWindow::copy()
{

}

void MainWindow::paste()
{

}

void MainWindow::closeFile()
{

}

void MainWindow::closeAll()
{

}

void MainWindow::tile()
{

}

void MainWindow::cascade()
{

}

void MainWindow::nextFile()
{

}

void MainWindow::previousFile()
{

}

void MainWindow::aboutProgram()
{
    QMessageBox::about(this, tr("About Editor"),
                       tr("<h2>Editor 0.1</h2>"
                          "Volatile_xian; 2013.8"));
}
