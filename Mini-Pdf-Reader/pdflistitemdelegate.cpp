#include "pdflistitemdelegate.h"

#include <QPainter>

#include <pdflistview.h>

PdfListItemDelegate::PdfListItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void PdfListItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.data(Qt::DisplayRole).canConvert<QImage>())
    {
        QImage img = index.data(Qt::DisplayRole).value<QImage>();
        painter->drawImage(option.rect.x(), option.rect.y(), img);
//        if(PdfListView *view = dynamic_cast<PdfListView*>(parent()))
//        {
//            view->resize(img.width(), view->height());
//        }
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

void PdfListItemDelegate::setSize(const QSize &size)
{
    m_size = size;
}
