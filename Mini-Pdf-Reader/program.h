#ifndef PROGRAM_H
#define PROGRAM_H
#include "stdafx.h"

#include <QWidget>
#include <ctime>
#include <functional>
#include <QMessageBox>

#define BEGIN   {
#define END     }
template <class T>
inline T d(const T &val)
{
    return val;
}

inline QString d(const std::string &val)
{
    return QString::fromStdString(val);
}

inline QString d(const std::wstring &val)
{
    return QString::fromStdWString(val);
}

inline const char *bts(bool b)
{
    return b ? "true" : "false";
}

inline void varTypeError(const QString &variable, const QString &type)
{
	qDebug() << QString("%1 is not %2 type").arg(variable).arg(type);
//    QMessageBox::critical(nullptr, QObject::tr("%1 Error").arg(variable), QString("%1 is not %2 type").arg(variable).arg(type));
}

template <typename T>
inline void onDebugVariable(const QString &name, const T &val)
{
    qDebug() << name << ": " << d(val);
}

template <typename T>
inline void onDebugVariable(const QString &name, const T &val, const QString &funcName)
{
    qDebug() << funcName << ". " << name << ": " << d(val);
}

inline void onDebugFunc(QString name)
{
	qDebug() << name;
}

inline void onDebugError(QString name, int code, const char *desc)
{
    qDebug() << QString("[%1] code : %2, desc : %3").arg(name).arg(code).arg(desc);
//    QMessageBox::critical(nullptr, QObject::tr("%1 Error").arg(name), QString("code : %1, desc : %2").arg(code).arg(desc));
}

inline int onGetElementReturn(const char *funcName, int ret)
{
	if (ret)
	{
		qDebug() << QString("On %1 Error! RetCode = %2").arg(funcName).arg(ret);
//        QMessageBox::critical(nullptr, QObject::tr("%1 Error").arg(funcName), QString("%1 Error! RetCode = %2").arg(funcName).arg(ret));
	}
	return ret;
}

inline void popErrorMsg(const QString &title, const QString &content)
{
    QMessageBox::critical(nullptr, title, content);
}

#define VAR_NAME(x)             (#x)
#define DEBUG_VAR(x)			onDebugVariable(#x, x, __func__)
#define DEBUG_FUNC				onDebugFunc(__func__)
#define DEBUG_ERROR				onDebugError(__func__, code, desc)
#define POP_ERROR(txt)          popErrorMsg(__func__, txt);
#define ON_INVOKE(func, ...)	onGetElementReturn(#func, func(__VA_ARGS__))

#define GET_ELEMENT(func, handle, p_str)        {       \
    char buf[MAXLENBUFFER];                             \
    uint32_t len = MAXLENBUFFER;                        \
    int ret = ON_INVOKE(func, handle, buf, &len);       \
    if(!ret)                                            \
    {                                                   \
        *p_str = QString::fromUtf8(buf, len);           \
    }                                                   \
}

using GetElementFuncType = int(void*, char*, uint32_t*);

template <int MAXLEN = MAXLENBUFFER>
void GetElement(GetElementFuncType func, const char *funcName, void *handle, QString *pStr)
{
    char buf[MAXLEN];
    uint32_t len = MAXLEN;
    int ret = onGetElementReturn(funcName, func(handle, buf, &len));
    if(!ret)
    {
        *pStr = QString::fromUtf8(buf, len);
    }
}

template <class T>
inline void SqlError(const T &sql, const QString &funcName)
{
    QMessageBox::critical(nullptr, QObject::tr("%1 Error").arg(funcName),
                      sql.lastError().text());
}

#define SQL_ERROR(sql)                                                      \
    QMessageBox::critical(nullptr, QObject::tr("%1 Error").arg(__func__),   \
                      sql.lastError().text())

#define ListenCallBack(prcClassName)    \
    prc = new prcClassName(bytes);      \
    prc->UnMarshal();                   \
    On##prcClassName(prc);

#define PrcDynamicCast(prcClassName)                            \
    prcClassName *castPrc = dynamic_cast<prcClassName*>(prc);   \
    if(castPrc == nullptr) return;

inline QString GetCacheDirName()
{
    return "/Cache/";
}

inline QString GetPicCacheDirName()
{
    return "/TimPath/PicCache/";
}

inline bool IsDirExist(const QString &dir)
{
    return QDir(dir).exists();
}

inline bool GenDir(const QString &dir)
{
    return QDir().mkdir(dir);
}

inline bool GenCacheDir()
{
    if(!IsDirExist(QDir::currentPath() + GetCacheDirName()))
        return GenDir(QDir::currentPath() + GetCacheDirName());
    return true;
}

template <typename T, typename T2>
inline T Range(T2 v, const T &left, const T &right)
{
    if(v < left)
        v = left;
    else if (right < v)
        v = right;
    return v;
}

template <class T>
inline int GetArraySize(const T& array)
{
    return sizeof(array) / sizeof(array[0]);
}
bool QCopyFile(const QString &src, const QString &des, bool cover = true);
QRect GetRectFrom2Point(const QPoint &p1, const QPoint &p2);
QRect InterSection2Rect(const QRect &r1, const QRect &r2);
QString UuidToStringEx();
time_t GetTime();
void SetWidgetCentral(QWidget *w);

#endif // PROGRAM_H
