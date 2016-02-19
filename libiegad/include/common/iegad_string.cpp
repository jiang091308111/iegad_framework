﻿#include "iegad_string.hpp"
#include <string.h>
#include <sstream>
#ifdef WIN32
#include <codecvt>
#endif // WIN32
#include <iomanip>
#include <boost/uuid/sha1.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/locale.hpp>
#include <cwctype>


const std::vector<std::string>
iegad::string::split_vct(const std::string &src, const std::string & chs)
{
    int pos = 0, len = chs.length(), n = 0, index = 0;
    std::vector<std::string> res;
    while (true) {
        index = src.find(chs, pos);
        if (index == -1) {
            res.push_back(std::string(src, pos, src.length() - pos));
            break;
        }
        n = index - n;
        res.push_back(std::string(src, pos, n));
        pos = index + len;
        n = pos;
    }
    return res;
}


const std::string
iegad::string::substr(const std::string &src, unsigned int pos, int n /*=-1*/)
{
    int len = n < 0 ? src.size() - pos : n;
    std::string restr(src, pos, len);
    return restr;
}


const std::string
iegad::string::substr2(const std::string & src, unsigned int bgn, unsigned int end /*= -1*/)
{
    return std::string(src.begin() + bgn, src.begin() + (end == (unsigned int)(-1) ? src.size() : end + 1));
}


const std::string
iegad::string::rtrim(const std::string &src)
{
    int n = src.length() - 1;
    while (std::isspace(src[n])) {
        n--;
    }
    std::string restr(src, 0, n + 1);
    return restr;
}


const std::string
iegad::string::trim(const std::string &src, char chr)
{
    std::string restr;
    for (int i = 0, n = src.length(); i < n; i++) {
        if (src[i] == chr) {
            continue;
        }
        restr.push_back(src[i]);
    }
    return restr;
}


const std::string 
iegad::string::trim(const std::string & src)
{
    std::string restr;
    for (int i = 0, n = src.length(); i < n; i++) {
        if (std::isspace(src[i])) {
            continue;
        }
        restr.push_back(src[i]);
    }
    return restr;
}


const std::string
iegad::string::ltrim(const std::string &src)
{
    int rpos = 0;
    while (std::isspace(src[rpos])) {
        rpos++;
    }
    std::string restr(src, rpos, src.length() - rpos);
    return restr;
}


const std::string
iegad::string::replace(const std::string &src, const std::string & oldstr, const std::string & newstr)
{
    int pos = 0, len = oldstr.length();
    std::string restr(src);
    while (true) {
        pos = restr.find(oldstr, pos);
        if (pos == -1) {
            break;
        }
        restr.replace(pos, len, newstr);
        pos++;
    }
    return restr;
}


int
iegad::string::fstchr(const std::string &src, char chr)
{
    for (int i = 0, n = src.length(); i < n; i++) {
        if (src[i] == chr) {
            return i;
        }
    }
    return -1;
}


int
iegad::string::lstchr(const std::string &src, char chr)
{
    for (int i = src.length() - 1; i >= 0; i--) {
        if (src[i] == chr) {
            return i;
        }
    }
    return -1;
}


const std::string
iegad::string::to_upr(const std::string &src)
{
    std::string restr(src);
    for (int i = 0, n = restr.length(); i < n; i++) {
        restr[i] = toupper(restr[i]);
    }
    return restr;
}


const std::string
iegad::string::to_lwr(const std::string &src)
{
    std::string restr(src);
    for (int i = 0, n = restr.length(); i < n; i++) {
        restr[i] = tolower(restr[i]);
    }
    return restr;
}


const std::string 
iegad::string::md5(const std::string & src)
{
    iegad::security::MD5 m(src);
    return m.hexdigest();
}

void 
iegad::string::sha1(const std::string & src, std::vector<unsigned int> & digest)
{
    unsigned int temp[5];
    digest.clear();
    boost::uuids::detail::sha1 sha;
    sha.process_bytes(src.c_str(), src.size());
    sha.get_digest(temp);
    for (int i = 0; i < 5; i++) {
        digest.push_back(temp[i]);
    }
}


