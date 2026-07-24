#include "gui/mainwindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextEdit>
#include <QCloseEvent>

#include <core/document.h>

gui::MainWindow::MainWindow(core::Document* document, QWidget* parent) 
    : QMainWindow(parent),m_document(document),m_textEdit(new QTextEdit(this))
{
    setCentralWidget(m_textEdit);
    createMenuBar();
    updateEditor();
    updateWindowTitle();
    resize(800,600);

    connect(m_textEdit, &QTextEdit::textChanged, this, &MainWindow::onTextChanged);
}

gui::MainWindow::~MainWindow() = default;

void gui::MainWindow::createMenuBar()
{
    auto* fileMenu = menuBar()->addMenu(tr("&File"));

    fileMenu->addAction(tr("&New"), QKeySequence::New, this, &MainWindow::newDocument);
    fileMenu->addAction(tr("&Open..."), QKeySequence::Open, this, &MainWindow::openDocument);
    fileMenu->addAction(tr("&Save"), QKeySequence::Save, this, &MainWindow::saveDocument);
    fileMenu->addAction(tr("Save &As..."), QKeySequence::SaveAs, this, &MainWindow::saveDocumentAs);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("E&xit"), QKeySequence::Quit, this, &MainWindow::exitApp);
}

void gui::MainWindow::newDocument()
{   
    if(maybeSave())
    {
        m_document->setText("");
        m_document->setFileName("");
        m_document->setModified(false);
        updateEditor();
        updateWindowTitle();
    }
}

void gui::MainWindow::openDocument()
{
    if(!maybeSave()) return;

    const QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));
    if(fileName.isEmpty()) return;

    if(m_document->load(fileName.toStdString()))
    {
        updateEditor();
        updateWindowTitle();
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("Could not open file %1").arg(fileName));
    }
}

void gui::MainWindow::saveDocument()
{
    const std::string currentName = m_document->fileName();

    if(currentName.empty())
    {
        saveDocumentAs();
        return;
    }

    if(m_document->save(currentName))
    {
        updateWindowTitle();
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("Could not save file"));
    }
}

void gui::MainWindow::saveDocumentAs()
{
    const QString fileName = QFileDialog::getSaveFileName(this, tr("Save File As"));
    if(fileName.isEmpty()) return;

    if(m_document->saveAs(fileName.toStdString()))
    {
        updateWindowTitle();
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("Could not save file"));
    }
}

void gui::MainWindow::exitApp()
{
    close();
}

void gui::MainWindow::onTextChanged()
{
    const QString currentText = m_textEdit->toPlainText();
    if(currentText != QString::fromStdString(m_document->text()))
    {
        m_document->setText(currentText.toStdString());
        m_document->setModified(true);
        updateWindowTitle();
    }
}

void gui::MainWindow::closeEvent(QCloseEvent* event)
{
    if(maybeSave())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

bool gui::MainWindow::maybeSave()
{
    if(!m_document->isModified()) return true;

    const QMessageBox::StandardButton ret = QMessageBox::warning(
        this,
        tr("Unsaved Changes"),
        tr("The document has unsaved changes. Do you want to save them?"),
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel
    );

    switch(ret)
    {
        case QMessageBox::Save:
            saveDocument();
            return !m_document->isModified();

        case QMessageBox::Discard:
            return true;

        default:
            return false;
    }
}

void gui::MainWindow::updateEditor()
{
    m_textEdit->setPlainText(QString::fromStdString(m_document->text()));
}

void gui::MainWindow::updateWindowTitle()
{
    QString title = tr("Text Editor");
    const std::string fname = m_document->fileName();
    if(!fname.empty())
    {
        title = QString::fromStdString(fname) + "-" + title;
    }

    if(m_document->isModified())
    {
        title += " *";
    }
    setWindowTitle(title);
}














