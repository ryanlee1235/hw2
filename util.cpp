#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <set>

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    int len = rawWords.length();

    std::set<string> wordSet;
    string word = "";
    for(int i = 0; i < len; i++)
    {
        if((rawWords[i] >= '0' && rawWords[i] <= '9') || (rawWords[i] >= 'A' && rawWords[i] <= 'Z')
            || (rawWords[i] >= 'a' && rawWords[i] <= 'z'))
        {
            if(rawWords[i] >= 'A' && rawWords[i] <= 'Z')
            {
                word += (rawWords[i] + 32);
            }
            else
            {
                word += rawWords[i];
            }
        }
        else
        {
            if(word.length() >= 2)
            {
                wordSet.insert(word);
            }
            word = "";
        }
    }
    if(word.length() >= 2)
    {
        wordSet.insert(word);
    }
    return wordSet;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
