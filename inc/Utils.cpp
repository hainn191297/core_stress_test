/*
* Utils.cpp
*
*  Created on: Jun 22, 2016
*      Author: cuongtv
*/

#include "Utils.h"
#include <boost/xpressive/xpressive.hpp>
#include "boost/archive/iterators/base64_from_binary.hpp"
#include "boost/archive/iterators/binary_from_base64.hpp"
#include "boost/archive/iterators/transform_width.hpp"
#include <boost/algorithm/string.hpp>
#include <list>
#include <string>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <chrono>
// #include <boost/uuid/sha1.hpp>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>
#include <fstream>
#include <boost/algorithm/hex.hpp>

using namespace std;
using namespace boost::filesystem;
using namespace boost::algorithm;
using namespace boost::xpressive;
using namespace boost::archive::iterators;

#include <glog/logging.h>

string Utils::generate_code(int len)
{
    const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string code = "";
    if (len <= 0 || len >= 32) return code;

    srand(time(NULL));

    for (int i = 0; i < len; i++)
    {
        code += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return code;
}

string Utils::pack_uuid(const uuid_t &uuid)
{
    uuid_t out;
    out[0] = uuid[6];
    out[1] = uuid[7];

    out[2] = uuid[4];
    out[3] = uuid[5];

    out[4] = uuid[0];
    out[5] = uuid[1];
    out[6] = uuid[2];
    out[7] = uuid[3];
    memcpy(out + 8, uuid + 8, 8);
    return string((char*) out, 16);
}

/*
 * Generate session ID using UUID
 */
string Utils::uuid_encode(string id)
{
    const char* _keyStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_=";
    unsigned char* input = (unsigned char*) id.c_str();
    unsigned char output[32];
    uint chr1, chr2, chr3, enc1, enc2, enc3, enc4;
    int i = 0;
    int j = 0;

    while (i < 16)
    {
        chr1 = input[i++];
        enc1 = chr1 >> 2;
        output[j++] = _keyStr[enc1];

        if (i < 16)
        {
            chr2 = input[i++];
            enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);
            output[j++] = _keyStr[enc2];
        }
        else
        {
            output[j++] = _keyStr[(chr1 & 3) << 4];
            break;
        }

        if (i < 16)
        {
            chr3 = input[i++];
            enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);
            output[j++] = _keyStr[enc3];
        }
        else
        {
            output[j++] = _keyStr[(chr2 & 15) << 2];
            break;
        }

        enc4 = chr3 & 63;
        output[j++] = _keyStr[enc4];
    }

    return string((char*) output, j);
}

string Utils::uuid_decode(string id)
{
    const char* _keyStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_=";
    unsigned char output[32];
    uint chr1, chr2, chr3;
    uint enc1, enc2, enc3, enc4;
    unsigned int i = 0;
    unsigned int j = 0;
    string input = id + "==";

    while (i < input.size())
    {
        enc1 = (std::strchr(_keyStr, input[i++]) - _keyStr);
        enc2 = (std::strchr(_keyStr, input[i++]) - _keyStr);
        enc3 = (std::strchr(_keyStr, input[i++]) - _keyStr);
        enc4 = (std::strchr(_keyStr, input[i++]) - _keyStr);

        chr1 = (enc1 << 2) | (enc2 >> 4);
        chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);
        chr3 = ((enc3 & 3) << 6) | enc4;

        output[j++] = chr1;

        if (enc3 != 64)
        {
            output[j++] = chr2;
        }
        else break;
        if (enc4 != 64)
        {
            output[j++] = chr3;
        }
        else break;
    }
    return string((char*) output, j);
}

string Utils::generate_uuid()
{
    uuid_t uuid;
    uuid_generate_time(uuid);
    return Utils::pack_uuid(uuid);
}

string Utils::generate_text_uuid()
{
    uuid_t uuid;
    uuid_generate_time(uuid);
    string input((char*) uuid, 16);
    return uuid_encode(input);
}

string Utils::generate_session_id()
{
    uuid_t uuid;
    uuid_generate_time(uuid);
    string input((char*) uuid, 16);
    return uuid_encode(input);
}

