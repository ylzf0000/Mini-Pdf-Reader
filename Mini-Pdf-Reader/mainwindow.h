#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pdflistitemdelegate.h"
#include "pdflistmodel.h"
#include "pdflistview.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    PdfListView *view() const;
    void setView(PdfListView *view);

    PdfListModel *model() const;
    void setModel(PdfListModel *model);

    PdfListItemDelegate *delegate() const;
    void setDelegate(PdfListItemDelegate *delegate);

private:
    Ui::MainWindow *ui;
    PdfListView *m_view;
    PdfListModel *m_model;
    PdfListItemDelegate *m_delegate;
};

#endif // MAINWINDOW_H
