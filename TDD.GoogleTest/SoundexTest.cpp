#include "pch.h"
#include <iostream>
#include "Soundex.h"

using namespace testing;

class SoundexEncoding : public Test {
public:
	Soundex soundex;
};

TEST_F(SoundexEncoding, RetainSoleLetterOfOneLetterWord) {	
	auto encoded = soundex.encode("A");
  ASSERT_EQ(encoded,"A000");
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
	auto encoded = soundex.encode("I");
	ASSERT_EQ(encoded, "I000");
}

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropiateDigits) {
	ASSERT_EQ(soundex.encode("Ax"), "A200");
	//EXPECT_EQ(soundex.encode("Ac"), std::string("A200"));
	//EXPECT_EQ(soundex.encode("Ad"), std::string("A300"));
	//EXPECT_EQ(soundex.encode("Ab"), std::string("A100"));
}

TEST_F(SoundexEncoding, IgnoresNonAlphabetics) {
	ASSERT_EQ(soundex.encode("A#"), "A000");
}

TEST_F(SoundexEncoding, ReplacesMultipleConsonantsWithDigits) {
	ASSERT_EQ(soundex.encode("Acdl"), "A234");
}

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters) {
	ASSERT_EQ(soundex.encode("Dcdlb").length(), 4u);
}

// Attached the word DISABLED_ before the name of your test e.g. DISABLED_IgnoresVowelLikeLetters
// to dismiss the test.
TEST_F(SoundexEncoding, IgnoresVowelLikeLetters) {
	ASSERT_EQ(soundex.encode("BaAEiIouhycdl"), "B234");
}

TEST_F(SoundexEncoding, CombinesDuplicateEncodings) {

	ASSERT_EQ(soundex.encodedDigit('b'), soundex.encodedDigit('f'));
	ASSERT_EQ(soundex.encodedDigit('c'), soundex.encodedDigit('g'));
	ASSERT_EQ(soundex.encodedDigit('d'), soundex.encodedDigit('t'));
	ASSERT_EQ(soundex.encode("Abfcgdt"), "A123");
}

TEST_F(SoundexEncoding, UpercasesFirstLetter) {
	ASSERT_EQ(soundex.upperFront("abcd"), "A");
}

TEST_F(SoundexEncoding, IgnoresCaseWhenEncodingConsonants) {
	ASSERT_EQ(soundex.encode("BCDL"), soundex.encode("bcdl"));
}

TEST_F(SoundexEncoding, CombinesDuplicateCodesWhen2ndLetterDuplicates1st) {
	ASSERT_EQ(soundex.encode("Bbcd"), "B230");
}

TEST_F(SoundexEncoding, DoesNotCombineDuplicateEncodingsSeparatedByVowels) {
	ASSERT_EQ(soundex.encode("Jbob"), "J110");
}