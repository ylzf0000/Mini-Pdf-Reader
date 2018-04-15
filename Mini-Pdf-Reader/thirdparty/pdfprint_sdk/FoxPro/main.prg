*!*	Main

_screen.visible = .F.
_screen.Caption = "Test PDF Verydoc"

ON SHUTDOWN

Declare INTEGER VeryPDF_PDFPrint in pdfprintsdk.dll String strCommandLine

DO FORM pdf_test

READ EVENTS


************************************************************************
* wwAPI :: Createprocess
****************************************
***  Function: Calls the CreateProcess API to run a Windows application
***    Assume: Gets around RUN limitations which has command line
***            length limits and problems with long filenames.
***            Can do everything EXCEPT REDIRECTION TO FILE!
***      Pass: lcExe - Name of the Exe
***            lcCommandLine - Any command line arguments
***    Return: .t. or .f.
************************************************************************
FUNCTION Createprocess(lcExe,lcCommandLine,lnShowWindow,llWaitForCompletion)
LOCAL hProcess, cProcessInfo, cStartupInfo
 
DECLARE INTEGER CreateProcess IN kernel32 as _CreateProcess; 
    STRING   lpApplicationName,; 
    STRING   lpCommandLine,; 
    INTEGER  lpProcessAttributes,; 
    INTEGER  lpThreadAttributes,; 
    INTEGER  bInheritHandles,; 
    INTEGER  dwCreationFlags,; 
    INTEGER  lpEnvironment,; 
    STRING   lpCurrentDirectory,; 
    STRING   lpStartupInfo,; 
    STRING @ lpProcessInformation 
 
 
cProcessinfo = REPLICATE(CHR(0),128)
cStartupInfo = GetStartupInfo(lnShowWindow)
 
IF !EMPTY(lcCommandLine)
   lcCommandLine = ["] + lcExe + [" ]+ lcCommandLine
ELSE
   lcCommandLine = ""
ENDIF
 
lnResult =  _CreateProcess(lcExe,lcCommandLine,0,0,1,0,0,;
                           SYS(5)+CURDIR(),cStartupInfo,@cProcessInfo)
 
lhProcess = CHARTOBIN( SUBSTR(cProcessInfo,1,4) )
 
IF llWaitForCompletion
   #DEFINE WAIT_TIMEOUT 0x00000102
   DECLARE INTEGER WaitForSingleObject IN kernel32.DLL ;
         INTEGER hHandle, INTEGER dwMilliseconds
 
   DO WHILE .T.
       *** Update every 100 milliseconds
       IF WaitForSingleObject(lhProcess, 100) != WAIT_TIMEOUT
          EXIT
        ELSE
           DOEVENTS
        ENDIF
   ENDDO
ENDIF
 
 
DECLARE INTEGER CloseHandle IN kernel32.DLL ;
        INTEGER hObject
 
CloseHandle(lhProcess)
 
RETURN IIF(lnResult=1,.t.,.f.)


FUNCTION getStartupInfo(lnShowWindow)
LOCAL lnFlags
* creates the STARTUP structure to specify main window
* properties if a new window is created for a new process
 
IF EMPTY(lnShowWindow)
  lnShowWindow = 1
ENDIF
  
*| typedef struct _STARTUPINFO {
*| DWORD cb; 4
*| LPTSTR lpReserved; 4
*| LPTSTR lpDesktop; 4
*| LPTSTR lpTitle; 4
*| DWORD dwX; 4
*| DWORD dwY; 4
*| DWORD dwXSize; 4
*| DWORD dwYSize; 4
*| DWORD dwXCountChars; 4
*| DWORD dwYCountChars; 4
*| DWORD dwFillAttribute; 4
*| DWORD dwFlags; 4
*| WORD wShowWindow; 2
*| WORD cbReserved2; 2
*| LPBYTE lpReserved2; 4
*| HANDLE hStdInput; 4
*| HANDLE hStdOutput; 4
*| HANDLE hStdError; 4
*| } STARTUPINFO, *LPSTARTUPINFO; total: 68 bytes
 
#DEFINE STARTF_USESTDHANDLES 0x0100
#DEFINE STARTF_USESHOWWINDOW 1
#DEFINE SW_HIDE 0
#DEFINE SW_SHOWMAXIMIZED 3
#DEFINE SW_SHOWNORMAL 1
 
lnFlags = STARTF_USESHOWWINDOW
 
