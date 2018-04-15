using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using pdfprintcom;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            pdfprintcom.pdfprint pdfPrintObj = new pdfprintcom.pdfprint();
            pdfPrintObj.com_PDFPrint("pdfprint -printer \"docPrint\" D:\\temp\\5.pdf");
        }
    }
}
