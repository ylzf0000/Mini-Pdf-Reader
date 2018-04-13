#include "mainwindow.h"
#include "program.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QProcess>

time_t GetTime()
{
    time_t t;
    std::time(&t);
    return t;
}

bool QCopyFile(const QString &src, const QString &desDir, bool cover)
{
    if(src == desDir)
        return true;
    if(!QFile::exists(src))
        return false;
    return QFile::copy(src, desDir);
}

QRect GetRectFrom2Point(const QPoint &p1, const QPoint &p2)
{
    auto px = std::minmax(p1.x(), p2.x());
    auto py = std::minmax(p1.y(), p2.y());
    return QRect(QPoint(px.first, py.first), QPoint(px.second, py.second));
}

QRect InterSection2Rect(const QRect &r1, const QRect &r2)
{
    int xmax = std::max(r1.x(), r2.x());
    int ymax = std::max(r1.y(), r2.y());

    int xmin = std::min(r1.x() + r1.width(), r2.x() + r2.width());
    int ymin = std::min(r1.y() + r1.height(), r2.y() + r2.height());
    if(xmax <= xmin && ymax <= ymin)
        return QRect(xmax, ymax, xmin - xmax, ymin - ymax);
    return QRect();
}

QString UuidToStringEx()
{
    QString s = QUuid::createUuid().toString();
    s = s.remove("{").remove("}");
    return s;
}

void SetWidgetCentral(QWidget *w)
{
    w->move((qApp->desktop()->availableGeometry().width() - w->width()) / 2 + qApp->desktop()->availableGeometry().x(),
               (qApp->desktop()->availableGeometry().height() - w->height()) / 2 + qApp->desktop()->availableGeometry().y());
}