RETURN binToChar(80) +;
    binToChar(0) + binToChar(0) + binToChar(0) +;
    binToChar(0) + binToChar(0) + binToChar(0) + binToChar(0) +;
    binToChar(0) + binToChar(0) + binToChar(0) +;
    binToChar(lnFlags) +;
    binToWordChar(lnShowWindow) +;
    binToWordChar(0) + binToChar(0) +;
    binToChar(0) + binToChar(0) + binToChar(0) + REPLICATE(CHR(0),30)
 
************************************************************************
FUNCTION CharToBin(lcBinString,llSigned)
****************************************
***  Function: Binary Numeric conversion routine. 
***            Converts DWORD or Unsigned Integer string
***            to Fox numeric integer value.
***      Pass: lcBinString -  String that contains the binary data 
***            llSigned    -  if .T. uses signed conversion
***                           otherwise value is unsigned (DWORD)
***    Return: Fox number
************************************************************************
LOCAL m.i, lnWord
 
lnWord = 0
FOR m.i = 1 TO LEN(lcBinString)
 lnWord = lnWord + (ASC(SUBSTR(lcBinString, m.i, 1)) * (2 ^ (8 * (m.i - 1))))
ENDFOR
 
IF llSigned AND lnWord > 0x80000000
  lnWord = lnWord - 1 - 0xFFFFFFFF
ENDIF
 
RETURN lnWord
*  wwAPI :: CharToBin
 
************************************************************************
FUNCTION BinToChar(lnValue)
****************************************
***  Function: Creates a DWORD value from a number
***      Pass: lnValue - VFP numeric integer (unsigned)
***    Return: binary string
************************************************************************
Local byte(4)
If lnValue < 0
    lnValue = lnValue + 4294967296
EndIf
byte(1) = lnValue % 256
byte(2) = BitRShift(lnValue, 8) % 256
byte(3) = BitRShift(lnValue, 16) % 256
byte(4) = BitRShift(lnValue, 24) % 256
RETURN Chr(byte(1))+Chr(byte(2))+Chr(byte(3))+Chr(byte(4))
*  wwAPI :: BinToChar
 
************************************************************************
FUNCTION BinToWordChar(lnValue)
****************************************
***  Function: Creates a DWORD value from a number
***      Pass: lnValue - VFP numeric integer (unsigned)
***    Return: binary string
************************************************************************
RETURN Chr(MOD(m.lnValue,256)) + CHR(INT(m.lnValue/256))
 
*Some of that code originated from Christof Wollenhaupt with a number of modifications made to support wait operations and easier access to the command line parameters.
 
*To support piping etc. wwIPStuff.dll (part of West Wind Internet Protocols or West Wind Client Tools) includes a wrapper that does something like this:
 
************************************************************************
* wwAPI :: CreateprocessEx
****************************************
***  Function: Calls the CreateProcess API to run a Windows application
***    Assume: Gets around RUN limitations which has command line
***            length limits and problems with long filenames.
***            Can do Redirection
***            Requires wwIPStuff.dll to run!
***      Pass: lcExe - Name of the Exe
***            lcCommandLine - Any command line arguments
***    Return: .t. or .f.
************************************************************************
FUNCTION CreateProcessEx(lcExe,lcCommandLine,lcStartDirectory,;
                         lnShowWindow,llWaitForCompletion,lcStdOutputFilename)
 
DECLARE INTEGER wwCreateProcess IN wwIPStuff.DLL AS _wwCreateProcess  ;
   String lcExe, String lcCommandLine, INTEGER lnShowWindow,;
   INTEGER llWaitForCompletion, STRING lcStartupDirectory, STRING StdOutFile
   
IF EMPTY(lcStdOutputFileName)
  lcStdOutputFileName = NULL
ENDIF
IF EMPTY(lcStartDirectory)
  lcStartDirectory = CHR(0)
ENDIF
 
IF !EMPTY(lcCommandLine)
   lcCommandLine = ["] + lcExe + [" ]+ lcCommandLine
ELSE
   lcCommandLine = ""
ENDIF
 
IF llWaitForCompletion
   lnWait = 1
ELSE
   lnWait = 0
ENDIF
IF EMPTY(lnShowWindow)
   lnShowWindow = 4
ENDIF   
 
lnResult = _wwCreateProcess(lcExe,lcCommandLine,lnShowWindow,lnWait,;
                            lcStartDirectory,lcStdOutputFileName)
   
RETURN IIF(lnResult == 1, .t. , .f.)
ENDFUNC

