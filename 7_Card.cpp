/*
2021-01-03 Program that calculates the percentage chance of winning in Texas Holdem (for 7 cards, 2 playing cards + 5 table cards)
*/

#include <iostream> //std::cout
#include <iomanip> //std::setprecision
#include <string> //stoi(string)
using namespace std; //string
#include "Poker_Card_Rank.h" //gives rank for 7 cards in texas holdem

int PlayerCard1 = 0;
int PlayerCard2 = 0;
int TestCard1;
int TestCard2;
int RankList[52][52];
int Wins = 0;
int Total = 0;

void ErrorText(string ErrorString);

int main(int argc, char* argv[])
{
	// checks that there are 7 parameters (+ 1 system parameter)
	if (argc < 8) { ErrorText("Too Few Parameters"); }

	//Player card 1
	try
	{ PlayerCard1 = -1 + stoi(argv[1]); }
	catch (const std::exception&) { ErrorText("Parameter 1 incorrect (Player card 1)"); }

	//Player card 2
	try
	{ PlayerCard2 = -1 + stoi(argv[2]); }
	catch (const std::exception&) { ErrorText("Parameter 2 incorrect (Player card 2)"); }

	//Table card 1
	try
	{ SevenCardsInput.Card[2].Number = -1 + stoi(argv[3]); }
	catch (const std::exception&) { ErrorText("Parameter 3 incorrect (Table card 1)"); }

	//Table card 2
	try
	{ SevenCardsInput.Card[3].Number = -1 + stoi(argv[4]); }
	catch (const std::exception&) { ErrorText("Parameter 4 incorrect (Table card 2)"); }

	//Table card 3
	try
	{ SevenCardsInput.Card[4].Number = -1 + stoi(argv[5]); }
	catch (const std::exception&) { ErrorText("Parameter 5 incorrect (Table card 3)"); }

	//Table card 4
	try
	{ SevenCardsInput.Card[5].Number = -1 + stoi(argv[6]); }
	catch (const std::exception&) { ErrorText("Parameter 6 incorrect (Table card 4)"); }

	//Table card 5
	try
	{ SevenCardsInput.Card[6].Number = -1 + stoi(argv[7]); }
	catch (const std::exception&) { ErrorText("Parameter 7 incorrect (Table card 5)"); }

	// checks that the values are between 0 and 51
	if (PlayerCard1 < 0 || PlayerCard1 > 51 ||
		 PlayerCard2 < 0 || PlayerCard2 > 51 ||
		 SevenCardsInput.Card[2].Number < 0 || SevenCardsInput.Card[2].Number > 51 ||
		 SevenCardsInput.Card[3].Number < 0 || SevenCardsInput.Card[3].Number > 51 ||
		 SevenCardsInput.Card[4].Number < 0 || SevenCardsInput.Card[4].Number > 51 ||
		 SevenCardsInput.Card[5].Number < 0 || SevenCardsInput.Card[5].Number > 51 ||
		 SevenCardsInput.Card[6].Number < 0 || SevenCardsInput.Card[6].Number > 51)
	{ ErrorText("Some parameter is not between 1 and 52"); }

	// checks that no card is identical to another
	if (PlayerCard1 == PlayerCard2 ||
		 PlayerCard1 == SevenCardsInput.Card[2].Number ||
		 PlayerCard1 == SevenCardsInput.Card[3].Number ||
		 PlayerCard1 == SevenCardsInput.Card[4].Number ||
		 PlayerCard1 == SevenCardsInput.Card[5].Number ||
		 PlayerCard1 == SevenCardsInput.Card[6].Number ||
		 PlayerCard2 == SevenCardsInput.Card[2].Number ||
		 PlayerCard2 == SevenCardsInput.Card[3].Number ||
		 PlayerCard2 == SevenCardsInput.Card[4].Number ||
		 PlayerCard2 == SevenCardsInput.Card[5].Number ||
		 PlayerCard2 == SevenCardsInput.Card[6].Number ||
		 SevenCardsInput.Card[2].Number == SevenCardsInput.Card[3].Number ||
		 SevenCardsInput.Card[2].Number == SevenCardsInput.Card[4].Number ||
		 SevenCardsInput.Card[2].Number == SevenCardsInput.Card[5].Number ||
		 SevenCardsInput.Card[2].Number == SevenCardsInput.Card[6].Number ||
		 SevenCardsInput.Card[3].Number == SevenCardsInput.Card[4].Number ||
		 SevenCardsInput.Card[3].Number == SevenCardsInput.Card[5].Number ||
		 SevenCardsInput.Card[3].Number == SevenCardsInput.Card[6].Number ||
		 SevenCardsInput.Card[4].Number == SevenCardsInput.Card[5].Number ||
		 SevenCardsInput.Card[4].Number == SevenCardsInput.Card[6].Number ||
		 SevenCardsInput.Card[5].Number == SevenCardsInput.Card[6].Number)
	{ ErrorText("Some parameters are duplicates"); }

	if (PlayerCard1 > PlayerCard2)
	{
		TestCard1 = PlayerCard1;
		PlayerCard1 = PlayerCard2;
		PlayerCard2 = TestCard1;
	}

	// gives all the cards on the table all their values
	SevenCardsInput.Card[2] = FromNumberToCard(SevenCardsInput.Card[2].Number);
	SevenCardsInput.Card[3] = FromNumberToCard(SevenCardsInput.Card[3].Number);
	SevenCardsInput.Card[4] = FromNumberToCard(SevenCardsInput.Card[4].Number);
	SevenCardsInput.Card[5] = FromNumberToCard(SevenCardsInput.Card[5].Number);
	SevenCardsInput.Card[6] = FromNumberToCard(SevenCardsInput.Card[6].Number);

	//Player card 1
	for (SevenCardsInput.Card[0].Number = 0; SevenCardsInput.Card[0].Number < 51; SevenCardsInput.Card[0].Number++)
	{
		if (SevenCardsInput.Card[0].Number == SevenCardsInput.Card[2].Number ||
			 SevenCardsInput.Card[0].Number == SevenCardsInput.Card[3].Number ||
			 SevenCardsInput.Card[0].Number == SevenCardsInput.Card[4].Number ||
			 SevenCardsInput.Card[0].Number == SevenCardsInput.Card[5].Number ||
			 SevenCardsInput.Card[0].Number == SevenCardsInput.Card[6].Number)
		{ continue; }
		SevenCardsInput.Card[0] = FromNumberToCard(SevenCardsInput.Card[0].Number);

		//Player card 2
		for (SevenCardsInput.Card[1].Number = SevenCardsInput.Card[0].Number + 1; SevenCardsInput.Card[1].Number < 52; SevenCardsInput.Card[1].Number++)
		{
			if (SevenCardsInput.Card[1].Number == SevenCardsInput.Card[2].Number ||
				 SevenCardsInput.Card[1].Number == SevenCardsInput.Card[3].Number ||
				 SevenCardsInput.Card[1].Number == SevenCardsInput.Card[4].Number ||
				 SevenCardsInput.Card[1].Number == SevenCardsInput.Card[5].Number ||
				 SevenCardsInput.Card[1].Number == SevenCardsInput.Card[6].Number)
			{ continue; }
			SevenCardsInput.Card[1] = FromNumberToCard(SevenCardsInput.Card[1].Number);

			GenerateRank();
			RankList[SevenCardsInput.Card[0].Number][SevenCardsInput.Card[1].Number] = Rank;
		}
	}

	//testing all combinations against each other
	for (TestCard1 = 0; TestCard1 < 51; TestCard1++)
	{
		for (TestCard2 = TestCard1 + 1; TestCard2 < 52; TestCard2++)
		{
			if (TestCard1 == PlayerCard1 ||
				 TestCard1 == PlayerCard2 ||
				 TestCard2 == PlayerCard1 ||
				 TestCard2 == PlayerCard2 ||
				 RankList[TestCard1][TestCard2] == 0)
			{ continue; }
			Wins += (RankList[PlayerCard1][PlayerCard2] > RankList[TestCard1][TestCard2]);
			Total++;
		}
	}

	//prints win chance in "percent" (1 = 100%, 0.01 = 1%)
	std::cout << std::fixed << std::setprecision(15) << (double)Wins / (double)Total;
	exit(0);
}

