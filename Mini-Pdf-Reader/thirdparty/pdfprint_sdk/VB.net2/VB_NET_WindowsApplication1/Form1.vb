Public Class Form1

    Private Declare Function VeryPDF_PDFPrint Lib "pdfprintsdk.dll" (ByVal strCommandLine As String) As Integer

    Private Sub PDFPrintSDK_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PDFPrintSDK.Click
        Dim strCmd As String

        strCmd = "pdfprint -$ XXXXXXXXXXXXXXXXXXXX"
        strCmd = strCmd & " -printer ""docPrint"""
        strCmd = strCmd & " """ & Application.StartupPath() & "\readme.pdf"""
        MsgBox(strCmd)
        VeryPDF_PDFPrint(strCmd)
    End Sub
End Class
