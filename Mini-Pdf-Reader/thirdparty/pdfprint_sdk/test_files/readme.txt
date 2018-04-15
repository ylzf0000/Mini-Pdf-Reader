D:\>pdfprint.exe
VeryPDF PDFPrint Command Line v3.0
Web: http://www.verypdf.com
Web: http://www.verypdf.com/app/pdf-print-cmd/index.html
Email: support@verypdf.com
Build: Nov  8 2012
-------------------------------------------------------
Description:
Print PDF files to physical printer.
Note:
1. Paper size can be selected either standard papers or user defined papers.
   Look at following page for the standard papers:
   http://www.verypdf.com/artprint/document-converter/index.htm
-------------------------------------------------------
Support following formats:
  PDF Document Format [.pdf]
  OpenOffice Documents [.odt, .ott, .odg, .odp, .ods]
  MS Word Documents [.doc, .docx, .rtf, .txt, .xml]
  MS PowerPoint Documents [.ppt, .pptx, .pps, .ppsx]
  MS Excel Documents [.xls, .xlsx, .xlsm]
  HTML Documents [.htm, .html, .mht, .mhtml]
  Vector Drawing Formats [.wmf, .emf]
  Image Formats [.bmp, .jpg, .jpeg, .tif, .tiff, .gif, .png, .pcx]
  Image Formats [.tga, .jp2, .j2k, .jpc, .jpx, .pbm, .pgm, .ppm, .pnm]
-------------------------------------------------------
Usage: pdfprint.exe [options] [Options] <PDF Files>
  -firstpage <int>             : first page to print, from 1 to max page
  -lastpage <int>              : last page to print, from 1 to max page
  -prompt                      : prompt the user with the print dialog so they can change printer settings and/or select pages manually
  -printer <string>            : printer name to print
  -savedevmode <string>        : prompt the user with print dialog and save the printer settings into a disk file
  -loaddevmode <string>        : restore printer settings which saved by -savedevmode parameter
  -promptdevmode               : prompt the user with print dialog and print the printer settings to screen
  -devmode <string>            : restore printer settings which outputed by -promptdevmode parameter
  -copies <int>                : set number of copies to print
  -setcopyto                   : set '-copies' value to printer instead of print it several times
  -paper <string>              : paper size to printer
    pdf    : retrieve paper size from PDF file
    number : standard paper size
    others : user defined paper size
  -scalex <int>                : X axis scale factors, default is 100
    100 : do not scale PDF page
      0 : scale the width of PDF page to fit the printer's paper size
     -1 : keep the minimum constant scaling in both paper width and height
  -scaley <int>                : Y axis scale factors, default is 100
    100 : do not scale PDF page
      0 : scale the height of PDF page to fit the printer's paper size
     -1 : keep the minimum constant scaling in both paper width and height
  -pdforient <int>             : select the orientation of the show PDF page,
    0 : upright, default
    1 : upside down
    2 : left side down
    3 : right side down
    4 : auto detect orientation for PDF pages
  -orient <int>                : select the orientation of the printer paper,
    1 is portrait (default) and 2 is landscape
  -duplex <int>                : select duplex or double-sided printing for printers capable of duplex printing,
    1 : simplex
    2 : horizontal
    3 : vertical
  -color <int>                 : specify color or monochrome to printer,
    1 : monochrome
    2 : color
  -xres <int>                  : specify the printer x-resolution,
    -4    : high
    -3    : medium
    -2    : low
    -1    : draft
    number: the number of dots per inch (DPI) and is therefore device dependent
  -yres <int>                  : specify the printer y-resolution
  -xoffset <int>               : specify a page offset in the horizontal axis
  -yoffset <int>               : specify a page offset in the vertical axis
  -collate <int>               : specify whether collation should be used when
     printing multiple copies, 0 is disable and 1 is enable
  -scale <int>                 : specify the factor by which the printed output
     is to be scaled, The apparent page size is scaled from the physical page
     size by a factor of scale/100.
  -shell                       : Call default PDF viewer to print PDF file
  -shell2                      : Call default PDF viewer to print PDF file
  -shelltime <int>             : set timeout for shell printing,in milliseconds
  -raster                      : render PDF page to image before printing
  -raster2                     : render PDF page to image before printing
  -raster2center               : center the printout when use -raster2
  -rasterbitcount <int>        : set bitcount for raster image, e.g., 1, 8, 24
  -rasterbwtext                : disable halftone for color text, for -raster2 only
  -preproc                     : process PDF file before printing, useful for some damaged PDF files
  -printtofile <string>        : save print spooling data to a disk file
  -mergeprintjobs              : combine all print jobs into one print job
  -listprinter                 : list printers in system
  -listbins                    : list bins/trays of a printer
  -listjobs                    : list print jobs in printer's queue
  -listall                     : list printers, ports, monitors etc.
  -chgbin <int>                : change bin/tray for printer by number
  -papersource <string>        : change bin/tray for printer by name
  -settraytopclfile <string>   : set tray to PCL file directly, only work when '-papersource' used
  -winfont                     : use Windows fonts to instead of embedded fonts
  -winfont2                    : force to use Windows fonts to instead of all embedded fonts
  -useembedfont                : use embedded fonts from PDF file
  -useunicode <int>            : enable or disable unicode conversion for PDF printing
  -antifonts                   : enable anti-aliased font bitmaps for emulated fonts
  -nochgprinter                : don't change default printer during printing
  -restoreprinter              : restore original settings to printer after printing
  -printermargins              : reduce to printer margins when printing
  -checkjobstatus              : check status for print jobs
  -checkjobtime <int>          : delay some time before check status for print jobs, in millisecond
  -nodelfailjobs               : don't delete failed print jobs
  -movetotop                   : move print area to top if printer paper not same as PDF paper, default is 'center'
  -openpassword <string>       : set open password to PDF file
  -ispasswordprotected         : check if a PDF file protected by 'open password' or not
  -getpagecount                : read page count from input PDF file
  -jobusername <string>        : specify the name of the user who owns the print job
  -jobdocname <string>         : specify document name of print job
  -ownerservicename <string>   : specify the name of OwnerService on Windows Server 2008
  -useownerservice             : force to use owner service for all systems
  -deleteownerservice <string> : remove the OwnerService from Windows
  -silent                      : print PDF files silently
  -timeout <int>               : specify a timeout to avoid hanging pdfprint process, in millisecond
  -wtext <string>              : watermark on printed document
  -wtype <int>                 : type of watermark
    0 : normal watermark
    1 : watermark on header
    2 : watermark on footer
  -wf <string>                 : font name of watermark
  -wh <int>                    : font height of watermark
  -ww <int>                    : font width of watermark
  -wb                          : specify bold font
  -wi                          : specify an italic font
  -wu                          : specify an underlined font
  -ws                          : specify a strikeout font
  -wo <int>                    : opacity of watermark, from 0 to 100
  -wa <int>                    : angle of watermark
  -wc <string>                 : color of watermark,
    FF0000: Red color
    00FF00: Green color
    0000FF: Blue color
    HexNum: Other colors
  -wx <int>                    : X offset of watermark
  -wy <int>                    : Y offset of watermark
  -quiet                       : don't print any message on screen
  -debug                       : print out debug messages
  -clickpopup                  : click 'Retry' button on 'Xerox Printer' automatically
  -watermarkfile <string>      : a .ini file which contain information for multiple watermarks
  -$ <string>                  : Input registration key
