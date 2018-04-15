VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3090
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3090
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "Test PDFPrint SDK Function"
      Height          =   1575
      Left            =   600
      TabIndex        =   0
      Top             =   720
      Width           =   3495
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Declare Function VeryPDF_PDFPrint Lib "pdfprintsdk.dll" (ByVal strCommandLine As String) As Long

Private Sub Command1_Click()
    Dim nRet As Long
    Dim strCmd As String
    
    strCmd = "pdfprint -$ XXXXXXXXXXXXXXXXXXXX"
    strCmd = strCmd & " -printer ""docPrint"""
    strCmd = strCmd & " """ & App.Path & "\readme.pdf"""
    
    MsgBox (strCmd)
    nRet = VeryPDF_PDFPrint(strCmd)
    MsgBox (Str(nRet))
End Sub
