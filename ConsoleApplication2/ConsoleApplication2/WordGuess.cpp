/*  This is the console executable that makes the FCowBullGame.
	For game logic see the FCowBullGame class
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FCowBullGame.h" 

using int32 = int;
using FText = std::string;

FText GetValidGuess();
void PrintIntro();
void PrintGameSummary();
void PlayGame();
bool AskToPlayAgain();


FCowBullGame BCGame; // Instantiate a new game

// Entry point of the program.
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		PrintGameSummary();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain == true);
    return 0; // Exit point of the program.
}

void PrintIntro()
{
	// Basic game UI or Introduction of the game
	std::cout << "Welcome to Bulls and Cows, a word game meant to suck your soul out of you. \n";
	std::cout << "Try to guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram :) \n\n";
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	// Loop asking for guesses while game is not won
	// and there are tries remaining
	
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry()<=MaxTries) 
	{
		FText Guess = GetValidGuess(); 	
		FCowBullCount CowBullCount = BCGame.SubmitValidGuess(Guess);
		
		// submit valid guess to the game and receive counts
		std::cout << "Your guess was " << Guess << std::endl;
		std::cout << "Bulls = " << CowBullCount.Bulls;
		std::cout << ". cows = " << CowBullCount.Cows << "\n\n";
	}
}

// looping continually till user gives a valid guess
FText GetValidGuess()
{
	ECheckStatus Status = ECheckStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		int32 MyCurrentTry = BCGame.GetCurrentTry();
		// Retreiving input from the user
		
		std::cout <<"Try "<< MyCurrentTry <<". Enter your guess: ";
		std::getline(std::cin, Guess);
	
		 Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case ECheckStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case ECheckStatus::Invalid_Character:
			std::cout << "Please do not use invalid characters.\n";
			break;
		case ECheckStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating characters.\n";
			break;
		case ECheckStatus::Not_Lowercase:
			std::cout << "Please enter the word in lowercase.\n";
			break;
		default:
			break; // assume the guess is valid
		}
		std::cout << std::endl ;
	} while (Status!=ECheckStatus::OK); // keep looping till we get no errors
	return Guess;
}


bool AskToPlayAgain()
{
	FText Response;
	std::cout << "Do you want to play again with the same word? (y/n): ";
	std::getline(std::cin, Response);
	
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon() == true)
	{
		std::cout << "Congratulations! You have guessed the correct word. \n";
	}
	else if (BCGame.IsGameWon() == false)
	{
		std::cout << "Too bad, you ran out of tries. Better luck next time. \n";
	}
	return;
}