Example:
   pdfprint.exe -printer "PDFcamp Printer" -copies 3 -paper 9 C:\input.pdf
   pdfprint.exe -printer "PDFcamp Printer" -paper "pdf" C:\input.pdf
   pdfprint.exe -printer "PDFcamp Printer" -paper "11x17in" C:\input.pdf
   pdfprint.exe -printer "PDFcamp Printer" -paper "215.9x279.4mm" C:\input.pdf
   pdfprint.exe -printer "PDFcamp Printer" -paper "612x792pt" C:\input.pdf
   pdfprint.exe -printer "docPrint" -paper "612x792pt" -orient 1 C:\input.pdf
   pdfprint.exe -printer "docPrint" -paper "612x792pt" -orient 2 C:\input.pdf
   pdfprint.exe -printer "docPrint" -paper "11x14in" -pdforient 3 C:\input.pdf
   pdfprint.exe -printer "docPrint" -firstpage 1 -lastpage 1 C:\input.pdf
   pdfprint.exe -prompt C:\input.pdf
   pdfprint.exe -firstpage -1 -lastpage -1 C:\lastpage.pdf
   pdfprint.exe -scalex 50 -scaley 50 C:\input.pdf
   pdfprint.exe -scalex 0 -scaley 0 C:\input.pdf
   pdfprint.exe -scalex -1 -scaley -1 C:\input.pdf
   pdfprint.exe -duplex 3 C:\input.pdf
   pdfprint.exe -color 1 C:\input.pdf
   pdfprint.exe -xres 600 -yres 600 C:\input.pdf
   pdfprint.exe -xres -4 C:\input.pdf
   pdfprint.exe -xoffset 200 -yoffset 200 C:\input.pdf
   pdfprint.exe -scale 50 C:\input.pdf
   pdfprint.exe -shell -shelltime 5000 C:\input.pdf
   pdfprint.exe -raster C:\input.pdf
   pdfprint.exe -raster2 -rasterbitcount 1 C:\input.pdf
   pdfprint.exe -raster2 -rasterbwtext -rasterbitcount 1 -xres 600 -yres 600 C:\input.pdf
   pdfprint.exe -raster2 -raster2center -printermargins C:\input.pdf
   pdfprint.exe -shell C:\input.pdf
   pdfprint.exe -shell2 C:\input.pdf
   pdfprint.exe -preproc C:\input.pdf
   pdfprint.exe -printermargins C:\input.pdf
   pdfprint.exe -nochgprinter -printer "docPrint" C:\input.pdf
   pdfprint.exe -mergeprintjobs -copies 3 C:\input.pdf
   pdfprint.exe -mergeprintjobs C:\*.pdf
   pdfprint.exe -mergeprintjobs C:\test*.pdf
   pdfprint.exe -mergeprintjobs C:\files.txt
   pdfprint.exe C:\files.txt
   pdfprint.exe -printtofile C:\out.pcl -printer "HP PCL Printer" C:\input.pdf
   pdfprint.exe -listprinter
   pdfprint.exe -listjobs -printer "docPrint"
   pdfprint.exe -listall
   pdfprint.exe -listbins -printer "docPrint"
   pdfprint.exe -chgbin 15 -printer "docPrint" C:\input.pdf
   pdfprint.exe -papersource "auto" -printer "docPrint" C:\input.pdf
   pdfprint.exe -papersource "Tray 1" -printer "docPrint" C:\input.pdf
   pdfprint.exe -papersource "Manual Feed" -printer "docPrint" C:\input.pdf
   pdfprint.exe -papersource "Media Tray" -printer "docPrint" C:\input.pdf
   pdfprint.exe -papersource "Tray 3" -settraytopclfile C:\test.pcl
   pdfprint.exe -getpagecount C:\input.pdf
   pdfprint.exe -jobusername TestUser C:\input.pdf
   pdfprint.exe -savedevmode C:\file.dat -printer "VeryPDF PCL Writer"
   pdfprint.exe -loaddevmode C:\file.dat -printer "VeryPDF PCL Writer" C:\input.pdf
   pdfprint.exe -jobdocname "test.doc" -jobusername "MyName" C:\input.pdf
   pdfprint.exe -useownerservice -jobdocname "test.doc" -jobusername "MyName" C:\input.pdf
   pdfprint.exe -winfont -winfont2 C:\input.pdf

