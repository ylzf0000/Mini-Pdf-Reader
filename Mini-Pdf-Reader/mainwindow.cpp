#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pdfprinttool.h"
#include "pdflistview.h"
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
//    ui->widget->setVisible(false);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openPdf);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::closePdf);
    connect(ui->actionPrint, &QAction::triggered, this, &MainWindow::printPdf);
    connect(ui->actionQuickPrint, &QAction::triggered, this, &MainWindow::quickPrintPdf);
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &MainWindow::onComboBoxTextChange);
    connect(m_delegate, &PdfListItemDelegate::onPaint, this, &MainWindow::updateCurrentPageCount);
}

MainWindow::MainWindow(const QString &fileName, QWidget *parent) : MainWindow(parent)
{
    m_fileName = fileName;
//    showPdf();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isFileExist() const
{
    QFile file(m_fileName);
    return file.exists();
}

float MainWindow::scale(const QString &txt) const
{
    bool ok;
    float s = txt.left(txt.count() - 1).toFloat(&ok);
    s = ok ? s : 100;
    return s / 100;
}

float MainWindow::scale() const
{
    return scale(ui->comboBox->currentText());
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
    if(!isFileExist())
    {
        QString e = QString("%1 not exists.").arg(m_fileName);
        QMessageBox::critical(nullptr, __func__, e);
        return;
    }
    QString name = m_fileName.mid(m_fileName.lastIndexOf('/') + 1);
    setWindowTitle(tr("%1 - Mini PDF Reader").arg(name));
    m_model->loadDocument(m_fileName);
    int pageCount = m_model->pageCount();
    ui->label->setText(QString("/%1").arg(pageCount));
    _showPdf();
}

void MainWindow::_showPdf()
{
    float sca = scale();
    fz_matrix ctm;
    fz_scale(&ctm, sca, sca);
    m_model->resetCtm(ctm);
    ui->widget->setVisible(true);
    QTimer::singleShot(200,[=]{
        if(m_delegate->size() != QSize())
        {
            int h = std::min(768, m_delegate->size().height());
            resize(m_delegate->size().width() + 100, h);
            SetWidgetCentral(this);
        }
    });
}

void MainWindow::closePdf()
{

}

void MainWindow::onComboBoxTextChange(const QString &txt)
{
    _showPdf();
}

void MainWindow::printPdf()
{
    if(fileName().isEmpty())
        return;
    DEBUG_VAR(fileName());
    QString cmd = QString("pdfprint.exe -prompt \"%1\"").arg(fileName());
    DEBUG_VAR(PdfPrintTool::Instance().PrintW(cmd));
}

void MainWindow::quickPrintPdf()
{
    if(fileName().isEmpty())
        return;
    DEBUG_VAR(fileName());
    QString cmd = QString("pdfprint.exe -quiet \"%1\"").arg(fileName());
    DEBUG_VAR(PdfPrintTool::Instance().PrintW(cmd));
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

void MainWindow::updateCurrentPageCount(int i)
{
    ui->lineEdit->setText(QString("%1").arg(m_model->beginPage() + i + 1));
}

void MainWindow::on_actionExit_triggered(bool checked)
{
    close();
}
