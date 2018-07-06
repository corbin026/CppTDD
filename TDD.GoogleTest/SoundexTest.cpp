#include "pch.h"
#include <iostream>
#include "Soundex.h"

using namespace testing;

class SoundexEncoding : public Test {
public:
	Soundex soundex;
};

TEST_F(SoundexEncoding, RetainSoleLetterOfOneLeterWord) {	
	auto encoded = soundex.encode("A");
  ASSERT_EQ(encoded, std::string("A000"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
	auto encoded = soundex.encode("I");
	ASSERT_EQ(encoded, std::string("I000"));
}

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropiateDigits) {
	ASSERT_EQ(soundex.encode("Ab"), std::string("A100"));
}
