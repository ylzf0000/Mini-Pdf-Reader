'please run "64bit-com-install.bat" to register pdfprintcom.exe first

Set pdfcom = CreateObject("pdfprintcom.pdfprint")
nRet = pdfcom.com_PDFPrint("pdfprint D:\temp\1234.pdf")
