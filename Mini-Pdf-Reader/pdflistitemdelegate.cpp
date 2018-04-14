#include "pdflistitemdelegate.h"
#include <QPainter>
#include <QMainWindow>
#include "pdflistview.h"

PdfListItemDelegate::PdfListItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void PdfListItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.data(Qt::DisplayRole).canConvert<QImage>())
    {
        emit onPaint(index.row());
        QImage img = index.data(Qt::DisplayRole).value<QImage>();
        setSize(img.size());
        int w = option.rect.width();
        int s = img.width();
        int x = (w - s) / 2;
        painter->drawImage(x, option.rect.y(), img);
    }
}

QSize PdfListItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.data(Qt::DisplayRole).canConvert<QImage>())
    {
        QImage img = index.data(Qt::DisplayRole).value<QImage>();
        return m_size = img.size();
    }
    return {};
}

QSize PdfListItemDelegate::size() const
{
    return m_size;
}

void PdfListItemDelegate::setSize(const QSize &size) const
{
    m_size = size;
}
