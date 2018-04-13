#include "pdfprinttool.h"

PdfPrintTool::PdfPrintTool()
{
    LoadDLL();
}

PdfPrintTool &PdfPrintTool::Instance()
{
    static PdfPrintTool instance;
    return instance;
}

int PdfPrintTool::LoadDLL()
{
    const QString name = "pdfprintsdk";
    DEBUG_VAR(name);
    QLibrary lib(name);
    if(lib.load())
    {
         pdfPrintAFunc = reinterpret_cast<VeryPDF_PDFPrintAFunc>(lib.resolve("VeryPDF_PDFPrint"));
         pdfPrintWFunc = reinterpret_cast<VeryPDF_PDFPrintWFunc>(lib.resolve("VeryPDF_PDFPrintW"));
    }
    else
    {
        POP_ERROR(lib.errorString());
        DEBUG_VAR(lib.errorString());
    }
    return 0;
}

int PdfPrintTool::PrintA(const QString &cmd)
{
    if(!pdfPrintAFunc)
    {
        POP_ERROR("pdfPrintAFunc is null");
        return 0;
    }
    std::wstring s = cmd.toStdWString();
    return pdfPrintAFunc(s.data());
}

int PdfPrintTool::PrintW(const QString &cmd)
{
    if(!pdfPrintWFunc)
    {
        POP_ERROR("pdfPrintWFunc is null");
        return 0;
    }
    std::wstring s = cmd.toStdWString();
    return pdfPrintWFunc(s.data());
}
