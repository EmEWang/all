#pragma once


#include <iconv.h>
#include <string>
#include <string.h>

inline bool code_convert(const char* from_charset, const char* to_charset, const char* inbuf, size_t inlen, char* outbuf, size_t outlen)
{
    char** pin = (char**)&inbuf;
    char** pout = &outbuf;
    bool ret = false;
    // iconv_open 返回一个新申请的字符集转换的描述符，转换字符序列从编码fromcode到编码tocode。出错时返回(iconv_t)-1
    // 转换描述符包含转换状态，调用iconv_open创建以后，转换状态处于初始状态，调用iconv函数以后改变转换描述符的转换状态，
    //  (意味着转换描述符不能在多线程中同时使用)
    // https://www.gnu.org/software/libiconv/documentation/libiconv-1.13/iconv_open.3.html
    // Chinese  EUC−CN, HZ, GBK, CP936, GB18030, EUC−TW, BIG5, CP950, BIG5−HKSCS, BIG5−HKSCS:2001,
    //  BIG5−HKSCS:1999, ISO−2022−CN, ISO−2022−CN−EXT
    // Unicode  UTF−8, UTF−7, UTF−16, UTF−16BE, UTF−16LE, UTF−32, UTF−32BE, UTF−32LE
    //  UCS−2, UCS−2BE, UCS−2LE, UCS−4, UCS−4BE, UCS−4LE
    iconv_t cd = iconv_open(to_charset, from_charset);
    if (cd == 0)
        return false;
    memset(outbuf, 0, outlen);
    // 此函数从inbuf中读取字符,转换后输出到outbuf中,inbytesleft(参数3) 用以记录还未转换的字符数,
    //  outbytesleft(参数5) 用以记录输出缓冲的剩余空间。
    size_t sss = iconv(cd, pin, &inlen, pout, &outlen);
    size_t ss2 = (size_t)-1;
    if (sss != (size_t)-1)
        ret = true;
    iconv_close(cd);
    return ret;
}

inline bool UnicodeToANSI(const wchar_t* pwcSource, std::string& strDestination)
{
    size_t srcLen = wcslen(pwcSource) * 2;
    size_t destLen = srcLen * 2;

    char* destBuf = new char[destLen + 2];
    if (destBuf == NULL)
        return false;
    memset(destBuf, 0, destLen + 2);

    bool bret = code_convert("gbk//IGNORE", "utf-16", (const char*)pwcSource, srcLen, destBuf, destLen);
    if (bret) {
        strDestination = destBuf;
    }
    delete[] destBuf;
    return bret;
}

inline bool UnicodeToUTF8(const wchar_t* pwcSource, std::string& strDestination)
{
    size_t srcLen = wcslen(pwcSource) * sizeof(wchar_t);
    size_t destLen = srcLen * 2;

    char* destBuf = new char[destLen + sizeof(wchar_t)];
    if (destBuf == NULL)
        return false;
    memset(destBuf, 0, destLen + sizeof(wchar_t));

    bool bret = code_convert("gbk//IGNORE", "utf-8", (const char*)pwcSource, srcLen, destBuf, destLen);
    if (bret) {
        strDestination = destBuf;
    }
    delete[] destBuf;
    return bret;
}

inline bool ANSIToUnicode(const char* pcSource, std::wstring& wstrDestination)
{
    size_t srcLen = strlen(pcSource);
    size_t destLen = srcLen * 2;

    char* destBuf = new char[destLen + 2];
    if (destBuf == NULL)
        return false;
    memset(destBuf, 0, destLen + 2);

    bool bret = code_convert("ansi//IGNORE", "utf-16", pcSource, srcLen, destBuf, destLen);
    if (bret) {
        wstrDestination = (wchar_t*)destBuf;
    }
    delete[] destBuf;
    return bret;
}

inline bool UTF8ToUnicode(const char* pcSource, std::wstring& wstrDestination)
{
    size_t srcLen = strlen(pcSource);
    size_t destLen = srcLen * 2;

    char* destBuf = new char[destLen + 2];
    if (destBuf == NULL)
        return false;
    memset(destBuf, 0, destLen + 2);

    bool bret = code_convert("utf-8//IGNORE", "utf-16", pcSource, srcLen, destBuf, destLen);
    if (bret) {
        wstrDestination = (wchar_t*)destBuf;
    }
    delete[] destBuf;
    return bret;
}

inline bool ANSIToUTF8(const char* pcSource, std::string& strDestination)
{
    size_t srcLen = strlen(pcSource);
    size_t destLen = srcLen * 2;

    char* destBuf = new char[destLen + 2];
    if (destBuf == NULL)
        return false;
    memset(destBuf, 0, destLen + 2);

    //bool bret = code_convert("gbk//IGNORE", "utf-8", pcSource, srcLen, destBuf, destLen);
    bool bret = code_convert("gbk", "utf-8", pcSource, srcLen, destBuf, destLen);
    if (bret) {
        strDestination = destBuf;
    }
    delete[] destBuf;
    return bret;
}

inline bool UTF8ToANSI(const char* pcSource, int srcLen, std::string& strDestination)
{
    size_t destLen = srcLen * 2;

    char* destBuf = new char[destLen + 2];
    if (destBuf == NULL)
        return false;
    memset(destBuf, 0, destLen + 2);

    bool bret = code_convert("utf-8", "gbk", pcSource, srcLen, destBuf, destLen);
    if (bret) {
        strDestination = destBuf;
    }
    delete[] destBuf;
    return bret;
}

inline bool UTF8ToANSI(const char* pcSource, std::string& strDestination)
{
    size_t srcLen = strlen(pcSource);
    return UTF8ToANSI(pcSource, srcLen, strDestination);
}


bool UTF8ToANSI2(const char* pcSource, int nInLen, std::string& strDestination)
{
    if (pcSource == NULL)
    {
        return false;
    }

    int srcLen = nInLen;// strlen(pcSource);
    size_t destLen = srcLen * 2;

    char* destBuf = new char[destLen + 2];
    if (destBuf == NULL)
        return false;
    memset(destBuf, 0, destLen + 2);

    bool bret = code_convert("utf-8", "gbk", pcSource, srcLen, destBuf, destLen);
    if (bret) {
        strDestination = destBuf;
    }
    delete[] destBuf;
    return bret;
}