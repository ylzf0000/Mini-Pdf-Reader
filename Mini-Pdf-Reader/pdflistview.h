#ifndef PDFLISTVIEW_H
#define PDFLISTVIEW_H
#include "stdafx.h"
#include <QListView>
class PdfListView : public QListView
{
    Q_OBJECT
public:
    explicit PdfListView(QWidget *parent = nullptr);

signals:

public slots:

private:


    // QAbstractItemView interface
protected slots:
    virtual void verticalScrollbarValueChanged(int value) override;
};

#endif // PDFLISTVIEW_H
