//
//  window.cpp
//  markdown
//
//  Created by Jackey Chen on 5/27/15.
//
//

#include "window.h"
#include "mdconvert.h"
#include "mdhandler.h"
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QTextEdit>
#include <QGridLayout>
#include <QSizePolicy>

namespace md {
    Window::Window(QWidget *parent) {
        createMenus();
        createComponents();
        
        initMdHandler();
    }
    
    Window::~Window() {
        //TODO::
    }
    
    void Window::initMdHandler() {
        MdHandler *mdhandler = new MdHandler(mdEditor);
        
        QObject::connect(mdEditor, SIGNAL(textChanged()), mdhandler, SLOT(handleMdChanged()));
        QObject::connect(mdhandler, SIGNAL(mdCompiled(QString)), this, SLOT(handleMdCompiled(QString)));
    }
    
    void Window::createMenus() {
        QAction *action;
        
        QMenu *file = new QMenu(this);
        
        action = new QAction("Open", this);
        action->setShortcut(tr("CTRL+O"));
        file->addAction(action);
        
        action = new QAction("Close", this);
        action->setShortcut(tr("CTRL+C"));
        file->addAction(action);
        
        menuBar()->addMenu(file)->setText("&File");
        
        statusBar();
    }
    
    void Window::createComponents() {
        mdEditor = new QTextEdit(this);
        mdEditor->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);
        mdEditor->setText("Play markdown here !");
        
        htmlEditor = new QTextEdit(this);
        htmlEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        htmlEditor->setText("Show your html here !");
        
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
        htmlEditor->setHtml(str);
    }
}

