#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QIcon>
#include <QMessageBox>
#include <QApplication>
#include <QMdiArea>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QMdiArea *mdiArea;

    //2 tool bars
    QToolBar *fileTool;
    QToolBar *editTool;

    //4 menus
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;

    //the items of the file menu
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    //the items of the edit menu
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    //the items of the window menu
    QAction *closeAction;
    QAction *closeAllAction;
    QAction *tileAction;
    QAction *cascadeAction;
    QAction *nextAction;
    QAction *previousAction;
    //the items of the help
    QAction *aboutAction;
    QAction *aboutQtAction;

    void createActions();
    void createMenuBar();
    void createToolBar();

private slots:
    //mainwindow
    void updateActions();

    //file menu
    void newFile();
    void openFile();
    void saveFile();
    void saveAS();
    void exitProgram();
    //edit menu
    void cut();
    void copy();
    void paste();
    //window menu
    void closeFile();
    void closeAll();
    void tile();
    void cascade();
    void nextFile();
    void previousFile();
    //help menu
    void aboutProgram();

};

#endif // MAINWINDOW_H
