#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <string>
#include <vector>

/*///////////////////////////////////

  Parameter:
    lpCommand : Command Line options to print PDF file

	Return values:
	   0: Print PDF file successfully.
	 -10: PDFPrint Library be damaged.
	 -11: Something is wrong in the command line options.
	-101: Can't start "spooler" service, please start "spooler" service from Service Manager by manual.
	  -4: Can't locate specify printer in this computer.
	 -12: Can't open specify printer.
	 -13: Something is wrong when set options to printer.
	  -5: No input PDF file for printing.
	   9: Password Required to open this PDF file.
	Other values: Something is wrong during render PDF file.
///////////////////////////////////*/

typedef int (WINAPI *VeryPDF_PDFPrintAFunc)(LPCTSTR lpCommand);
typedef int (WINAPI *VeryPDF_PDFPrintWFunc)(LPCWSTR lpCommand);

HMODULE	g_hVeryW = NULL;
VeryPDF_PDFPrintAFunc	VeryPDF_PDFPrintA;
VeryPDF_PDFPrintWFunc	VeryPDF_PDFPrintW;

void	GetModulePath(char *out_path,char *in_name);
BOOL	LoadPDFPrintDLL(void);
void	FreePDFPrintDLL();

void GetModulePath(char *out_path,char *in_name)
{
	char *p;
	GetModuleFileName(NULL,out_path,256);
	p = strrchr(out_path,'\\');
	p[1]=0;
	strcat(out_path,in_name);
}
BOOL LoadPDFPrintDLL()
{
	char path[_MAX_PATH];
	GetModulePath(path,"pdfprintsdk.dll");
	g_hVeryW=LoadLibrary(path);
	if(g_hVeryW==NULL)
		goto Failer;

	VeryPDF_PDFPrintA = (VeryPDF_PDFPrintAFunc)GetProcAddress(g_hVeryW, "VeryPDF_PDFPrint");
	if(VeryPDF_PDFPrintA == NULL)
		goto Failer;
	VeryPDF_PDFPrintW = (VeryPDF_PDFPrintWFunc)GetProcAddress(g_hVeryW, "VeryPDF_PDFPrintW");
	if(VeryPDF_PDFPrintW == NULL)
		goto Failer;

	return TRUE;
Failer:
	FreePDFPrintDLL(); 
	return FALSE;
}
void FreePDFPrintDLL()
{
	if(g_hVeryW == NULL)
		return ;
	FreeLibrary(g_hVeryW);
	g_hVeryW=NULL;
}
int TestPDFPrintDLLA(const char *lpCommand)
{
	if(LoadPDFPrintDLL() == FALSE)
		return 0;
	int nRet = VeryPDF_PDFPrintA(lpCommand);
	FreePDFPrintDLL();
	return nRet;
}
int TestPDFPrintDLLW(const wchar_t *lpCommand)
{
	if(LoadPDFPrintDLL() == FALSE)
		return 0;
	int nRet = VeryPDF_PDFPrintW(lpCommand);
	FreePDFPrintDLL();
	return nRet;
}

std::string wstrtostr(const std::wstring wstr)
{
	if(wstr.size() == 0)
		return "";
    // Convert a Unicode string to an ASCII string
    std::string strTo;
    char *szTo = new char[wstr.length() + 1];
    szTo[wstr.size()] = '\0';
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, szTo, (int)wstr.length(), NULL, NULL);
    strTo = szTo;
    delete[] szTo;
    return strTo;
}

std::wstring strtowstr(const std::string str)
{
    // Convert an ASCII string to a Unicode String
    std::wstring wstrTo;
    wchar_t *wszTo = new wchar_t[str.length() + 1];
    wszTo[str.size()] = L'\0';
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wszTo, (int)str.length());
    wstrTo = wszTo;
    delete[] wszTo;
    return wstrTo;
}

void main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("testsdk2.exe C:\\test.pdf\n");
		printf("testsdk2.exe C:\\test.odt\n");
		printf("testsdk2.exe C:\\test.doc\n");
		printf("testsdk2.exe C:\\test.docx\n");
		printf("testsdk2.exe C:\\test.rtf\n");
		printf("testsdk2.exe C:\\test.ppt\n");
		printf("testsdk2.exe C:\\test.pptx\n");
		printf("testsdk2.exe C:\\test.xls\n");
		printf("testsdk2.exe C:\\test.xlsx\n");
		printf("testsdk2.exe C:\\test.html\n");
		printf("testsdk2.exe C:\\test.wmf\n");
		printf("testsdk2.exe C:\\test.emf\n");
		printf("testsdk2.exe C:\\test.jpg\n");
		printf("testsdk2.exe C:\\test.png\n");
		printf("testsdk2.exe C:\\test.bmp\n");
		printf("testsdk2.exe C:\\test.tif\n");
		printf("testsdk2.exe C:\\test.gif\n");
		return;
	}
	char *lpLicenseKey = "XXXXXXXXXXXXXXXXXX";
	char szCommandLine[2048] = {0};

	sprintf(szCommandLine,"pdfprint -$ \"%s\" ",lpLicenseKey);
	for(int i = 1; i < argc; i++)
	{
		strcat(szCommandLine, " \"");
		strcat(szCommandLine, argv[i]);
		strcat(szCommandLine, "\"");
	}

	printf("[Cmd]=\n%s\n", szCommandLine);
	printf("\n==============================================================\n");
	int nRet = 0;
	nRet = TestPDFPrintDLLA(szCommandLine);
	nRet = TestPDFPrintDLLW(strtowstr(szCommandLine).c_str());
	printf("\n==============================================================\n");
	printf("Return Value = %d\n",nRet);
	printf("\n==============================================================\n");
}