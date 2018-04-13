#include "mupdftool.h"
#include "fz_header.h"
using namespace std;

MuPdfUtil::Document::~Document()
{
    fz_drop_document(m_ctx, m_doc);
    fz_drop_context(m_ctx);
}

MuPdfUtil::Document::Document()
{
    m_ctx = fz_new_context(nullptr, nullptr, FZ_STORE_UNLIMITED);
    if(!m_ctx)
    {
        qDebug() << QString("%1. cannot create mupdf m_ctx").arg(__func__);
    }
    fz_register_document_handlers(m_ctx);


}

MuPdfUtil::Document::Document(const QString &fileName) : Document()
{
    Open(fileName);
}

void MuPdfUtil::Document::Open(const QString &fileName)
{
    string name = fileName.toStdString();
    fz_try(m_ctx)
    {
        m_doc = fz_open_document(m_ctx, name.data());
    }
    FZ_CATCH_DROPDOC(m_ctx, m_doc);
}

int MuPdfUtil::Document::GetPageCount() const
{
    if(pageCount >= 0)
        return pageCount;
    fz_try(m_ctx)
    {
        pageCount = fz_count_pages(m_ctx, m_doc);
    }
    FZ_CATCH_DROPDOC_NORETURN(m_ctx, m_doc);
    return pageCount;
}

fz_pixmap *MuPdfUtil::Document::LoadPixmap(int i, fz_matrix *mat) const
{
    fz_pixmap *pixmap;
    fz_try(m_ctx)
        pixmap = fz_new_pixmap_from_page_number(m_ctx, m_doc, i, mat, fz_device_rgb(m_ctx), 0);
    FZ_CATCH_DROPDOC_NORETURN(m_ctx, m_doc);
    return pixmap;
}

fz_document *MuPdfUtil::Document::doc() const
{
    return m_doc;
}

void MuPdfUtil::Document::setDoc(fz_document *doc)
{
    m_doc = doc;
}

fz_context *MuPdfUtil::Document::ctx() const
{
    return m_ctx;
}

void MuPdfUtil::Document::setCtx(fz_context *ctx)
{
    m_ctx = ctx;
}
