#include "stdafx.h"
#include "FCowBullGame.h"
#include <map>
#define TMap std::map

using int32 = int;
using FString = std::string;

int32 FCowBullGame::GetMaxTries() const { return MyMaxTries; }
int32 FCowBullGame::GetCurrentTry() const { return MyCurrentTries; }
int32 FCowBullGame::GetHiddenWordLength() const {	return MyHiddenWord.length(); }
bool FCowBullGame::IsGameWon() const {	return bGameIsWon; }


// constructor
FCowBullGame::FCowBullGame()
{
	Reset();
}

// resets game to starting state
void FCowBullGame::Reset()
{
	constexpr int32 MAX_TRIES = 5;
	const FString HIDDEN_WORD = "planet";

	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = MAX_TRIES;
	MyCurrentTries = 1;
	bGameIsWon = false;
	return;
}

ECheckStatus FCowBullGame::CheckGuessValidity(FString guess) const
{
	if (!IsIsogram(guess)) // if the guess isnt an isogram return an error
	{
		return ECheckStatus::Not_Isogram;
	}
	else if ( guess.length() != GetHiddenWordLength()) // if the guess length is wrong return an error
	{
		return ECheckStatus::Wrong_Length;
	}
	else // otherwise return ok
	{
		return ECheckStatus::OK;
	}
}

// receives valid guess, increments turn and returns count
FCowBullCount FCowBullGame::SubmitValidGuess(FString UserGuess)
{
	MyCurrentTries++;
	FCowBullCount CowBullCount;

	//looping through all letters in the guess
	int32 WordLength = MyHiddenWord.length();
	//compare letters against hidden word
	for (int32 i = 0; i < WordLength; i++) 
	{
		if (MyHiddenWord[i] == UserGuess[i]) // checking condition for bulls
		{
			CowBullCount.Bulls++;
		}
		else 
		{		
			for (int32 j = 0; j < WordLength; j++)
			{
				if (MyHiddenWord[i] == UserGuess[j]) // checking condition for cows
				{
					CowBullCount.Cows++;
				}
			}
		}
	}
	if (CowBullCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return CowBullCount;
}

bool FCowBullGame::IsIsogram(FString Word) const
{
	// treat zero or one letter words as isograms
	if (Word.length() <= 1) { return true; }
	
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter); // handles mixed case
		if (LetterSeen[Letter]) {  // if the letter is in the map
			return false; // we do not have an isogram 
		} else { // otherwise
			LetterSeen[Letter] = true; // add the letter to the map
		}			
	}
	return true;
}
