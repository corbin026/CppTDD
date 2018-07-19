#pragma once

#include <unordered_map>
#include <locale>

class Soundex
{
public:
	Soundex();	
	~Soundex();
	std::string encode(const std::string & word) const;	
	std::string encodedDigit(char letter) const;
	std::string upperFront(const std::string & string) const;

private:
	std::locale loc;
	static const size_t MaxCodeLength{4};
	const std::string NotADigit{ "*" };
	char lower(char c) const;
	std::string head(const std::string& word) const;
	std::string encodedDigits(const std::string& word) const;
	void encodeTail(const std::string & word, std::string &encoding) const;
	void encodeLetter(const char &letter, std::string & encoding, char lastLetter) const;
	bool isVowel(char letter) const;
	void encodeHead(std::string &encoding, const std::string & word) const;
	std::string lastDigit(const std::string & encoding) const;
	bool isComplete(std::string &encoding) const;
	std::string zeroPad(const std::string& word) const;
	std::string tail(const std::string& word)const;	
};


