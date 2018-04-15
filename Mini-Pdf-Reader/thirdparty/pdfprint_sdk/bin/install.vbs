'REM -------------------------------------------
'REM Please run a cmd window by administrator privilege, and then run following command line to register COM component,
'REM -------------------------------------------
'
'  pdfprintcom.exe /regserver
'

strFolder = ExtractFilePath(WScript.ScriptFullName)
strExe = """" & strFolder & "\pdfprintcom.exe" & """"

Set UAC = CreateObject("Shell.Application")
UAC.ShellExecute "cmd.exe", "/c " & strExe & " /regserver", "", "runas", 1

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Function ExtractFilePath(PathName)
   For x = Len(PathName) To 1 Step -1
      If Mid(PathName, x, 1) = "\" Then Exit For
   Next
   ExtractFilePath = Left (PathName, x - 1)
End Function

