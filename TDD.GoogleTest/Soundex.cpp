#include "pch.h"
#include "Soundex.h"

Soundex::Soundex()
{
}

Soundex::~Soundex()
{
}

std::string Soundex::encode(const std::string & word) const
{
	return zeroPad(upperFront(head(word)) + tail(encodedDigits(word)));
}

std::string Soundex::upperFront(const std::string& string) const {
	auto upper = std::string(1,
		std::toupper(static_cast<unsigned char>(string.front()), loc));
	return upper;
}

std::string Soundex::tail(const std::string& word) const {
	return word.substr(1);
}

std::string Soundex::encodedDigits(const std::string & word) const
{
	std::string encoding;
	encodeHead(encoding, word);

	encodeTail(word, encoding);
	return encoding;
}
void Soundex::encodeTail(const std::string & word, std::string &encoding) const
{
	for (auto i = 1u; i < word.length(); i++) {
		if (!isComplete(encoding)) {
			encodeLetter(word[i], encoding, word[i - 1]);
		}

	}
}
void Soundex::encodeLetter(const char &letter, std::string & encoding, char lastLetter) const
{
	auto digit = encodedDigit(letter);
	if (digit != NotADigit && (digit != lastDigit(encoding) || isVowel(lastLetter))) {
		encoding += digit;
	}
}
bool Soundex::isVowel(char letter) const {
	return std::string("aeiouy").find(lower(letter)) != std::string::npos;
}
void Soundex::encodeHead(std::string &encoding, const std::string & word) const
{
	encoding += encodedDigit(word.front());
}
std::string Soundex::lastDigit(const std::string & encoding) const
{
	if (encoding.empty()) {
		return NotADigit;
	}
	return std::string(1, encoding.back());
}

bool Soundex::isComplete(std::string &encoding) const
{
	return encoding.length() == MaxCodeLength;
}

std::string Soundex::encodedDigit(char letter) const {
	const std::unordered_map<char, std::string> encodings{
		{'b',"1"},{ 'f',"1" },{ 'p',"1" },{ 'v',"1" },
		{'c',"2"},{ 'g',"2" },{ 'j',"2" },{ 'k',"2" },{ 'q',"2" },
				  { 's',"2" },{ 'x',"2" },{ 'z',"2" },
		{'d',"3"},{ 't',"3" },
		{'l',"4" },
		{'m',"5" },{ 'n',"5" },
		{'r',"6" }
	};
	auto it = encodings.find(lower(letter));
	return (it == encodings.end()) ? NotADigit : it->second;
}

char Soundex::lower(char c) const
{
	return std::tolower(static_cast<unsigned char>(c), loc);
}

std::string Soundex::head(const std::string & word) const
{
	return word.substr(0, 1);
}


std::string Soundex::zeroPad(const std::string & word) const
{
	auto zerosNeeded = MaxCodeLength - word.length();
	return word + std::string(zerosNeeded, '0');
}
