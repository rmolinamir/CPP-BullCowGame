/* This is the FBullCowClass class where all the logic
(no view code or use interaction) regarding. The game is
a simple guess the word game based on Mastermind. It is 
handled, this amounts to getters, setters, private variables, 
public variables, and helper functions.
*/

#pragma once
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EDifficultyStatus
{
	Invalid_Status,
	OK
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	FString GetRandomWord(int32) const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetHiddenWord() const;
	bool GetIsGameWon() const;
	int32 GetMaxTries() const;
	EDifficultyStatus CheckDifficultyValidity(FString) const;
	EGuessStatus CheckGuessValidity(FString) const;
	
	void SetDifficulty(int32);
	void Reset();
	FBullCowCount SubmitValidGuess(FString); // counts bulls & cows, and incrementing try # assuming valid guess

private:
	// see constructor for initialization
	int32 MyDifficulty;
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon;

	bool IsDigit(FString) const; // TODO write function
	bool IsValidDifficulty(FString) const; // is valid if word's length is between 3 and 8

	bool isLowerCase(FString) const;
	bool IsIsogram(FString) const;
};