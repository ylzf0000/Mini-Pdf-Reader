#ifndef PDFPRINTTOOL_H
#define PDFPRINTTOOL_H
#include "stdafx.h"
typedef int (WINAPI *VeryPDF_PDFPrintAFunc)(LPCTSTR lpCommand);
typedef int (WINAPI *VeryPDF_PDFPrintWFunc)(LPCWSTR lpCommand);
class PdfPrintTool
{
    PdfPrintTool();
public:
    static PdfPrintTool &Instance();
    int LoadDLL();
    int PrintA(const QString &cmd);
    int PrintW(const QString &cmd);
private:
    VeryPDF_PDFPrintAFunc pdfPrintAFunc;
    VeryPDF_PDFPrintWFunc pdfPrintWFunc;
};

#endif // PDFPRINTTOOL_H
