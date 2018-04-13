#ifndef PDFLISTMODEL_H
#define PDFLISTMODEL_H

#include <QAbstractListModel>
#include "FzPdf/fz_header.h"
#include <unordered_map>
class PdfListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    ~PdfListModel();
    explicit PdfListModel(QObject *parent = nullptr);
    explicit PdfListModel(const QString &fileName, QObject *parent = nullptr);
    void LoadDocument(const QString &fileName);
    fz_pixmap *LoadPixmap(int i) const;
    void Update();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QString fileName() const;

    fz_matrix ctm() const;
    void setCtm(const fz_matrix &ctm);

    MuPdfUtil::Document doc() const;
    void setDoc(const MuPdfUtil::Document &doc);

private:
    const int MAX_COUNT = 10;
    QString m_fileName;
    mutable fz_matrix m_ctm;
    MuPdfUtil::Document m_doc;
    mutable std::unordered_map<int, fz_pixmap*> m_pixMap;
    mutable QSize m_size;
};

#endif // PDFLISTMODEL_H
