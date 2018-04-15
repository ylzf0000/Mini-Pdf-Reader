using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;

namespace WindowsApplication1
{
    public partial class Form1 : Form
    {
        private static string LicenseKey = null;
        private static string PrintCommandTemplate = "pdfprint -$ \"[LicenseKey]\" -printer \"<PrinterName>\" \"<DocFullPath>\"";

        public Form1()
        {
            InitializeComponent();
        }

        [DllImport("pdfprintsdk.dll")]
        public static extern int VeryPDF_PDFPrint(string CommandLine);

        public static long PrintDoc(string FullDocumentName, string PrinterName)
        {
            string PrintCommand = PrintCommandTemplate;
            if (LicenseKey != null)
                PrintCommand = PrintCommand.Replace("[LicenseKey]", LicenseKey);
            else
                PrintCommand = PrintCommand.Replace("[LicenseKey]", "XXXXXXXXXXXXXXXX");
            PrintCommand = PrintCommand.Replace("<PrinterName>", PrinterName).Replace("<DocFullPath>", FullDocumentName);

            MessageBox.Show(PrintCommand);
            return VeryPDF_PDFPrint(PrintCommand);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string appPath = Path.GetDirectoryName(Application.ExecutablePath);
            string strPDFFile = (appPath + "\\readme.pdf");
            long nRet = PrintDoc(strPDFFile, "docPrint");
            MessageBox.Show(nRet.ToString());
        }
    }
}