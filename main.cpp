/* This is the console executable, that makes use of the BullCowClass
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowClass class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PickDifficulty();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

// entry point for our application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();

		PickDifficulty();

		PlayGame();
		std::cout << std::endl;

		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "         /(o o)\\      /(o o)\\ " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the isogram word I'm thinking off?\n";
	std::cout << std::endl;
	return;
}

void PickDifficulty()
{
	FString Difficulty;
	EDifficultyStatus Status = EDifficultyStatus::Invalid_Status;
	std::cout << "Pick your difficulty!\n";
	std::cout << "Choose the length of the word you want to guess (anywhere from 3 letters to 8 letters): ";
	do {
		std::getline(std::cin, Difficulty);
		std::cout << std::endl;

		Status = BCGame.CheckDifficultyValidity(Difficulty);

		switch (Status)
		{
		case EDifficultyStatus::OK:
			break;
		case EDifficultyStatus::Invalid_Status:
			std::cout << "You must enter a number between 3 and 8 to determine your hidden word's length: ";
			break;
		default:
			// assume guess is valid
			break;
		}

	} while (Status != EDifficultyStatus::OK); // TODO change vack to OK status after functions are written
	BCGame.SetDifficulty(std::stoi(Difficulty));
	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	std::cout << "Guess the " << BCGame.GetHiddenWordLength() << " letter isogram!\n";
	int32 MaxTries = BCGame.GetMaxTries();
	// loop asking for guesses while the game
	// iis NOT won and there are still tries remaining
	while (!BCGame.GetIsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print32 number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
	}
	PrintGameSummary();
	return;
}

// loop until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = ""; // get a guess from the player
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry(); // Get Current Try
		std::cout << std::endl << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::OK:
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "You guess is not an isogram! An isogram is a word without a repeating letter.\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word!\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter an all lowercase word!\n";
			break;
		default:
			// assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

void PrintGameSummary()
{
	std::cout << std::endl;
	if (BCGame.GetIsGameWon())
	{
		std::cout << "You won the game!\n";
	}
	else
	{
		std::cout << "You lost the game, better luck next time!\n";
	}
	return;
}

bool AskToPlayAgain()
{
	std::cout << "The hidden word was: " << BCGame.GetHiddenWord() << "\n\n";
	std::cout << "Do you want to play again (y/n)?\n";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
