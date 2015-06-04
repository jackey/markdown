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

namespace md {
    Window::Window(QWidget *parent) {
        QFile file(":/style/screen.css");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        screenStyleFile = new QTextStream(&file);
        
        std::cout << file.size() << std::endl;
        
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
        action->setShortcut(tr("CTRL+O"));
        file->addAction(action);
        file->addSeparator();
        
        action = new QAction(tr("&Save"), this);
        action->setShortcut(tr("CTRL+S"));
        file->addAction(action);
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
        mdEditor->setText("#happy in markdown");
        
        htmlEditor = new QTextEdit(this);
        htmlEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        QTextDocument *document = new QTextDocument();
        if (screenStyleFile) {
            screenStyleFile->reset();
            screenStyleFile->seek(0);
            QString css = screenStyleFile->readAll();
            qDebug(css.toUtf8().data());
            document->setDefaultStyleSheet(css);
        }
        else {
            qDebug("Read css failed");
        }

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
        qDebug(str.toUtf8().data());
        htmlEditor->setHtml(str);
    }
}

