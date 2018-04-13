#include "pdflistview.h"
#include <QScrollBar>
PdfListView::PdfListView(QWidget *parent) : QListView(parent)
{
//    setSpacing(10);
    setSizeAdjustPolicy(AdjustToContents);
    setVerticalScrollMode(ScrollPerPixel);
    verticalScrollBar()->setSingleStep(20);
}
