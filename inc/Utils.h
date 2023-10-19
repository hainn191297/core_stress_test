/*
 * Utils.h
 *
 *  Created on: Apr 9, 2013
 *      Author: nhsan
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <uuid/uuid.h>
#include <string>
#include <boost/algorithm/string/replace.hpp>
#include <vector>
#include <sstream>
#include <time.h>
#include <iostream>
#include <math.h>
#include <openssl/sha.h>
#include <openssl/md5.h>
#include <fstream>
#include <iomanip>
#include <boost/lexical_cast.hpp>
#include <cppcms/json.h>

using namespace std;
typedef std::string string;

#define SAFE_DEL(x) if (x) {delete x; x = NULL;}
#define SAFE_DEL_ARRAY(x) if (x) {delete[] x; x = NULL;}
#define SAFE_FREE(x) if (x) {free(x); x = NULL;}
#define DELIMSTART "<@"
#define DELIMEND ">"

class Utils
{
public:
	static string generate_code(int len);
	static string pack_uuid(const uuid_t &uuid);
	static string uuid_encode(string id);
	static string uuid_decode(string id);
	static string generate_uuid();
	static string generate_text_uuid();
	static string generate_session_id();
	static bool normalize_string(string &str);
	static bool normalize_email(string &str);
	static bool normalize_tel(string &str);
	static bool check_password(string str);
	static string peer_chat_key(string user1_id, string user2_id);
    static string getPeerName(int fd);
	static string utf8_substr(const string& str, unsigned int start, unsigned int leng);
	static bool utf8_check_is_valid(const string& string);
	template <typename T>
	static string join_with_separator_string ( const T& t ,const std::string& separator)
	{
		std::string output = "";
		unsigned int count = t.size();
		unsigned int i = 0;
		for(typename T::const_iterator it = t.begin(); it != t.end(); it++)
		{
			i++;
			output += *it;
			if(i != count) output += separator;
		}
		return output;
	}
	static void split(const string& str, const string& delim, std::vector<string>& tokens)
	{
	    size_t prev = 0, pos = 0;
	    do
	    {
	        pos = str.find(delim, prev);
	        if (pos == string::npos) pos = str.length();
	        string token = str.substr(prev, pos-prev);
	        if (!token.empty()) tokens.push_back(token);
	        prev = pos + delim.length();
	    }
	    while (pos < str.length() && prev < str.length());
	}

	static bool make_directory(string path);
	static std::string generate_uuid1();
	static bool validate_token(string token);
	static uint64_t time_t();
    static uint64_t time_seconds_t();
	static string hex_sha1(string text);
	static size_t curlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s);
    static size_t header_callback (void * pData, size_t tSize, size_t tCount, void * pmUser);

	static int IntRange(int min, int max)
    {
	   static bool first = true;
	   if ( first )
	   {
		  srand(time(NULL)); //seeding for the first time only!
		  first = false;
	   }
	   return min + rand() % (max - min);
    }

	static string GenerateOtpNumber(string phone, bool is_production)
	{
		int otp = IntRange(1000, 9999);
		if (phone == "841234567890" || phone == "841234567891" || !is_production)
		{
			otp = 1234;
		}
		std::stringstream ss;
		ss << otp;
		return ss.str();
	}

    static string GenerateCaptcha()
    {
        int captcha = IntRange(100000, 999999);
        std::stringstream ss;
        ss << captcha;
        return ss.str();
    }

    static string GenerateSecureCodeVnptpay(string& param)
    {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, param.c_str(), param.size());
        SHA256_Final(hash, &sha256);
        ostringstream sout;
        sout << hex << setfill('0');
        for(long long c: hash)
        {
            sout << setw(2) << (long long)c;
        }
        return sout.str();
    }

	static bool isSameDay(uint64_t t1, uint64_t t2)
	{
		std::time_t tt1 = static_cast<std::time_t>(t1/1000);
		struct tm tm1 = *gmtime(&tt1);
		std::time_t tt2 = static_cast<std::time_t>(t2/1000);
		struct tm tm2 = *gmtime(&tt2);
		if (tm1.tm_year != tm2.tm_year || tm1.tm_mon != tm2.tm_mon || tm1.tm_mday != tm2.tm_mday) return false;
		return true;
	}

	static double get_distance(double lat1, double lon1, double lat2, double lon2)
	{
		auto deg2rad = [](float d) { return d * (M_PI / 180.f); };

		auto dlon = deg2rad(lon2 - lon1);
		auto dlat = deg2rad(lat2 - lat1);

		constexpr int R = 6371000;

        auto a = pow(sin(dlat/2), 2) +
                 cos(lat1) * cos(lat2) *
                 pow(sin(dlon/2),2);

        auto c = 2 * atan2(sqrt(a), sqrt(1-a));

		auto d = R * c;
		return d;
    }

	static std::string getFileExtension(const std::string& fileName)
	{
	    if(fileName.find_last_of(".") != std::string::npos)
	        return fileName.substr(fileName.find_last_of(".")+1);
	    return "";
	}

	template <typename T>
	static std::string NumberToString(T number)
	{
		// TNVN1.0.x # SonTV # 2020-12-18 # Fix crash stringstream load number
		// std::string strResult = "";
		// std::stringstream ss;
		// ss << number;
		// strResult = ss.str();
		// ss.clear();
		// return ss.str();

		return std::to_string(number);
	}

	template <class T>
	static T StringToNumber(std::string value)
	{
		T ret;
		std::stringstream ss;
		ss << value;
		ss >> ret;
		ss.clear();
		return ret; 
	}

	static string CreateMD5(const string &value);
	static int LoadJsonFromFile(const string &strFile, cppcms::json::value &jValue);
	static string ParseKeyFromPem(std::string strPathPem);
	static int ReplaceStringInPlace(std::string &strContent, std::map<std::string, std::string> mMemberIDName);
	static bool CheckStringIsNumber(std::string strNumber);
	// Return < 0  => app version smaller than ref app version to be passed.
	// > 0 => app version greater than ref app version to be passed.
	static int32_t CheckAppVersion(const std::vector<std::string> &vAppVersion, const std::vector<std::string> &vRefAppVersion);
	// Function to verify app version
	static int32_t VerifyVersion(const std::string &strVersion, std::vector<std::string> &vVersion);
	static void ByteStringToHexString(const std::string &strByteString, std::string &strHexString);
	static void HexStringToByteString(const std::string &strHexString, std::string &strByteString);
	
	static uint64_t GetYearLocal()
	{
		std::time_t objTime = time(NULL);
		struct tm *pTime = localtime(&objTime);

		return pTime->tm_year + 1900;
	}
	static uint64_t GetDayOfYear()
	{
		std::time_t objTime = time(NULL);
		struct tm *pTime = localtime(&objTime);

		return pTime->tm_yday;
	}

};

#endif /* UTILS_H_ */
