#include "pdflistmodel.h"
using namespace std;
PdfListModel::~PdfListModel()
{

}

PdfListModel::PdfListModel(QObject *parent)
    : QAbstractListModel(parent),
      m_samplesList(make_shared<deque<item_s>>()),
      m_imgList(make_shared<deque<img_s>>()),
      m_indexList(make_shared<deque<QModelIndex>>()),
      m_ctm(make_shared<fz_matrix>()),
      m_size(make_shared<QSize>())
{

}

PdfListModel::PdfListModel(const QString &fileName, QObject *parent):PdfListModel()
{
    m_fileName = fileName;
    m_doc.open(m_fileName);
}

void PdfListModel::loadDocument(const QString &fileName)
{
    if(m_fileName == fileName)
        return;
    m_fileName = fileName;
    m_doc.open(fileName);
}

fz_pixmap *PdfListModel::loadPixmap(int i) const
{
    return m_doc.loadPixmap(i, m_ctm.get());
}

void PdfListModel::resetCtm(const fz_matrix &mat)
{
    beginResetModel();
    *m_ctm = mat;
    m_samplesList->clear();
    m_imgList->clear();
    endResetModel();
}

//void PdfListModel::resetPageCount()
//{
//    beginResetModel();
//    m_showPage += m_incrementPage;
//    endResetModel();
//}

void PdfListModel::resetBeginPage(int page)
{
    beginResetModel();
    m_beginPage = page;
    endResetModel();
}

int PdfListModel::pageCount() const
{
    static int page_count = m_doc.pageCount();
    return page_count;
}

int PdfListModel::nextBeginPage() const
{
    int next = m_beginPage + MAX_ROW_COUNT / 2;
    return  next >= pageCount() ? m_beginPage : next;
}

int PdfListModel::midRow() const
{
    if(nextBeginPage() > beginPage())
        return MAX_ROW_COUNT / 2;
    return beginPage();
}

unsigned char *PdfListModel::samples32FromFzPixmap(fz_pixmap *pix) const
{
//    int w = pix->w;
    int h = fz_pixmap_height(m_doc.ctx(), pix);
//    int n = pix->n;
    int stride = pix->stride;
//    int stride2 = static_cast<int>(std::ceil(stride / 4.0)) * 4;
    int stride2 = (stride * 8 + 31) / 32 * 4;
    unsigned char * samples32 = new unsigned char[stride2 * h]{0};
    int des_offset = 0;
    int src_offset = 0;
    for(int i = 0; i < h; ++i)
    {
        std::memcpy(samples32 + des_offset, pix->samples + src_offset, stride);
        src_offset += stride;
        des_offset += stride2;
    }
    return samples32;
}

QSize PdfListModel::size32FromFzPixmap(fz_pixmap *pix) const
{
    int w = fz_pixmap_width(m_doc.ctx(), pix);
    int h = fz_pixmap_height(m_doc.ctx(), pix);
//    int w2 = static_cast<int>(std::ceil(w / 4.0)) * 4;
    int w2 = w;
    return { w2, h };
}

int PdfListModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    if(m_fileName.isEmpty())
        return 0;
    if(pageCount() <= MAX_ROW_COUNT)
        return pageCount();
    int diff = pageCount() - beginPage();
    int row = diff > MAX_ROW_COUNT ? MAX_ROW_COUNT : diff;
    return row;
}

QVariant PdfListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(m_fileName.isEmpty())
        return QVariant();
    if(role == Qt::DisplayRole)
    {
//        DEBUG_VAR(index.row());
        int i = index.row() + m_beginPage;
        std::deque<item_s> &sampList = *m_samplesList;

        unsigned char *samples32 = nullptr;
        auto it = std::find_if(sampList.cbegin(), sampList.cend(), [=](const item_s &item){
            return item.i == i;
        });

        if(it != sampList.cend() && it->samples)
        {
            samples32 = it->samples;
        }
        else
        {
            fz_pixmap *pix = loadPixmap(i);
            samples32 = samples32FromFzPixmap(pix);
            sampList.push_back({i, samples32});
            *m_size = size32FromFzPixmap(pix);
            if(pix)
                fz_drop_pixmap(m_doc.ctx(), pix);
        }

        deque<QModelIndex> &indexList = *m_indexList;
        auto it_index = std::find_if(indexList.cbegin(), indexList.cend(), [=](const QModelIndex &obj){
            return obj == index;
        });
        if(it_index == indexList.cend())
        {
            indexList.push_back(index);
        }
        if(indexList.size() > MAX_ROW_COUNT)
        {
            if(m_defaultImg.isNull())
            {
                m_defaultImg = QImage(*m_size, QImage::Format_RGB888);
                m_defaultImg.fill(Qt::white);
            }
//            setData(indexList.front(), m_defaultImg, Qt::DisplayRole);
            indexList.pop_front();
        }
        QImage img = QImage(samples32, m_size->width(), m_size->height(), QImage::Format_RGB888, [](void *data){
            if(unsigned char *samples32 = static_cast<unsigned char*>(data))
                delete[] samples32;
        });
//        DEBUG_VAR(img.scanLine(1) - img.scanLine(0));
        return img;
    }
    return QVariant();
}

QString PdfListModel::fileName() const
{
    return m_fileName;
}

MuPdfUtil::Document PdfListModel::doc() const
{
    return m_doc;
}

void PdfListModel::setDoc(const MuPdfUtil::Document &doc)
{
    m_doc = doc;
}

std::shared_ptr<fz_matrix> PdfListModel::ctm() const
{
    return m_ctm;
}

void PdfListModel::setCtm(const std::shared_ptr<fz_matrix> &ctm)
{
    m_ctm = ctm;
}

int PdfListModel::beginPage() const
{
    return m_beginPage;
}

void PdfListModel::setBeginPage(int beginPage)
{
    m_beginPage = beginPage;
}