Watermark options during printing:
   pdfprint.exe -wtext "Watermark" C:\input.pdf
   pdfprint.exe -wtext "Watermark" -wtype 1 C:\input.pdf
   pdfprint.exe -wtext "Watermark" -wf "Arial" C:\input.pdf
   pdfprint.exe -wtext "Watermark" -wh 200 C:\input.pdf
   pdfprint.exe -wtext "Watermark" -wb -wi -wu -ws C:\input.pdf
   pdfprint.exe -wtext "Watermark" -wo 80 C:\input.pdf
   pdfprint.exe -wtext "Watermark" -wo 80 -wa 75 C:\input.pdf
   pdfprint.exe -wtext "Watermark" -wc "FF0000" C:\input.pdf
   pdfprint.exe -wtext "Watermark" -wc "00FF00" C:\input.pdf
   pdfprint.exe -wtext "Watermark" -wc "0000FF" C:\input.pdf
   pdfprint.exe -wtext "Watermark" -wx 100 -wy 100 C:\input.pdf

Print WMF and EMF files with vector information:
   pdfprint.exe C:\input.wmf
   pdfprint.exe C:\input.emf

Print Raster Image formats:
   pdfprint.exe C:\input.bmp
   pdfprint.exe C:\input.jpg
   pdfprint.exe C:\input.tif
   pdfprint.exe C:\input.gif
   pdfprint.exe C:\input.png
   pdfprint.exe C:\input.pcx
   pdfprint.exe C:\input.tga
   pdfprint.exe C:\input.jp2
   pdfprint.exe C:\input.j2k
   pdfprint.exe C:\input.pnm

Print multipage TIFF file format:
   pdfprint.exe C:\multipage.tif

Print MS Office, TXT, HTML files:
   pdfprint.exe C:\test.odt
   pdfprint.exe C:\test.ott
   pdfprint.exe C:\test.doc
   pdfprint.exe C:\test.docx
   pdfprint.exe C:\test.ppt
   pdfprint.exe C:\test.pptx
   pdfprint.exe C:\test.pps
   pdfprint.exe C:\test.ppsx
   pdfprint.exe C:\test.xls
   pdfprint.exe C:\test.xlsx
   pdfprint.exe C:\test.rtf
   pdfprint.exe C:\test.txt
   pdfprint.exe C:\test.html
   pdfprint.exe C:\test.mhtml
   pdfprint.exe C:\test.xml
