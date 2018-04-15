..\bin\testsdk2.exe test-sample.doc
..\bin\testsdk2.exe test-6pages.docx
..\bin\testsdk2.exe test-sample.ppt
..\bin\testsdk2.exe test-sample.pptx

REM "-paper 66" is use the A2 paper size, more paper types can be found from following web page,
REM http://www.verypdf.com/artprint/document-converter/index.htm

..\bin\testsdk2.exe -restoreprinter -paper 66 test-sample.xlsx

..\bin\testsdk2.exe readme.txt

pause
