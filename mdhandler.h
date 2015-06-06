//
//  mdhandler.h
//  markdown
//
//  Created by Jackey Chen on 6/3/15.
//
//

#ifndef __markdown__mdhandler__
#define __markdown__mdhandler__

#include <stdio.h>
#include <QObject>

class QTextEdit;

class MdHandler: public QObject {
    Q_OBJECT
    
public:
    MdHandler(QTextEdit *);
    ~MdHandler();
    const QString getCompiledMd();
    static const QString markdown(QString mdText);
    
public slots:
    void handleMdChanged();

signals:
    void mdCompiled(QString html);
    
private:
    QString mdText;
    const QString compiledMd;
    QTextEdit *mdEditor;
};

#endif /* defined(__markdown__mdhandler__) */
