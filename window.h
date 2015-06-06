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
#include <QFile>

class QTextEdit;
class QTextStream;

namespace md {
    
    enum SAVE_TYPE {SAVE_PDF, SAVE_HTML};
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
        void saveAsPDF();
        void saveAsHTML();
        
        // 保存文件
        // 如果保存文件是PDF, 则也保存对应的PDF文件;同理 HTML
        void saveTriggered();
        
    private:
        QTextEdit *mdEditor;
        QTextEdit *htmlEditor;
        QTextStream *screenStyleFile;
        QString mdSaveTo;
        QString pdfSaveTo;
        QString htmlSaveTo;
        SAVE_TYPE saveType = SAVE_HTML;
        
        // Menu action
        QAction *pdfAction;
        QAction *htmlAction;
        QAction *saveAction;
        
        QFile styleFile;
    };
}


#endif /* defined(__markdown__window__) */
