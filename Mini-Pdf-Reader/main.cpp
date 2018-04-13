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
    MainWindow w;
    w.show();
    return a.exec();
}
