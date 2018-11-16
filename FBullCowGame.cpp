#pragma once

#include "FBullCowGame.h"
#include "FIsogramCollection.h"
#include <cctype>
#include <map>

// to make syntax Unreal friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

FIsogramCollection IsogramCollection; // IsogramDictionary instantiation

FBullCowGame::FBullCowGame() { this->Reset(); } // default constructor

void FBullCowGame::SetDifficulty(int32 Difficulty)
{
	const int32 MY_DIFFICULTY = Difficulty;
	MyDifficulty = MY_DIFFICULTY;
	return;
}

FString FBullCowGame::GetRandomWord(int32 Difficulty) const {	return IsogramCollection.GetRandomWordByLength(Difficulty); }
int32 FBullCowGame::GetCurrentTry() const {	return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }
bool FBullCowGame::GetIsGameWon() const { return bIsGameWon; }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3, 7}, {4, 10}, {5, 12}, {6, 15}, {7, 18}, {8, 22} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}


void FBullCowGame::Reset()
{
	constexpr int32 CURRENT_TRY = 1;
	MyCurrentTry = CURRENT_TRY;

	constexpr bool IS_GAME_WON = false;
	bIsGameWon = IS_GAME_WON;

	const FString HIDDEN_WORD = IsogramCollection.GetRandomWordByLength(MyDifficulty);
	MyHiddenWord = HIDDEN_WORD;

	return;
}

EDifficultyStatus FBullCowGame::CheckDifficultyValidity(FString Difficulty) const
{
	if (!IsValidDifficulty(Difficulty))
	{
		return EDifficultyStatus::Invalid_Status;
	}
	else
	{
		return EDifficultyStatus::OK;
	}
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{

	if (!isLowerCase(Guess)) // if the guess isn't all lower case
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (!IsIsogram(Guess)) // otherwise if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (Guess.length() != GetHiddenWordLength()) // otherwise if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else // otherwise
	{
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	// increment the turn number
	MyCurrentTry++;
	// setup a return variable
	FBullCowCount BullCowCount;

	// loop through all letters in the hidden word
	for (int32 i = 0; i < GetHiddenWordLength(); i++)
	{
		// compare letters against the hidden word
		// if they're in the same
		if (MyHiddenWord[i] == Guess[i])
		{
			BullCowCount.Bulls++; // increment bulls
			continue;
		}
		// else
		else 
		{
			// loop through all the letters in the hidden word
			// to compare if any of the letters in the guess 
			// match a letter in the hidden word
			for (int32 j = 0; j < GetHiddenWordLength(); j++)
			{
				// if the letter is the same as any of the hidden words letters
				if (Guess[i] == MyHiddenWord[j])
				{
					BullCowCount.Cows++; // increment cows
					break;
				}
			}
		}
	}
	if (BullCowCount.Bulls == GetHiddenWordLength())
	{
		bIsGameWon = true;
	}
	return BullCowCount;
}

bool FBullCowGame::IsDigit(FString Difficulty) const
{
	for (auto Letter : Difficulty)
	{
		if (!std::isdigit(Letter)) // if the letter is not a digit return false
		{
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsValidDifficulty(FString Difficulty) const
{
	if (Difficulty.length() == 0 || Difficulty.length() == '\0') { return false;  } // if it's an empty string or \0
	if (!IsDigit(Difficulty)) { return false; } // if it's not a digit then return false
	if (std::stoi(Difficulty) >= 3 && std::stoi(Difficulty) <= 8) // if it's not between 3 and 8 then return false
	{
		return true;
	}
	return false;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	// setup our map
	TMap<char, bool> LetterSeen;

	// loop through each letter
	for (auto Letter : Word) // for all letters of the word
	{
		// Letter = tolower(Letter); // to handle uppercase letters
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
		
	return true;
}

bool FBullCowGame::isLowerCase(FString Word) const
{
	if (Word.empty() || Word == "\0") { return false;  } // if the word is empty or if it's \0
	for (auto Letter : Word)
	{
		if (!islower(Letter) || isspace(Letter)) // if not a lower case or if it's an empty character
		{
			return false;
		}
	}
	return true;
}
