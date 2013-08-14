#include <QTimer>
#include <QApplication>
#include <QCloseEvent>
#include <QStatusBar>
#include <QMdiSubWindow>
#include <QLabel>

#include "mainwindow.h"
#include "editor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea;
    setCentralWidget(mdiArea);
    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(updateActions()));//update the actions to the activated open file

    createActions();
    createMenuBar();
    createToolBar();

    setWindowIcon(QIcon(":/images/icon.png"));
    setWindowTitle(tr("MDI editor"));
    QTimer::singleShot(0, this, SLOT(loadFiles()));
}

void MainWindow::updateActions()
{
    bool hasEditor = (activeEditor() != 0);
    bool hasSelection = activeEditor() && activeEditor()->textCursor().hasSelection();

    saveAction->setEnabled(hasEditor);
    saveAsAction->setEnabled(hasEditor);
    cutAction->setEnabled(hasSelection);
    copyAction->setEnabled(hasSelection);
    pasteAction->setEnabled(hasEditor);
    closeAction->setEnabled(hasEditor);
    closeAllAction->setEnabled(hasEditor);
    tileAction->setEnabled(hasEditor);
    cascadeAction->setEnabled(hasEditor);
    nextAction->setEnabled(hasEditor);
    previousAction->setEnabled(hasEditor);
    separaAction->setEnabled(hasEditor);

    if(activeEditor())
        activeEditor()->windowMenuAction()->setChecked(true);
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows();
    if(!mdiArea->subWindowList().isEmpty())
        event->ignore();
    else
        event->accept();
}

void MainWindow::loadFiles()
{
    QStringList args = QApplication::arguments();
    args.removeFirst();
    if(!args.isEmpty())
    {
        foreach (QString arg, args)
            openFile(arg);
        mdiArea->cascadeSubWindows();
    }
    else
        newFile();

    mdiArea->activateNextSubWindow();
}

void MainWindow::openFile(const QString &fileName)
{
    Editor *editor = Editor::openFile(fileName, this);
    if(editor)
        addEditor(editor);
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

    menuBar()->addSeparator();

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

void MainWindow::createStatusBar()
{
    QLabel *readyLabel = new QLabel(tr(" Ready"));
    statusBar()->addWidget(readyLabel, 1);
}

void MainWindow::createActions()
{
    //file menu
    newAction = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAction->setShortcut(QKeySequence::New);
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    openAction = new QAction(QIcon(":/images/open.png"), tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    saveAction = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));
    saveAsAction = new QAction(tr("Save &As"), this);
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAS()));
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

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
    connect(closeAction, SIGNAL(triggered()), mdiArea, SLOT(closeActiveSubWindow()));
    closeAllAction = new QAction(tr("Close &All"), this);
    connect(closeAllAction, SIGNAL(triggered()), this, SLOT(close()));
    tileAction = new QAction(tr("&Tile"), this);
    connect(tileAction, SIGNAL(triggered()), mdiArea, SLOT(tileSubWindows()));
    cascadeAction = new QAction(tr("&Cascade"), this);
    connect(cascadeAction, SIGNAL(triggered()), mdiArea, SLOT(cascadeSubWindows()));
    nextAction = new QAction(tr("Ne&xt"), this);
    nextAction->setShortcut(QKeySequence::NextChild);
    connect(nextAction, SIGNAL(triggered()), mdiArea, SLOT(activateNextSubWindow()));
    previousAction = new QAction(tr("Pre&vious"), this);
    previousAction->setShortcut(QKeySequence::PreviousChild);
    connect(previousAction, SIGNAL(triggered()), mdiArea, SLOT(activatePreviousSubWindow()));

    separaAction = new QAction(this);
    separaAction->setSeparator(true);

    //help menu
    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutProgram()));
    aboutQtAction = new QAction(tr("About &Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    windowActionGroup = new QActionGroup(this);
}

void MainWindow::addEditor(Editor *editor)
{
    connect(editor, SIGNAL(copyAvailable(bool)), cutAction, SLOT(setEnabled(bool)));
    connect(editor, SIGNAL(copyAvailable(bool)), copyAction, SLOT(setEnabled(bool)));

    QMdiSubWindow *subWindow = mdiArea->addSubWindow(editor);
    windowMenu->addAction(editor->windowMenuAction());
    windowActionGroup->addAction(editor->windowMenuAction());
    subWindow->show();
}

Editor *MainWindow::activeEditor()
{
    QMdiSubWindow *subWindow = mdiArea->activeSubWindow();
    if(subWindow)
        return qobject_cast<Editor *>(subWindow->widget());
    return 0;
}

//the following functions are the slot of the actions
void MainWindow::newFile()
{
    Editor *editor = new Editor;
    editor->newFile();
    addEditor(editor);
}

void MainWindow::open()
{
    Editor *editor = Editor::open(this);
    if(editor)
        addEditor(editor);
}

void MainWindow::saveFile()
{
    if(activeEditor())
        activeEditor()->save();
}

void MainWindow::saveAS()
{
    if(activeEditor())
        activeEditor()->saveAs();
}

void MainWindow::cut()
{
    if(activeEditor())
        activeEditor()->cut();
}

void MainWindow::copy()
{
    if(activeEditor())
        activeEditor()->copy();
}

void MainWindow::paste()
{
    if(activeEditor())
        activeEditor()->paste();
}

void MainWindow::aboutProgram()
{
    QMessageBox::about(this, tr("About Editor"),
                       tr("<h2>Editor 0.1</h2>"
                          "Volatile_xian; 2013.8"));
}
