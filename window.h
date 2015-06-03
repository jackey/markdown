//
//  window.h
//  markdown
//
//  Created by Jackey Chen on 5/27/15.
//
//

#ifndef __markdown__window__
#define __markdown__window__

#include <stdio.h>
#include <QWidget>
#include <QMainWindow>


class QTextEdit;

namespace md {
    
    class Window: public QMainWindow {
        Q_OBJECT
        
    public:
        Window(QWidget *parent = 0);
        ~Window();
        
        void createMenus();
        void createComponents();
        void initMdHandler();
        
    public slots:
        void handleMdCompiled(QString compiledString);
        
    private:
        QTextEdit *mdEditor;
        QTextEdit *htmlEditor;
        
    };
}


#endif /* defined(__markdown__window__) */
