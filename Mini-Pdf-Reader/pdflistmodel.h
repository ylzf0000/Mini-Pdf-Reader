#ifndef PDFLISTMODEL_H
#define PDFLISTMODEL_H

#include <QAbstractListModel>
#include "FzPdf/fz_header.h"
#include <unordered_map>
#include <deque>
#include <memory>
class PdfListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    ~PdfListModel();
    explicit PdfListModel(QObject *parent = nullptr);
    explicit PdfListModel(const QString &fileName, QObject *parent = nullptr);
    void loadDocument(const QString &fileName);
    fz_pixmap *loadPixmap(int i) const;
    void resetCtm(const fz_matrix &mat);
    void resetPageCount();
private:
    unsigned char *samples32FromFzPixmap(fz_pixmap *pix) const;
    QSize size32FromFzPixmap(fz_pixmap *pix) const;
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QString fileName() const;

    MuPdfUtil::Document doc() const;
    void setDoc(const MuPdfUtil::Document &doc);

    std::shared_ptr<fz_matrix> ctm() const;
    void setCtm(const std::shared_ptr<fz_matrix> &ctm);

private:
    size_t MAX_COUNT = 10;
    mutable size_t m_showPage = 10;
    size_t m_incrementPage = 10;
    QString m_fileName;
    MuPdfUtil::Document m_doc;
    struct item_s
    {
        int i;
        unsigned char *samples;
    };
    struct img_s
    {
        int i;
        QImage img;
    };
    std::shared_ptr<std::deque<item_s>> m_samplesList;
    std::shared_ptr<std::deque<img_s>> m_imgList;
    std::shared_ptr<std::deque<QModelIndex>> m_indexList;
//    std::shared_ptr<std::unordered_map<int, unsigned char *>> m_samplesList;
    std::shared_ptr<fz_matrix> m_ctm;
    std::shared_ptr<QSize> m_size;
    mutable QImage m_defaultImg;
    mutable int m_beginPage = 0;

};

#endif // PDFLISTMODEL_H