void ErrorText(string ErrorString)
{
	std::cout << std::endl;
	std::cout << "ERROR: " << ErrorString << std::endl;
	std::cout << std::endl;
	std::cout << "Help with the parameters:" << std::endl;
	std::cout << "Should be 7 parameters, Player card 1, 2, table card 1, 2, 3, 4, 5" << std::endl;
	std::cout << "All the parameters (cards) must be numbers between 1 and 52. (see table)" << std::endl;
	std::cout << "No duplicates. (same card/number)" << std::endl;
	std::cout << "A space between each parameter." << std::endl;
	std::cout << std::endl;
	std::cout << "Table of cards / numbers (parameters):" << std::endl;
	std::cout << "          2    3    4    5    6    7    8    9    10   Jack  Queen  King  Ace" << std::endl;
	std::cout << "Diamonds  1    2    3    4    5    6    7    8    9    10    11     12    13" << std::endl;
	std::cout << "   Clubs  14   15   16   17   18   19   20   21   22   23    24     25    26" << std::endl;
	std::cout << "  Hearts  27   28   29   30   31   32   33   34   35   36    37     38    39" << std::endl;
	std::cout << "  Spades  40   41   42   43   44   45   46   47   48   49    50     51    52" << std::endl;
	std::cout << std::endl;
	std::cout << "The program was created on 2021-03-25 by GoaXeoN" << std::endl;
	std::cout << "And gives the chance of winning as a percentage with 15 decimal places for the river in texas holdem" << std::endl;
	std::cout << std::endl;
}
