//
//  window.cpp
//  markdown
//
//  Created by Jackey Chen on 5/27/15.
//
//

#include "window.h"
#include "mdhandler.h"
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QTextEdit>
#include <QGridLayout>
#include <QSizePolicy>
#include <QTextStream>
#include <QFile>
#include <iostream>
#include <QFileDialog>
#include <QDir>
#include <QPrinter>

namespace md {
    Window::Window(QWidget *parent) {
        QFile styleFile(":/style/screen.css");
        styleFile.open(QIODevice::ReadOnly | QIODevice::Text);
        screenStyleFile = new QTextStream(&styleFile);
        
        createMenus();
        createComponents();
        initMdHandler();
    }
    
    Window::~Window() {
        delete screenStyleFile;
    }
    
    void Window::initMdHandler() {
        MdHandler *mdhandler = new MdHandler(mdEditor);
        
        QObject::connect(mdEditor, SIGNAL(textChanged()), mdhandler, SLOT(handleMdChanged()));
        QObject::connect(mdhandler, SIGNAL(mdCompiled(QString)), this, SLOT(handleMdCompiled(QString)));
    }
    
    void Window::createMenus() {
        QAction *action;
        
        // 文件相关菜单
        QMenu *file = new QMenu(this);
        
        action = new QAction(tr("&Open"), this);
        action->setShortcut(QKeySequence::Open);
        file->addAction(action);
        file->addSeparator();
        
        saveAction = new QAction(tr("&Save"), this);
        saveAction->setShortcut(QKeySequence::Save);
        file->addAction(saveAction);
        QObject::connect(saveAction, SIGNAL(triggered()), this, SLOT(saveTriggered()));
        
        htmlAction =new QAction(tr("&Save As HTML"), this);
        QObject::connect(htmlAction, SIGNAL(triggered()), this, SLOT(saveAsHTML()));
        file->addAction(htmlAction);
        
        pdfAction = new QAction(tr("&Save As PDF"), this);
        QObject::connect(pdfAction, SIGNAL(triggered()), this, SLOT(saveAsPDF()));
        file->addAction(pdfAction);
        
        file->addSeparator();
        
        menuBar()->addMenu(file)->setText(tr("&File"));
        
        // 编辑相关菜单
        QMenu *edit = new QMenu(this);
        
        menuBar()->addMenu(edit)->setText(tr("&Edit"));
        
        statusBar();
    }
    
    void Window::createComponents() {
        mdEditor = new QTextEdit(this);
        mdEditor->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);
        mdEditor->setText("");
        
        htmlEditor = new QTextEdit(this);
        htmlEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        QTextDocument *document = new QTextDocument();
        if (screenStyleFile) {
            screenStyleFile->reset();
            screenStyleFile->seek(0);
            QString css = screenStyleFile->readAll();
            document->setDefaultStyleSheet(css);
        }
        else {
            qDebug("Read css failed");
        }
        
        const QString defaultHtml = MdHandler::markdown(mdEditor->toPlainText());
        document->setHtml(defaultHtml);
        
        htmlEditor->setDocument(document);
        
        QGridLayout *mainLayout = new QGridLayout();
        mainLayout->addWidget(mdEditor, 0, 0);
        mainLayout->addWidget(htmlEditor, 0, 1);
        
        QWidget *main = new QWidget();
        main->setLayout(mainLayout);
        setCentralWidget(main);
        setWindowTitle(tr("Markdown Editor From Fumer"));
        
        setMinimumSize(800, 900);
    }
    
    void Window::handleMdCompiled(QString str) {
        str.append("</body></html>");
        str.prepend("<html><body>");
        htmlEditor->setHtml(str);
    }
    
    void Window::saveAsHTML() {
        if (htmlSaveTo.isEmpty()) {
            QString homeDir = QDir::homePath();
            htmlSaveTo = QFileDialog::getSaveFileName(this, tr("Save HTML To"), homeDir.append("/Documents"), tr("Pdf Files (*.html)"));
        }
        
        // 用户选择文件后 存储选择位置
        if (!htmlSaveTo.isEmpty()) {
            QString html = htmlEditor->toHtml();
            QFile saveTo(htmlSaveTo);
            saveTo.open(QIODevice::WriteOnly | QIODevice::Text);
            char *data = html.toUtf8().data();
            saveTo.write(html.toUtf8().data(), strlen(data));
            saveTo.close();
            
            saveType = SAVE_HTML;
        }
    }
    
    void Window::saveAsPDF() {
        if (pdfSaveTo.isEmpty()) {
            QString homeDir = QDir::homePath();
            pdfSaveTo = QFileDialog::getSaveFileName(this, tr("Save PDF To"), homeDir.append("/Documents"), tr("HTML Files (*.pdf)"));
        }
        
        if (!pdfSaveTo.isEmpty()) {
            QString html = htmlEditor->toHtml();
            QPrinter printer(QPrinter::HighResolution);
            printer.setPageSize(QPrinter::A4);
            printer.setOutputFormat(QPrinter::PdfFormat);
            
            printer.setOutputFileName(pdfSaveTo);
            
            QTextDocument *document = new QTextDocument();
            document->setHtml(html);
            
            document->print(&printer);
            delete document;
            
            saveType = SAVE_PDF;
        }
    }
    
    void Window::saveTriggered() {
        switch (saveType) {
            case SAVE_HTML:
                if (!htmlSaveTo.isEmpty()) {
                    emit htmlAction->trigger();
                }
                break;
            case SAVE_PDF:
                if (!pdfSaveTo.isEmpty()) {
                    emit pdfAction->trigger();
                }
                break;
        }
        QString homeDir = QDir::homePath();
        if (mdSaveTo.isEmpty()) {
            mdSaveTo = QFileDialog::getSaveFileName(this,
                                                    tr("Save Markdown File To"),
                                                    homeDir.append("/Documents"),
                                                    tr("Markdown files (*.md)"));
        }
        
        QFile saveTo(mdSaveTo);
        saveTo.open(QIODevice::WriteOnly | QIODevice::Text);
        char *data = mdEditor->toPlainText().toUtf8().data();
        saveTo.write(data, strlen(data));
        saveTo.close();
    }
}

