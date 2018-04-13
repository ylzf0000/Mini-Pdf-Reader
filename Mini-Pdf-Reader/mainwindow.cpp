#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pdfprinttool.h"

#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Mini PDF Reader"));
    m_view = new PdfListView(this);
    m_model = new PdfListModel(this);
    m_delegate = new PdfListItemDelegate(this);
    m_view->setModel(m_model);
    m_view->setItemDelegate(m_delegate);
    ui->comboBox->setCurrentIndex(2);
    ui->verticalLayout->addWidget(m_view);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openPdf);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::closePdf);
    connect(ui->actionPrint, &QAction::triggered, this, &MainWindow::printPdf);
    connect(ui->actionQuickPrint, &QAction::triggered, this, &MainWindow::quickPrintPdf);
}

MainWindow::~MainWindow()
{
    delete ui;
}

float MainWindow::scale() const
{
    bool ok;
    QString txt = ui->comboBox->currentText();
    float s = txt.left(txt.count() - 1).toFloat(&ok);
    s = ok ? s : 100;
    return s / 100;
}

void MainWindow::openPdf()
{
    m_fileName = QFileDialog::getOpenFileName(this, tr("Open PDF file"), "D:/", "*.pdf");
    if(!m_fileName.isNull())
    {
        showPdf();
    }
}

void MainWindow::showPdf()
{
    setWindowTitle(tr("%1 - Mini PDF Reader").arg(m_fileName));
    float sca = scale();
    fz_matrix ctm;
    fz_scale(&ctm, sca, sca);
    m_model->LoadDocument(m_fileName);
    m_model->setCtm(ctm);
    m_model->Update();
    QTimer::singleShot(1000,[=]{
        DEBUG_VAR(m_delegate->size());
        if(m_delegate->size() != QSize())
        {
            m_view->resize(m_delegate->size().width(), m_view->height());
        }
    });
}

void MainWindow::closePdf()
{

}

void MainWindow::printPdf()
{
    if(fileName().isEmpty())
        return;
    DEBUG_FUNC;
    DEBUG_VAR(fileName());
    QString cmd = QString("pdfprint.exe -prompt \"%1\"").arg(fileName());
    DEBUG_VAR(PdfPrintTool::Instance().PrintW(cmd));
}

void MainWindow::quickPrintPdf()
{

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

QString MainWindow::fileName() const
{
    return m_fileName;
}

void MainWindow::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}
