#include "stdafx.h"
#include "strman.h"
#include <algorithm>

using namespace std;
/////////////////////////////////////////////////////////

void SplitString(std::string const& str, const char& cSep, int& nFields, std::vector<string> &v)
{
	string localStr, s;
	char cDefault = ',';
	localStr = str;
	
	// to guarantee that there's no space character at two ends of the string
	Cut(localStr);
	// replace the cSep character with the default one	
	replace(localStr.begin(), localStr.end(), cSep, cDefault);
	
	string::iterator itl, ith;
	itl = localStr.begin();
	ith = localStr.begin();
	// start looping...
	nFields = 0;
	while (1)
	{
		// find the first cDefault character 
		ith = find(itl, localStr.end(), cDefault);
		// extract from itl to ith into s
		s.assign(itl, ith);
		// update the vector
		v.push_back(s);
		// update number of fields
		nFields++;
		
		// test if there's not any longer cDefault character
		if (ith == localStr.end())
			break;
		// save the rest of the string
		localStr.erase(itl, ++ith);
		// to guarantee that there's no space character at two ends of the string
		Cut(localStr);
	}
}

void SplitString(std::string const& str, std::vector<char>& sep, int& nFields, std::vector<string> &v)
{
	std::string localStr, s;
	char cDefault = ',';		
	localStr = str;
	
	// to guarantee that there's no space character at two ends of the string	
	Cut(localStr);
	// replace the sep character with the default one	
	vector<char>::iterator itc;
	for (itc = sep.begin(); itc != sep.end(); itc++)
		replace(localStr.begin(), localStr.end(), *itc, cDefault);

	string::iterator itl, ith;
	itl = localStr.begin();
	ith = localStr.begin();

	nFields = 0;
	while (1)
	{
		// find the first cDefault character
		ith = find(itl, localStr.end(), cDefault);
		// extract from itl to ith into s
		s.assign(itl, ith);
		// update the vector
		v.push_back(s);
		// update number of fields
		nFields++;
		
		// test if there's not any longer cDefault character
		if (ith == localStr.end())
			break;
		// save the rest of the string
		localStr.erase(itl, ++ith);
		// to guarantee that there's no space character at two ends of the string
		Cut(localStr);
	}
}

void SplitString(const char* pStr, std::vector<char>& sep, int& nFields, std::vector<string> &v)
{
	std::string localStr(pStr), s;
	char cDefault = ',';		
	
	// to guarantee that there's no space character at two ends of the string	
	Cut(localStr);
	// replace the sep character with the default one	
	vector<char>::iterator itc;
	for (itc = sep.begin(); itc != sep.end(); itc++)
		replace(localStr.begin(), localStr.end(), *itc, cDefault);

	string::iterator itl, ith;
	itl = localStr.begin();
	ith = localStr.begin();

	nFields = 0;
	while (1)
	{
		// find the first cDefault character
		ith = find(itl, localStr.end(), cDefault);
		// extract from itl to ith into s
		s.assign(itl, ith);
		// update the vector
		v.push_back(s);
		// update number of fields
		nFields++;
		
		// test if there's not any longer cDefault character
		if (ith == localStr.end())
			break;
		// save the rest of the string
		localStr.erase(itl, ++ith);
		// to guarantee that there's no space character at two ends of the string
		Cut(localStr);
	}
}

void SplitString(std::string const& str, const char* sep, int& nFields, std::vector<std::string> &v)
{
	string localStr(str), s;
	char cDefault = ',';		
	
	// to guarantee that there's no space character at two ends of the string	
	Cut(localStr);
	// replace the sep characters with the default one	
	int i, nSize =  sizeof(sep)/sizeof(char);
	for (i=0; i<nSize-1; i++)
		replace(localStr.begin(), localStr.end(), sep[i], cDefault);

	string::iterator itl, ith;
	itl = localStr.begin();
	ith = localStr.begin();

	nFields = 0;

	while (1)
	{
		// find the first cDefault character
		ith = find(itl, localStr.end(), cDefault);
		// extract from itl to ith into s
		s.assign(itl, ith);
		// update the vector
		v.push_back(s);
		// update number of fields
		nFields++;
		
		// test if there's not any longer cDefault character
		if (ith == localStr.end())
			break;
		// save the rest of the string
		localStr.erase(itl, ++ith);
		// to guarantee that there's no space character at two ends of the string
		Cut(localStr);
	}
}

void SplitString(std::string const& str, std::string const& sep, int& nFields, std::vector<string> &v)
{
	string localStr, s;
	char cDefault = ',';		
	localStr = str;

	// to guarantee that there's no space character at two ends of the string	
	Cut(localStr);

	string::iterator itl, ith;
	itl = localStr.begin();
	ith = localStr.begin();

	nFields = 0;
	IsDelimiters isDel;
	isDel.sDelimiters = sep;

	while (1)
	{
		// find the first cDefault character
		ith = find_if(itl, localStr.end(), isDel);
		// extract from itl to ith into s
		s.assign(itl, ith);
		// update the vector
		v.push_back(s);
		// update number of fields
		nFields++;
		
		// test if there's not any longer cDefault character
		if (ith == localStr.end())
			break;
		// save the rest of the string
		localStr.erase(itl, ++ith);
		// to guarantee that there's no space character at two ends of the string
		Cut(localStr);
	}
}

void Cut(std::string& s)
{
	if (s.length() == 0)
		return;

	string::iterator it, its, ite;
	
	its = s.begin();
	for (it = s.begin(); it != s.end(); it++)
	{
		if (isspace(*it))
			its++;
		else
			break;
	}

	ite = s.end();
	for (it = s.end()-1; it != s.begin(); it--)
	{
		if (isspace(*it))
			ite = it;
		else
			break;
	}

	copy(its, ite, s.begin());
	s.resize(ite - its);
}

int Parse(const char* sInputLine, std::string& entry, std::string& value)
{
	std::string str(sInputLine);
	string::iterator ith, itl;

	if (str.length() == 0)
		return 0;

	itl = str.begin();
	ith = find(itl, str.end(), ']');

	entry.assign(itl, ++ith);
	value.assign(++ith, str.end());

	// Remove all spaces
	Cut(value);

	return 1;
}

void Output(std::string const& str, std::ofstream& ofs)
{
	int n = str.size();
	ofs.write((char*)&n, sizeof(n));
	ofs.write((char*)str.c_str(), str.size());
}

void Input(std::string& str, std::ifstream& ifs)
{
	int n;
	ifs.read((char*)&n, sizeof(n));
	str.resize(n);
	ifs.read((char*)str.data(), n);
}