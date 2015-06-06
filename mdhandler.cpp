//
//  mdhandler.cpp
//  markdown
//
//  Created by Jackey Chen on 6/3/15.
//
//

#include "mdhandler.h"
#include <QTextEdit>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
#include <mkdio.h>
}

#include <QObject>

MdHandler::MdHandler(QTextEdit *editor)
:mdEditor(editor) {
    //TODO::
}

MdHandler::~MdHandler() {
    //TODO::
}

void MdHandler::handleMdChanged() {
    QString str = mdEditor->toPlainText();
    
    const char *txt = str.toUtf8().constData();
    int size = strlen(txt);
    
    MMIOT *mddoc;
    
    mddoc = mkd_string(txt, size, 0);
    
    mkd_compile(mddoc, 0);
    char *buf;
    int sizeBuf;
    sizeBuf = mkd_document(mddoc, &buf);

    // 把内容转换到QString中
    QString html = QString::fromUtf8(buf);
    
    if (html.size() <= 0 || sizeBuf == EOF) {
        html = mdEditor->toHtml();
    }
    
    // 释放内存
    free(buf);
    
    // 触发事件
    emit mdCompiled(html);
}

// 编译 Markdown -> HTML
const QString MdHandler::markdown(QString mdText) {
    const char *data = mdText.toUtf8().constData();
    int size = strlen(data);
    
    std::cout << "编译的内容: " << data << std::endl;
    
    MMIOT *doc = mkd_string(data, size, 0);
    mkd_compile(doc, 0);
    char *buf;
    int sizeBuf;
    sizeBuf = mkd_document(doc, &buf);
    
    std::cout << "编译的长度: " << sizeBuf;
    
    QString html = QString::fromUtf8(buf);
    
    free(buf);
    
    std::cout << "默认HTML " << html.toUtf8().data();
    
    return html;
}


