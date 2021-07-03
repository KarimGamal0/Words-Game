// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();
	GetValidWords(Words);
	SetupGame(); //Setting Up the game

	PrintLine(TEXT("The number of possible words is %i"), Words.Num());
	PrintLine(TEXT("The number of valid words is %i."), GetValidWords(Words).Num());
	PrintLine(TEXT("The HiddenWord is %s."), *HiddenWord, HiddenWord.Len()); //Debug Line

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	if (bGameOver)
	{
		ClearScreen();
		SetupGame();
	}
	else {
		ProcessGuess(Input);
	}
}

void UBullCowCartridge::SetupGame() {
	PrintLine(TEXT("Welcome to Bull Cows!"));

	HiddenWord = TEXT("Cakes"); //Set the HiddenWord
	Lives = HiddenWord.Len(); //Set Lives
	bGameOver = false;

	PrintLine(TEXT("Guess %i Letter Word"), HiddenWord.Len()); //Magic Number Remove
	PrintLine(TEXT("You have %i lives."), Lives);
	PrintLine(TEXT("Type in your guess and \nPress Enter to continue..."));

	//const TCHAR HW[] = TEXT("cakes");
}

void UBullCowCartridge::EndGame() {
	bGameOver = true;
	PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
	if (Guess == HiddenWord)
	{
		PrintLine("You have Won");
		EndGame();
		return;
	}

	if (Guess.Len() != HiddenWord.Len())
	{
		PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
		PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);
		return;
	}

	//Check if isogram
	if (!IsIsogram(Guess)) {
		PrintLine(TEXT("No repeating letters, guess again"));
		return;
	}

	//Remove life
	PrintLine(TEXT("Lost a life!"));
	--Lives;

	if (Lives <= 0) {
		ClearScreen();
		PrintLine(TEXT("You have no lives left!"));
		PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);

		EndGame();
		return;
	}

	PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{

	for (int32 Index = 0; Index < Word.Len() - 1; Index++)
	{
		for (int Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
		{
			if (Word[Index] == Word[Comparison])
			{
				return false;
			}
		}
	}

	return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
{
	TArray<FString> ValidWords;
	for (FString Word :WordList)
	{
		if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
		{
			ValidWords.Emplace(Word);
		}
	}

	return ValidWords;
}
