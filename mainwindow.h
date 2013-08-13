#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QIcon>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //4 menus
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;

    //the items of the file menu
    QAction *newFile;
    QAction *openFile;
    QAction *saveFile;
    QAction *saveAs;
    QAction *exitProgram;
    //the items of the edit menu
    QAction *cut;
    QAction *copy;
    QAction *paste;
    //the items of the window menu
    QAction *closeFile;
    QAction *closeAll;
    QAction *tile;
    QAction *cascade;
    QAction *nextFile;
    QAction *previousFile;
    //the items of the help
    QAction *aboutProgram;
    QAction *aboutQt;

    void createActions();
    void createMenuBar();
};

#endif // MAINWINDOW_H
