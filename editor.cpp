#include <QFileDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QApplication>

#include "editor.h"

Editor::Editor(QWidget *parent)
    : QTextEdit(parent)
{
    action = new QAction(this);
    action->setCheckable(true);
    connect(action, SIGNAL(triggered()), this, SLOT(show()));
    connect(action, SIGNAL(triggered()), this, SLOT(setFocus()));

    isUntitled = true;

    connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));

    setWindowIcon(QPixmap(":/images/icon.png"));
    setWindowTitle("[*]");;
    setAttribute(Qt::WA_DeleteOnClose);
}

void Editor::newFile()
{
    static int documentNumber = 1;
    curFile = tr("document%1.txt").arg(documentNumber);
    setWindowTitle(curFile + "[*]");
    action->setText(curFile);
    isUntitled = true;
    ++documentNumber;
}

Editor *Editor::open(QWidget *parent)
{
    QString fileName = QFileDialog::getOpenFileName(parent, tr("Open"), ".");

    if(fileName.isEmpty())
        return 0;

    return openFile(fileName, parent);
}

Editor *Editor::openFile(const QString &fileName, QWidget *parent)
{
    Editor *editor = new Editor(parent);

    if(editor->readFile(fileName))
    {
        editor->setCurrentFile(fileName);
        return editor;
    }
    else
    {
        delete editor;
        return 0;
    }
}

bool Editor::save()
{
    if(isUntitled)
        return saveAs();
    else
        return saveFile(curFile);
}

bool Editor::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), curFile);

    if(fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void Editor::closeEvent(QCloseEvent *event)
{
    if(oktocontinue())
        event->accept();
    else
        event->ignore();
}

void Editor::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    isUntitled = false;
    action->setText(strippedName(curFile));
    document()->setModified(false);
    setWindowTitle(strippedName(curFile) + "[*]");
    setWindowModified(false);
}

QSize Editor::sizeHint() const
{
    return QSize(72 * fontMetrics().width('x'), 25 * fontMetrics().lineSpacing());
}

void Editor::documentWasModified()
{
    setWindowModified(true);
}

bool Editor::oktocontinue()
{
    if(document()->isModified())
    {
        int r = QMessageBox::warning(this, tr("MDIEditor"), tr("file %1 has been modified, \n"
                                 "Do you want to save your changes?").arg(curFile),
                             QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(QMessageBox::Yes == r)
            return save();
        else if (QMessageBox::No == r)
            return true;
        else
            return false;
    }

    return true;
}

bool Editor::saveFile(const QString &fileName)
{
    if(writeFile(fileName))
    {
        setCurrentFile(fileName);
        return true;
    }
    else
        return false;
}

bool Editor::readFile(const QString &fileName)
{
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("Mdi editor"),
                             tr("can't open file %1.\n%2").arg(fileName).arg(file.errorString()));
        return false;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
    return true;
}

bool Editor::writeFile(const QString &fileName)
{
    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("Mdi editor"),
                             tr("Can't write file %1.\n%2").arg(fileName).arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << toPlainText() << endl;//there must be some wrong
    QApplication::overrideCursor();
    return true;
}

QString Editor::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}
