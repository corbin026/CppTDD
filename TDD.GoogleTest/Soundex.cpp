#include "pch.h"
#include "Soundex.h"


Soundex::Soundex()
{
}

std::string Soundex::encode(const std::string & word) const
{
	return zeroPad(head(word) + encodedDigits(word));
}


Soundex::~Soundex()
{
}

std::string Soundex::encodedDigits() const
{
	return "1";
}

std::string Soundex::head(const std::string & word) const
{
	return word.substr(0, 1);
}

std::string Soundex::encodedDigits(const std::string & word) const
{
	if (word.length() > 1) {
		return encodedDigits();
	}
	return "";
}

std::string Soundex::zeroPad(const std::string & word) const
{
	auto zerosNeeded = MaxCodeLength - word.length();
	return word + std::string(zerosNeeded,'0');
}