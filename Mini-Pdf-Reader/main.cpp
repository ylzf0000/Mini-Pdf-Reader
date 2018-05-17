#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto loadGlobalTrans = [&a]{
        static QTranslator trans;
        trans.load(":/qt_zh_CN.qm");
        a.installTranslator(&trans);
    };
    auto loadMineTrans = [&a]{
        static QTranslator trans;
        trans.load(":/client_cn.qm");
        a.installTranslator(&trans);
    };
    loadGlobalTrans();
    loadMineTrans();
    MainWindow *w;
    if(argc >= 2)
    {
        QString fileName(argv[1]);
        qDebug() << fileName;
        w = new MainWindow(fileName);
        w->showPdf();
    }
    else
    {
        w = new MainWindow;
    }
    w->show();
    return a.exec();
}
