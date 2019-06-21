#pragma once
#include <string>

using int32 = int;
using FString = std::string;

// all values initialized to zero
struct FCowBullCount
{
	int32 Cows = 0;
	int32 Bulls = 0;
};

enum class ECheckStatus 
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Invalid_Character,
	Not_Lowercase,
	
};

class FCowBullGame {
public:
	FCowBullGame(); //Constructor

	int32 GetMaxTries() const; 
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	ECheckStatus CheckGuessValidity(FString) const; //TODO make a more rich return value
	
	void Reset(); //TODO make a more rich return value
	FCowBullCount SubmitValidGuess(FString); // counts bulls and cows and increases try #, assuming valid guess



private:
	int32 MyCurrentTries;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
	
	bool IsIsogram(FString) const;
};