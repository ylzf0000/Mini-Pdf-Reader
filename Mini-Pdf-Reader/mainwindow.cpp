#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_view = new PdfListView;
    m_model = new PdfListModel;
    m_delegate = new PdfListItemDelegate;
    m_view->setModel(m_model);
    m_view->setItemDelegate(m_delegate);
    ui->verticalLayout->addWidget(m_view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

PdfListView *MainWindow::view() const
{
    return m_view;
}

void MainWindow::setView(PdfListView *view)
{
    m_view = view;
}

PdfListModel *MainWindow::model() const
{
    return m_model;
}

void MainWindow::setModel(PdfListModel *model)
{
    m_model = model;
}

PdfListItemDelegate *MainWindow::delegate() const
{
    return m_delegate;
}

void MainWindow::setDelegate(PdfListItemDelegate *delegate)
{
    m_delegate = delegate;
}
