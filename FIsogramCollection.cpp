#include "FIsogramCollection.h"
#include <random>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

FString FIsogramCollection::GetRandomWordByLength(int32 Length) const
{
	switch (Length) // selects a word collection depending on the length picked
	{
	case 3:
		return ThreeLetterWords[RandomNumber(ThreeLetterWords.size())];
	case 4:
		return FourLetterWords[RandomNumber(FourLetterWords.size())];
	case 5:
		return FiveLetterWords[RandomNumber(FiveLetterWords.size())];
	case 6:
		return SixLetterWords[RandomNumber(SixLetterWords.size())];
	case 7:
		return SevenLetterWords[RandomNumber(SevenLetterWords.size())];
	case 8:
		return EightLetterWords[RandomNumber(EightLetterWords.size())];
	default:
		break;
	}
	return FourLetterWords[RandomNumber(FourLetterWords.size())]; // returns 4 letter word if for some reason no case was recognized
}

int32 FIsogramCollection::RandomNumber(int32 MaxRange) const // random number generator helper function
{
	static thread_local std::mt19937 s_Rng{ std::random_device{}() };
	std::uniform_int_distribution<std::mt19937::result_type> distRandom(1, MaxRange); // distribution in range [1, MaxRange]
	return distRandom(s_Rng);
}
