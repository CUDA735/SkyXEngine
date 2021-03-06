#ifndef __FILE_EXST_ITERATOR_H
#define __FILE_EXST_ITERATOR_H

#include "FileSystem.h"

class CFileExtsIterator final: public IXUnknownImplementation<IFileIterator>
{
private:
    String m_sPath;
    String m_pathStr;

    const char **m_szExts;

    //Количество типов расширений
    int m_extCount = 0;
    //Текущее расширение
    int m_currentExt = 0;

    HANDLE m_handle = nullptr;

public:
    CFileExtsIterator(const char *szPath, const char **szExts, int extArraySize);

    const char* XMETHODCALLTYPE next() override;

    void XMETHODCALLTYPE reset() override;

    ~CFileExtsIterator();
};

#endif