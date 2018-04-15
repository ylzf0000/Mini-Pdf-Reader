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

__declspec(dllexport)
int WINAPI VeryPDF_PDFPrint(LPCTSTR lpCommand);

typedef int (WINAPI *VeryPDF_PDFPrintFunc)(LPCTSTR lpCommand);

HMODULE	g_hVeryW = NULL;
VeryPDF_PDFPrintFunc	lpVeryPDF_PDFPrint;
void	GetModulePath(char *out_path,char *in_name);
BOOL	LoadVeryWDll(void);
void	FreeVeryWDll();

void GetModulePath(char *out_path,char *in_name)
{
	char *p;
	GetModuleFileName(NULL,out_path,256);
	p =strrchr(out_path,'\\');
	p[1]=0;
	strcat(out_path,in_name);
}
BOOL LoadVeryWDll()
{
	char path[_MAX_PATH];
	GetModulePath(path,"pdfprintsdk.dll");
	g_hVeryW=LoadLibrary(path);
	if(g_hVeryW==NULL)
		goto Failer;

	lpVeryPDF_PDFPrint=(VeryPDF_PDFPrintFunc)GetProcAddress(g_hVeryW,"VeryPDF_PDFPrint");
	if(lpVeryPDF_PDFPrint==NULL)
		goto Failer;

	return TRUE;
Failer:
	FreeVeryWDll(); 
	return FALSE;
}
void FreeVeryWDll()
{
	if(g_hVeryW==NULL)
		return ;
	FreeLibrary(g_hVeryW);
	g_hVeryW=NULL;
}
void TestPDFPrintDLL(char *lpCommand)
{
	if(LoadVeryWDll() == FALSE)
		return;
	if(lpVeryPDF_PDFPrint == NULL)
		return;
	int nRet = lpVeryPDF_PDFPrint(lpCommand);
	FreeVeryWDll();
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
	int nRet = VeryPDF_PDFPrint(szCommandLine);
	printf("\n==============================================================\n");
	printf("Return Value = %d\n",nRet);
	printf("\n==============================================================\n");
}