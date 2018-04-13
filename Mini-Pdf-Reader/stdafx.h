#ifndef STDAFX_H
#define STDAFX_H
#ifdef _WIN32
#pragma execution_character_set("UTF-8")
#endif

#if defined(__cplusplus)
    #include <QtCore>
    #include <QtGui>
    #include <algorithm>
//    #include "expdef.h"
//    #include "exptype.h"
    #include "program.h"
#endif

#ifndef _WIN32
    #error Win32 compiler required.
#endif

#endif // STDAFX_H
