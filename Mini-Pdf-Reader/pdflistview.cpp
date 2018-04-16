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
    if(value >= maxVal)
    {
        if(PdfListModel *m = dynamic_cast<PdfListModel*>(this->model()))
        {
            DEBUG_VAR(m->beginPage());
            int next = m->nextBeginPage();
            if(next > m->beginPage())
                m->resetBeginPage(next);
//            QModelIndex idx = this->currentIndex();

            this->setCurrentIndex(m->index(m->midRow()));
//            m->resetPageCount();
//            QModelIndex index = indexAt({rect().x() / 2, rect().y() / 2});
//            m->resetBeginPage(m->beginPage() + 5);
//            verticalScrollBar()->setValue(verticalScrollBar()->maximum()/10*4.5);
//            QTimer::singleShot(200, [=]{ verticalScrollBar()->scroll(0,verticalScrollBar()->maximum()/2); });
        }
    }

//    this->setCurrentIndex();
}