bool Utils::normalize_string(string &str)
{
    trim(str);
    if (str.empty()) return false;
    return true;
}

bool Utils::normalize_email(string &str)
{
    trim(str);
    if (str.empty()) return false;
    return true;
}

bool Utils::normalize_tel(string &str)
{
    trim(str);
    if (str.empty()) return false;
    return true;
}

bool Utils::check_password(string str)
{
	trim(str);
	if (str.empty()) return false;
    return true;
}

string Utils::peer_chat_key(string user1_id, string user2_id)
{
    if (user1_id > user2_id) return (user1_id + user2_id);
    else return (user2_id + user1_id);
}

bool Utils::make_directory(string path)
{
    if(!exists(path))
    {
        if(!create_directory(path)) return false;
    }
    else
    {
        if(!is_directory(path)) return false;
    }
    return true;
}

std::string Utils::generate_uuid1()
{
    unsigned char buf[16];
    uint64_t u = time(nullptr);
    buf[7] = (u & 0xFF);
    u >>= 8;
    buf[6] = (u & 0xFF);
    u >>= 8;
    buf[5] = (u & 0xFF);
    u >>= 8;
    buf[4] = (u & 0xFF);
    u >>= 8;
    buf[3] = (u & 0xFF);
    u >>= 8;
    buf[2] = (u & 0xFF);
    u >>= 8;
    buf[1] = (u & 0xFF);
    u >>= 8;
    buf[0] = (u & 0xFF);
    u >>= 8;

    uint64_t l = 0;
    if(l == 0) l = rand();

    buf[15] = (l & 0xFF);
    l >>= 8;
    buf[14] = (l & 0xFF);
    l >>= 8;
    buf[13] = (l & 0xFF);
    l >>= 8;
    buf[12] = (l & 0xFF);
    l >>= 8;
    buf[11] = (l & 0xFF);
    l >>= 8;
    buf[10] = (l & 0xFF);
    l >>= 8;
    buf[9] = (l & 0xFF);
    l >>= 8;
    buf[8] = (l & 0xFF);
    l >>= 8;

    string t = string((char*)buf,16);
    return t;
}

bool Utils::validate_token(string token)
{
	trim(token);
	if (token.empty()) return false;
    return true;
}

uint64_t Utils::time_t()
{
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

uint64_t Utils::time_seconds_t()
{
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
}

string Utils::hex_sha1(string text)
{
    // const char* const lut = "0123456789ABCDEF";
    // boost::uuids::detail::sha1 s;
    // char hash[20];
    // s.process_bytes(text.c_str(), text.size());
    // unsigned int digest[5];
    // s.get_digest(digest);
    // for(int i = 0; i < 5; ++i)
    // {
    //     const char* tmp = reinterpret_cast<char*>(digest);
    //     hash[i*4] = tmp[i*4+3];
    //     hash[i*4+1] = tmp[i*4+2];
    //     hash[i*4+2] = tmp[i*4+1];
    //     hash[i*4+3] = tmp[i*4];
    // }
    string output;
    // for(int i = 0; i < 20; ++i)
    // {
    //     unsigned char c = hash[i];
    //     output.push_back(lut[c >> 4]);
    //     output.push_back(lut[c & 15]);
    // }
    // boost::algorithm::to_lower(output);
    return output;
}

size_t Utils::curlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size*nmemb;
    size_t oldLength = s->size();
    try
    {
        s->resize(oldLength + newLength);
    }
    catch(std::bad_alloc &e)
    {
        //handle memory problem
        return 0;
    }

    std::copy((char*)contents,(char*)contents+newLength,s->begin()+oldLength);
    return size*nmemb;
}

