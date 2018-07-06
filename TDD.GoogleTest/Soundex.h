#pragma once
class Soundex
{
public:
	Soundex();
	std::string encode(const std::string & word) const;
	~Soundex();
private:
	static const size_t MaxCodeLength{4};
	std::string encodedDigits() const;
	std::string head(const std::string& word) const;
	std::string encodedDigits(const std::string& word) const;
	std::string zeroPad(const std::string& word) const;
};

