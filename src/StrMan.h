//////////////////////////////////////////////////////
// StrMan.h
#pragma warning (disable : 4786)

#include <string>
#include <vector>
#include <fstream>

struct IsDelimiters
{
	std::string sDelimiters;
	bool operator()(char ch)
	{
		return (sDelimiters.find(ch) != std::string::npos);
	}
};

void Cut(std::string& s);
void SplitString(std::string  const& str,  const char&  cSep, int& nFields, std::vector<std::string> &v);
void SplitString(std::string  const& str,  std::vector<char>& sep, int& nFields, std::vector<std::string> &v);
void SplitString(std::string  const& str,  const char*   sep, int& nFields, std::vector<std::string> &v);
void SplitString(std::string  const& str,  std::string const& sep, int& nFields, std::vector<std::string> &v);
void SplitString(const   char*  pStr, std::vector<char>& sep, int& nFields, std::vector<std::string> &v);

int	Parse(const char* sInputLine, std::string& entry, std::string& value);

void Input(std::string& str, std::ifstream& ifs);
void Output(std::string const& str, std::ofstream& ofs);