size_t Utils::header_callback (void * pData, size_t tSize, size_t tCount, void * pmUser)
{
    size_t length = tSize * tCount, index = 0;
    while (index < length)
    {
        unsigned char *temp = (unsigned char *)pData + index;
        if ((temp[0] == '\r') || (temp[0] == '\n'))
            break;
        index++;
    }

    std::string str((unsigned char*)pData, (unsigned char*)pData + index);
    std::map<std::string, std::string>* pmHeader = (std::map<std::string, std::string>*)pmUser;
    size_t pos = str.find(": ");
    if (pos != std::string::npos)
        pmHeader->insert(std::pair<std::string, std::string> (str.substr(0, pos), str.substr(pos + 2)));
    return (tCount);
}

string Utils::getPeerName(int fd)
{
    // get ip address from this connection
    socklen_t len;
    struct sockaddr_storage addr;
    char ipstr[INET6_ADDRSTRLEN];
    memset(ipstr, 0, sizeof(ipstr));
    len = sizeof addr;
    getpeername(fd, (struct sockaddr*)&addr, &len);

    // deal with both IPv4 and IPv6:
    if (addr.ss_family == AF_INET) {
        struct sockaddr_in *s = (struct sockaddr_in *)&addr;
        inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
    }
    else
    { // AF_INET6
        struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
        inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
    }
    //string peername(ipstr);
    std::stringstream myStreamString;
    myStreamString << ipstr;
    std::string myString = myStreamString.str();
    //return peername;
    return myString;
}

string Utils::CreateMD5(const string &value)
{
    unsigned char buff[MD5_DIGEST_LENGTH];
    MD5_CTX stMD5;
    MD5_Init(&stMD5);
    MD5_Update(&stMD5, value.c_str(), value.length());
    MD5_Final(buff, &stMD5);
    string ret((char*)buff, MD5_DIGEST_LENGTH);
    return ret;
}

int Utils::LoadJsonFromFile(const string &strFile, cppcms::json::value &jValue)
{
    std::ifstream ifStream(strFile.c_str());
    if (!jValue.load(ifStream, true))
    {
        ifStream.close();
        return -1;
    }
    
    ifStream.close();
    return 0;
}

string Utils::ParseKeyFromPem( std::string strPathPem)
{
    string strKey = "";
    string strLine = "";
    string strBeginSearch = "-----BEGIN";
    string strSearchLast = "-----";
    string strEndSearch = "-----END";
    string strCRLF = "\r\n";
    ifstream ifFile(strPathPem.c_str());
    bool bIsKey = false;
    if (ifFile)
    {
        while (getline(ifFile, strLine))
        {
            int iFoundBegin1 = strLine.find(strBeginSearch);
            int iFoundBegin2 = strLine.find(strSearchLast, strLine.size() - strSearchLast.size()) ;
            int iFoundEnd1 = strLine.find(strEndSearch);
            int iFoundEnd2 = strLine.find(strSearchLast, strLine.size() - strSearchLast.size());
            if (iFoundBegin1 == 0 && iFoundBegin2 != string::npos)
            {
                bIsKey = true;
                strKey += strLine + strCRLF;
                continue;
            }
            if (iFoundEnd1 == 0 && iFoundEnd2 != string::npos)
            {
                bIsKey = false;
                strKey += strCRLF + strLine;
                break;
            }
            if (bIsKey)
            {
                strKey += strLine;
            }

        }
        ifFile.close();
    }
    if(bIsKey)
    {
        return "";
    }
    return strKey;
}

string Utils::utf8_substr(const string& str, unsigned int start, unsigned int leng)
{
	if (leng==0) { return ""; }
    unsigned int c, i, ix, q, min=string::npos, max=string::npos;
    for (q=0, i=0, ix=str.length(); i < ix; i++, q++)
    {
        if (q==start){ min=i; }
        if (q<=start+leng || leng==string::npos){ max=i; }
 
        c = (unsigned char) str[i];
        if      (c>=0   && c<=127) i+=0;
        else if ((c & 0xE0) == 0xC0) i+=1;
        else if ((c & 0xF0) == 0xE0) i+=2;
        else if ((c & 0xF8) == 0xF0) i+=3;
        //else if (($c & 0xFC) == 0xF8) i+=4; // 111110bb //byte 5, unnecessary in 4 byte UTF-8
        //else if (($c & 0xFE) == 0xFC) i+=5; // 1111110b //byte 6, unnecessary in 4 byte UTF-8
        else return "";//invalid utf8
    }
    if (q<=start+leng || leng==string::npos){ max=i; }
    if (min==string::npos || max==string::npos) { return ""; }
    return str.substr(min,max);
}