const std::string 
iegad::string::guid()
{
    boost::uuids::random_generator rgen;
    boost::uuids::uuid u(rgen());
    return boost::uuids::to_string(u);
}


const std::string 
iegad::string::en_cust(const std::string & src, char key)
{
    std::string res;
    for (int i = 0, n = src.size(); i < n; i++) {
	// res.push_back(src[i] ^ key);
	res.push_back(~src[i] + 1);
    }
    return res;
}


const std::string 
iegad::string::de_cust(const std::string & src, char key)
{
    return en_cust(src, key);
}


int 
iegad::string::find_str(const std::string & src, const std::string & substr, int ntime /*= 1*/)
{
    int pos = 0, n = 0, index = 0;
    while (true) {
        pos = src.find(substr, index);
        if (pos == -1 || ++n == ntime) {
            break;
        }
        index = pos + 1;
    }
    return pos;
}


bool 
iegad::string::start_with(const std::string & src, const std::string & substr)
{
    return src.find(substr, 0) == 0;
}


bool 
iegad::string::end_with(const std::string & src, const std::string & substr)
{
    std::string str = src.substr(src.size() - substr.size(), substr.size());
    return str == substr;
}


const std::string 
iegad::string::remove(const std::string & src, unsigned int pos, int n /*= -1*/)
{
    std::string res = src;
    int len = n < 0 ? src.size() : n;
    return res.erase(pos, len);
}


const std::string 
iegad::string::remove2(const std::string & src, unsigned int bgn, unsigned int end /*= -1*/)
{
    std::string res = src;
    end = static_cast<int>(end) == -1 ? res.size() : end;
    res.erase(res.begin() + bgn, res.begin() + end + 1);
    return res;
}



/******************************************************/



const std::vector<std::wstring>
iegad::string::split_vct(const std::wstring &src, const std::wstring &chs)
{
    int pos = 0, len = chs.length(), n = 0, index = 0;
    std::vector<std::wstring> res;
    while (true) {
        index = src.find(chs, pos);
        if (index == -1) {
            res.push_back(std::wstring(src, pos, src.length() - pos));
            break;
        }
        n = index - n;
        res.push_back(std::wstring(src, pos, n));
        pos = index + len;
        n = pos;
    }
    return std::move(res);
}


const std::wstring
iegad::string::substr(const std::wstring &src, unsigned int pos, int n)
{
    int len = n < 0 ? src.size() - pos : n;
    std::wstring restr(src, pos, len);
    return restr;
}


const std::wstring
iegad::string::substr2(const std::wstring &src, unsigned int bgn, unsigned int end)
{
    return std::wstring(src.begin() + bgn,
                        src.begin() + (end == (unsigned int)(-1) ? src.size() : end + 1));
}


const std::wstring
iegad::string::rtrim(const std::wstring &src)
{
    int n = src.length() - 1;
    while (std::iswspace(src[n])) {
        n--;
    }
    std::wstring restr(src, 0, n + 1);
    return restr;
}


const std::wstring
iegad::string::trim(const std::wstring &src)
{
    std::wstring restr;
    for (int i = 0, n = src.length(); i < n; i++) {
        if (std::iswspace(src[i])) {
            continue;
        }
        restr.push_back(src[i]);
    }
    return restr;
}


const std::wstring
iegad::string::trim(const std::wstring &src, wchar_t chr)
{
    std::wstring restr;
    for (int i = 0, n = src.length(); i < n; i++) {
        if (src[i] == chr) {
            continue;
        }
        restr.push_back(src[i]);
    }
    return restr;
}


const std::wstring
iegad::string::ltrim(const std::wstring &src)
{
    int rpos = 0;
    while (std::iswspace(src[rpos])) {
        rpos++;
    }
    std::wstring restr(src, rpos, src.length() - rpos);
    return restr;
}


