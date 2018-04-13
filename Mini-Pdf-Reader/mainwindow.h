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

    float scale() const;
    void openPdf();
    void showPdf();
    void closePdf();
    void printPdf();
    void quickPrintPdf();

    PdfListView *view() const;
    void setView(PdfListView *view);

    PdfListModel *model() const;
    void setModel(PdfListModel *model);

    PdfListItemDelegate *delegate() const;
    void setDelegate(PdfListItemDelegate *delegate);

    QString fileName() const;
    void setFileName(const QString &fileName);

public slots:
    void updateCurrentPageCount(int i);

private:
    Ui::MainWindow *ui;
    QString m_fileName;
    PdfListView *m_view;
    PdfListModel *m_model;
    PdfListItemDelegate *m_delegate;
};

#endif // MAINWINDOW_H
