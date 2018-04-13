#include "pdflistview.h"
#include <QScrollBar>
PdfListView::PdfListView(QWidget *parent) : QListView(parent)
{
    setSizeAdjustPolicy(AdjustToContents);
    setVerticalScrollMode(ScrollPerPixel);
    verticalScrollBar()->setSingleStep(20);
}