bool Utils::utf8_check_is_valid(const string& string)
{
	int c,i,ix,n,j;
    for (i=0, ix=string.length(); i < ix; i++)
    {
        c = (unsigned char) string[i];
        //if (c==0x09 || c==0x0a || c==0x0d || (0x20 <= c && c <= 0x7e) ) n = 0; // is_printable_ascii
        if (0x00 <= c && c <= 0x7f) n=0; // 0bbbbbbb
        else if ((c & 0xE0) == 0xC0) n=1; // 110bbbbb
        else if ( c==0xed && i<(ix-1) && ((unsigned char)string[i+1] & 0xa0)==0xa0) return false; //U+d800 to U+dfff
        else if ((c & 0xF0) == 0xE0) n=2; // 1110bbbb
        else if ((c & 0xF8) == 0xF0) n=3; // 11110bbb
        //else if (($c & 0xFC) == 0xF8) n=4; // 111110bb //byte 5, unnecessary in 4 byte UTF-8
        //else if (($c & 0xFE) == 0xFC) n=5; // 1111110b //byte 6, unnecessary in 4 byte UTF-8
        else return false;
        for (j=0; j<n && i<ix; j++) { // n bytes matching 10bbbbbb follow ?
            if ((++i == ix) || (( (unsigned char)string[i] & 0xC0) != 0x80))
                return false;
        }
    }
    return true;
}

int Utils::ReplaceStringInPlace(std::string &strContent, std::map<std::string, std::string> mSearchReplace)
{
	for(std::map<std::string, std::string>::iterator it = mSearchReplace.begin(); it != mSearchReplace.end(); it++)
	{
		size_t iPos = 0;
		std::string strSearchReplace = DELIMSTART + it->first + DELIMEND;
		while((iPos = strContent.find(strSearchReplace, iPos)) != std::string::npos) // need improve
		{
			strContent.replace(iPos, strSearchReplace.length(), it->second);
			iPos += it->second.length();
		}
	}
	return 0;
}

bool Utils::CheckStringIsNumber(std::string strNumber)
{
	for (auto const &cDigit : strNumber)
	{
		if (!isdigit(cDigit))
		{
			return false;
		}
	}
	return true;
}

int32_t Utils::CheckAppVersion(const std::vector<std::string> &vAppVersion, const std::vector<std::string> &vRefAppVersion)
{
	for (size_t i = 1; i < vAppVersion.size(); i++)
	{
		int32_t iPartVersion = Utils::StringToNumber<int32_t>(vAppVersion.at(i));
		int32_t iRefPartVersion = Utils::StringToNumber<int32_t>(vRefAppVersion.at(i));
		if (iPartVersion == iRefPartVersion)
		{
			continue;
		}

		return iPartVersion - iRefPartVersion;
	}
	return 0;
}

int32_t Utils::VerifyVersion(const std::string &strVersion, std::vector<std::string> &vVersion)
{
	split(strVersion, ".", vVersion);

	// Verify app version format
	if (vVersion.size() != 4)
	{
		return 1;
	}
	
	// Verify app version format prefix
	// if (vVersion[0] != "AND" && vVersion[0] != "iOS" && vVersion[0] != "WIN")
	// {
	// 	return 2;
	// }

	// Verify app version data
	for (size_t i = 1; i < vVersion.size(); i++)
	{
		if (!CheckStringIsNumber(vVersion[i]))
		{
			return 3;
		}
	}
	return 0;
}

void Utils::ByteStringToHexString(const std::string &strByteString, std::string &strHexString)
{
	strHexString = boost::algorithm::hex(strByteString);
}

void Utils::HexStringToByteString(const std::string &strHexString, std::string &strByteString)
{
	strByteString = boost::algorithm::unhex(strHexString);
}