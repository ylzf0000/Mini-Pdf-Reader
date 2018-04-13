#ifndef MUPDFTOOL_H
#define MUPDFTOOL_H
#include "stdafx.h"
#include <mupdf/pdf.h>

#define FZ_CATCH(ctx)                                                                       \
    fz_catch(ctx)                                                                           \
    {                                                                                       \
        qDebug() << QString("%2. Error : %1").arg(fz_caught_message(ctx)).arg(__func__);    \
        fz_drop_context(ctx);                                                               \
    }

#define FZ_CATCH_DROPDOC(ctx, doc)                                                          \
    fz_catch(ctx)                                                                           \
    {                                                                                       \
        qDebug() << QString("%2. Error : %1").arg(fz_caught_message(ctx)).arg(__func__);    \
        fz_drop_document(ctx, doc);                                                         \
        fz_drop_context(ctx);                                                               \
        return;                                                                             \
    }
#define FZ_CATCH_DROPDOC_NORETURN(ctx, doc)                                                 \
    fz_catch(ctx)                                                                           \
    {                                                                                       \
        qDebug() << QString("%2. Error : %1").arg(fz_caught_message(ctx)).arg(__func__);    \
        fz_drop_document(ctx, doc);                                                         \
        fz_drop_context(ctx);                                                               \
    }
namespace MuPdfUtil
{
    class Document
    {
    public:
        ~Document();
        Document();
        Document(const QString &fileName);
        void Open(const QString &fileName);
        int GetPageCount() const;
        fz_pixmap *LoadPixmap(int i, fz_matrix *mat) const;

        fz_context *ctx() const;
        void setCtx(fz_context *ctx);

        fz_document *doc() const;
        void setDoc(fz_document *doc);

    private:
        fz_context *m_ctx = nullptr;
        fz_document *m_doc = nullptr;
        mutable int pageCount = -1;
    };
}
#endif // MUPDFTOOL_H
