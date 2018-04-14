#include "pdflistview.h"
#include <QScrollBar>
#include "pdflistmodel.h"
PdfListView::PdfListView(QWidget *parent) : QListView(parent)
{
    setSizeAdjustPolicy(AdjustToContents);
    setVerticalScrollMode(ScrollPerPixel);
    verticalScrollBar()->setSingleStep(20);
    setStyleSheet("background-color:gray;");
    verticalScrollBar()->setStyleSheet("QScrollBar:vertical{background:rgba(0, 0, 0, 0);}");
    setSpacing(5);
}

void PdfListView::verticalScrollbarValueChanged(int value)
{
    QListView::verticalScrollbarValueChanged(value);
    int maxVal = verticalScrollBar()->maximum();
    if(value + 10 >= maxVal)
    {
        if(PdfListModel *m = dynamic_cast<PdfListModel*>(this->model()))
        {
            m->resetPageCount();
        }
    }
}