const std::wstring
iegad::string::replace(const std::wstring &src, const std::wstring &oldstr, const std::wstring &newstr)
{
    int pos = 0, len = oldstr.length();
    std::wstring restr(src);
    while (true) {
        pos = restr.find(oldstr, pos);
        if (pos == -1) {
            break;
        }
        restr.replace(pos, len, newstr);
        pos++;
    }
    return restr;
}


int
iegad::string::fstchr(const std::wstring &src, wchar_t chr)
{
    for (int i = 0, n = src.length(); i < n; i++) {
        if (src[i] == chr) {
            return i;
        }
    }
    return -1;
}


int
iegad::string::lstchr(const std::wstring &src, wchar_t chr)
{
    for (int i = src.length() - 1; i >= 0; i--) {
        if (src[i] == chr) {
            return i;
        }
    }
    return -1;
}


int
iegad::string::find_str(const std::wstring &src, const std::wstring &substr, int ntime)
{
    int pos = 0, n = 0, index = 0;
    while (true) {
        pos = src.find(substr, index);
        if (pos == -1 || ++n == ntime) {
            break;
        }
        index = pos + 1;
    }
    return pos;
}


bool
iegad::string::start_with(const std::wstring &src, const std::wstring &substr)
{
    return src.find(substr, 0) == 0;
}


bool
iegad::string::end_with(const std::wstring &src, const std::wstring &substr)
{
    std::wstring str = src.substr(src.size() - substr.size(), substr.size());
    return str == substr;
}


const std::wstring
iegad::string::remove(const std::wstring &src, unsigned int pos, int n)
{
    std::wstring res = src;
    int len = n < 0 ? src.size() : n;
    return res.erase(pos, len);
}


const std::wstring
iegad::string::remove2(const std::wstring &src, unsigned int bgn, unsigned int end)
{
    std::wstring res = src;
    end = static_cast<int>(end) == -1 ? res.size() : end;
    res.erase(res.begin() + bgn, res.begin() + end + 1);
    return res;
}


const std::wstring
iegad::string::to_upr(const std::wstring &src)
{
    std::wstring restr(src);
    for (int i = 0, n = restr.length(); i < n; i++) {
        restr[i] = std::towupper(restr[i]);
    }
    return restr;
}


const std::wstring
iegad::string::to_lwr(const std::wstring &src)
{
    std::wstring restr(src);
    for (int i = 0, n = restr.length(); i < n; i++) {
        restr[i] = std::towlower(restr[i]);
    }
    return restr;
}


const std::string 
iegad::string::bin_tostr(const char * buff, unsigned int buff_size)
{
    std::string res(buff_size * 2, 0);
    uint8_t temp;

    for (size_t i = 0; i < buff_size; i++) {
	temp = buff[i];
	for (size_t j = 0; j < 2; j++) {
	    uint8_t cCur = (temp & 0x0f);
	    if (cCur < 10) {
		cCur += '0';
	    }
	    else {
		cCur += ('A' - 10);
	    }
	    res[2 * i + 1 - j] = cCur;
	    temp >>= 4;
	}
    }

    return res;
}


const char * 
iegad::string::str_tobin(const std::string & src, char * buff, int & buff_size)
{
    if (src.size() % 2 != 0 || 
	buff == nullptr || 
	static_cast<size_t>(buff_size) < src.size() / 2) {
	return nullptr;
    }

    buff_size = src.size() / 2;
    for (int i = 0; i < buff_size; i++) {
	uint8_t cTemp = 0;
	for (size_t j = 0; j < 2; j++) {
	    char cCur = src[2 * i + j];
	    if (cCur >= '0' && cCur <= '9') {
		cTemp = (cTemp << 4) + (cCur - '0');
	    }
	    /*else if (cCur >= 'a' && cCur <= 'f') {
		cTemp = (cTemp << 4) + (cCur - 'a' + 10);
	    }*/
	    else if (cCur >= 'A' && cCur <= 'F') {
		cTemp = (cTemp << 4) + (cCur - 'A' + 10);
	    }
	    else {
		return nullptr;
	    }
	} // for (size_t j = 0; j < 2; j++);
	buff[i] = cTemp;
    } // for (size_t i = 0; i < buff_size; i++);

    return buff;
}