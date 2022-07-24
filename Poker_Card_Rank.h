/*
2021-01-02 made by GoaXeoN
Poker Card Rank C++ add-on
extension calculates the rank of a set of 7 cards

each card has a unique number between 0 and 51
Table N:
           2   3   4   5   6   7   8   9   10  Jack Queen King Ace
Diamonds   0   1   2   3   4   5   6   7   8   9    10    11   12
   Clubs   13  14  15  16  17  18  19  20  21  22   23    24   25
  Hearts   26  27  28  29  30  31  32  33  34  35   36    37   38
  Spades   39  40  41  42  43  44  45  46  47  48   49    50   51

cards 2-10, Jack, Queen, King, Ace have the following values:
Table V:
    2   3   4   5   6   7   8   9   10  Jack Queen King Ace
    0   1   2   3   4   5   6   7   8    9    10    11   12

each suit(color) has its own value:
Table C:
    Diamonds Clubs Hearts Spades
     0        1     2      3

Each set has its own rank level (higher wins over lower)
Table RL:
    Royal Straight Flush   Straight Flush   Four of a Kind   Full House   Flush
     9                      8                7                6            5
	  
    Straight   Three of a Kind   Two Pairs   One Pair   Value Cards
     4          3                 2           1          0

1. assign all 7 cards in SevenCardInput with a unique card and number of cards
   (SevenCardsInput.Card[0] to SevenCardsInput.Card[6])
   (SevenCardsInput.Card[x].Number = N (see table N))
   (SevenCardsInput.Card[x].Value = N (see table V))
   (SevenCardsInput.Card[x].Color = N (see table C))
   (SevenCardsInput.NumberOfCards = 7)
3. call the function GenerateRank();
4. SevenCardsResults contains the 5 best cards in order from the 7 from SevenCardsInput
   RankLevel tells the rank level of the SevenCardsResults (see table RL)
   Rank tells the rank of the SevenCardsResults, higher rank wins over lower
   (Rank is a calculation of RankLevel and the value of the cards in their order)
*/

struct OneCardStruct
{
    int Number = 0;
    short Value = 0;
    short Color = 0;
};
struct SevenCardsStruct
{
    short NumberOfCards = 0;
    OneCardStruct Card[8];
};
struct CardListRowStruct
{
    short NumberOfCards = 0;
    OneCardStruct Card[4];
};
struct CardListStruct
{
    short NumberOfRows = 0;
    CardListRowStruct Row[7];
};

//struct variable:
OneCardStruct OneCard;
SevenCardsStruct SevenCardsInput;
SevenCardsStruct SevenCardsInOrder;
SevenCardsStruct SevenCardsTemp;
SevenCardsStruct SevenCardsResults;
CardListStruct CardListValue;
CardListStruct CardListDuplicate;

//regular variable:
short Value;
short Color;
short CardNumber;
short StartPosition;
short FastIf; //returns 0 or 1 from an "if" request
short RankLevel;
int Rank;

//function declaration
void GenerateRank();
void SummarizeRankLevelAndCardValue();
OneCardStruct FromNumberToCard(short Number);

// figures out if the card has a set (full house, suit, straight etc) and then figures out what rank it has
void GenerateRank()
{
    // preliminary work: put all the cards in order of size
    RankLevel = 0;
    SevenCardsInOrder.NumberOfCards = 0;
    for (Value = 12; Value > -1; Value--)
    {
        for (CardNumber = 0; CardNumber < 7; CardNumber++)
        {
            FastIf = (SevenCardsInput.Card[CardNumber].Value == Value);
            SevenCardsInOrder.Card[SevenCardsInOrder.NumberOfCards] = SevenCardsInput.Card[CardNumber];
            SevenCardsInOrder.NumberOfCards += FastIf;
        }
    }

    // check for flush
    for (Color = 0; Color < 4; Color++)
    {
        SevenCardsTemp.NumberOfCards = 0;
        for (CardNumber = 0; CardNumber < 7; CardNumber++)
        {
            FastIf = (SevenCardsInOrder.Card[CardNumber].Color == Color);
            SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards] = SevenCardsInOrder.Card[CardNumber];
            SevenCardsTemp.NumberOfCards += FastIf;
        }
        if (SevenCardsTemp.NumberOfCards > 4) { goto CheckForRoyalStraightFlush; }
    }
    goto CheckForFourOfAKind;

CheckForRoyalStraightFlush:
    StartPosition = -1;
    FastIf = ((SevenCardsTemp.Card[0].Value == SevenCardsTemp.Card[1].Value + 1) &&
        (SevenCardsTemp.Card[1].Value == SevenCardsTemp.Card[2].Value + 1) &&
        (SevenCardsTemp.Card[2].Value == SevenCardsTemp.Card[3].Value + 1) &&
        (SevenCardsTemp.Card[3].Value == SevenCardsTemp.Card[4].Value + 1));
    StartPosition += (1 * FastIf);
    FastIf = ((StartPosition == -1) && (SevenCardsTemp.NumberOfCards > 5) &&
        (SevenCardsTemp.Card[1].Value == SevenCardsTemp.Card[2].Value + 1) &&
        (SevenCardsTemp.Card[2].Value == SevenCardsTemp.Card[3].Value + 1) &&
        (SevenCardsTemp.Card[3].Value == SevenCardsTemp.Card[4].Value + 1) &&
        (SevenCardsTemp.Card[4].Value == SevenCardsTemp.Card[5].Value + 1));
    StartPosition += (2 * FastIf);
    FastIf = ((StartPosition == -1) && (SevenCardsTemp.NumberOfCards == 7) &&
        (SevenCardsTemp.Card[2].Value == SevenCardsTemp.Card[3].Value + 1) &&
        (SevenCardsTemp.Card[3].Value == SevenCardsTemp.Card[4].Value + 1) &&
        (SevenCardsTemp.Card[4].Value == SevenCardsTemp.Card[5].Value + 1) &&
        (SevenCardsTemp.Card[5].Value == SevenCardsTemp.Card[6].Value + 1));
    StartPosition += (3 * FastIf);
    if (StartPosition > -1)
    {
        SevenCardsResults.Card[0] = SevenCardsTemp.Card[0 + StartPosition];
        SevenCardsResults.Card[1] = SevenCardsTemp.Card[1 + StartPosition];
        SevenCardsResults.Card[2] = SevenCardsTemp.Card[2 + StartPosition];
        SevenCardsResults.Card[3] = SevenCardsTemp.Card[3 + StartPosition];
        SevenCardsResults.Card[4] = SevenCardsTemp.Card[4 + StartPosition];
        SevenCardsResults.NumberOfCards = 5;
        FastIf = (SevenCardsResults.Card[0].Value == 12);
        RankLevel = 8 + FastIf; // (9) royal straight flush or (8) straight flush is found
        SummarizeRankLevelAndCardValue();
        return;
    }

    // check for small straight flush (A,2,3,4,5)
    if ((SevenCardsTemp.Card[0].Value == 12) &&
        (SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 1].Value == 0) &&
        (SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 2].Value == 1) &&
        (SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 3].Value == 2) &&
        (SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 4].Value == 3))
    {
        SevenCardsResults.Card[0] = SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 4];
        SevenCardsResults.Card[1] = SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 3];
        SevenCardsResults.Card[2] = SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 2];
        SevenCardsResults.Card[3] = SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 1];
        SevenCardsResults.Card[4] = SevenCardsTemp.Card[0];
        SevenCardsResults.NumberOfCards = 5;
        RankLevel = 8;
        SummarizeRankLevelAndCardValue();
        return;
    }

CheckForFourOfAKind:
    //preliminary work
    //make a table with all cards with the same value on the same row (each value of existing cards has its own row)
    //adds the first value
    CardListValue.NumberOfRows = 1;
    CardListValue.Row[0].NumberOfCards = 1;
    CardListValue.Row[0].Card[0] = SevenCardsInOrder.Card[0];
    //zero the other rows
    CardListValue.Row[1].NumberOfCards = 0;
    CardListValue.Row[2].NumberOfCards = 0;
    CardListValue.Row[3].NumberOfCards = 0;
    CardListValue.Row[4].NumberOfCards = 0;
    CardListValue.Row[5].NumberOfCards = 0;
    CardListValue.Row[6].NumberOfCards = 0;
    //puts each card in its respective row
    for (CardNumber = 1; CardNumber < 7; CardNumber++)
    {
        FastIf = (SevenCardsInOrder.Card[CardNumber].Value != CardListValue.Row[CardListValue.NumberOfRows - 1].Card[0].Value);
        CardListValue.NumberOfRows += FastIf;
        CardListValue.Row[CardListValue.NumberOfRows - 1].Card[CardListValue.Row[CardListValue.NumberOfRows - 1].NumberOfCards] = SevenCardsInOrder.Card[CardNumber];
        CardListValue.Row[CardListValue.NumberOfRows - 1].NumberOfCards++;
    }
    //make a table of duplicates, triplicates, etc.
    CardListDuplicate.NumberOfRows = 0;
    //first adds all "four of a kind"
    for (CardNumber = 0; CardNumber < 4; CardNumber++)
    {
        FastIf = (CardListValue.Row[CardNumber].NumberOfCards == 4);
        CardListDuplicate.Row[CardListDuplicate.NumberOfRows] = CardListValue.Row[CardNumber];
        CardListDuplicate.NumberOfRows += FastIf;
    }
    //add all "three of a kind" under "four of a kind"
    for (CardNumber = 0; CardNumber < 5; CardNumber++)
    {
        FastIf = (CardListValue.Row[CardNumber].NumberOfCards == 3);
        CardListDuplicate.Row[CardListDuplicate.NumberOfRows] = CardListValue.Row[CardNumber];
        CardListDuplicate.NumberOfRows += FastIf;
    }
    //add all "one pair" under "three of a kind"
    for (CardNumber = 0; CardNumber < 6; CardNumber++)
    {
        FastIf = (CardListValue.Row[CardNumber].NumberOfCards == 2);
        CardListDuplicate.Row[CardListDuplicate.NumberOfRows] = CardListValue.Row[CardNumber];
        CardListDuplicate.NumberOfRows += FastIf;
    }
    //adds all "single" cards at the bottom
    for (CardNumber = 0; CardNumber < 7; CardNumber++)
    {
        FastIf = (CardListValue.Row[CardNumber].NumberOfCards == 1);
        CardListDuplicate.Row[CardListDuplicate.NumberOfRows] = CardListValue.Row[CardNumber];
        CardListDuplicate.NumberOfRows += FastIf;
    }

    // check for four of a kind
    if (CardListDuplicate.Row[0].NumberOfCards == 4)
    {
        SevenCardsResults.Card[0] = CardListDuplicate.Row[0].Card[0];
        SevenCardsResults.Card[1] = CardListDuplicate.Row[0].Card[1];
        SevenCardsResults.Card[2] = CardListDuplicate.Row[0].Card[2];
        SevenCardsResults.Card[3] = CardListDuplicate.Row[0].Card[3];
        SevenCardsResults.NumberOfCards = 4;
        for (CardNumber = 0; SevenCardsResults.NumberOfCards < 5; CardNumber++)
        {
            FastIf = (SevenCardsInOrder.Card[CardNumber].Value != SevenCardsResults.Card[0].Value);
            SevenCardsResults.Card[SevenCardsResults.NumberOfCards] = SevenCardsInOrder.Card[CardNumber];
            SevenCardsResults.NumberOfCards += FastIf;
        }
        RankLevel = 7; // (7) four of a kind is found
        SummarizeRankLevelAndCardValue();
        return;
    }

    // check for full house
    if (CardListDuplicate.Row[0].NumberOfCards == 3 && CardListDuplicate.Row[1].NumberOfCards > 1)
    {
        SevenCardsResults.Card[0] = CardListDuplicate.Row[0].Card[0];
        SevenCardsResults.Card[1] = CardListDuplicate.Row[0].Card[1];
        SevenCardsResults.Card[2] = CardListDuplicate.Row[0].Card[2];
        SevenCardsResults.Card[3] = CardListDuplicate.Row[1].Card[0];
        SevenCardsResults.Card[4] = CardListDuplicate.Row[1].Card[1];
        SevenCardsResults.NumberOfCards = 5;
        RankLevel = 6; // (6) full house is found
        SummarizeRankLevelAndCardValue();
        return;
    }

    // check for flush
    if (SevenCardsTemp.NumberOfCards > 4)
    {
        SevenCardsResults.Card[0] = SevenCardsTemp.Card[0];
        SevenCardsResults.Card[1] = SevenCardsTemp.Card[1];
        SevenCardsResults.Card[2] = SevenCardsTemp.Card[2];
        SevenCardsResults.Card[3] = SevenCardsTemp.Card[3];
        SevenCardsResults.Card[4] = SevenCardsTemp.Card[4];
        SevenCardsResults.NumberOfCards = 5;
        RankLevel = 5; // (5) flush is found
        SummarizeRankLevelAndCardValue();
        return;
    }

    // check for straight
    SevenCardsTemp.Card[0] = SevenCardsInOrder.Card[0];
    SevenCardsTemp.NumberOfCards = 1;
    for (CardNumber = 1; CardNumber < 7; CardNumber++)
    {
        FastIf = (SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 1].Value != SevenCardsInOrder.Card[CardNumber].Value);
        SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards] = SevenCardsInOrder.Card[CardNumber];
        SevenCardsTemp.NumberOfCards += FastIf;
    }
    StartPosition = -1;
    FastIf = ((SevenCardsTemp.NumberOfCards > 4) &&
        (SevenCardsTemp.Card[0].Value == SevenCardsTemp.Card[1].Value + 1) &&
        (SevenCardsTemp.Card[1].Value == SevenCardsTemp.Card[2].Value + 1) &&
        (SevenCardsTemp.Card[2].Value == SevenCardsTemp.Card[3].Value + 1) &&
        (SevenCardsTemp.Card[3].Value == SevenCardsTemp.Card[4].Value + 1));
    StartPosition += (1 * FastIf);
    FastIf = ((StartPosition == -1) && (SevenCardsTemp.NumberOfCards > 5) &&
        (SevenCardsTemp.Card[1].Value == SevenCardsTemp.Card[2].Value + 1) &&
        (SevenCardsTemp.Card[2].Value == SevenCardsTemp.Card[3].Value + 1) &&
        (SevenCardsTemp.Card[3].Value == SevenCardsTemp.Card[4].Value + 1) &&
        (SevenCardsTemp.Card[4].Value == SevenCardsTemp.Card[5].Value + 1));
    StartPosition += (2 * FastIf);
    FastIf = ((StartPosition == -1) && (SevenCardsTemp.NumberOfCards == 7) &&
        (SevenCardsTemp.Card[2].Value == SevenCardsTemp.Card[3].Value + 1) &&
        (SevenCardsTemp.Card[3].Value == SevenCardsTemp.Card[4].Value + 1) &&
        (SevenCardsTemp.Card[4].Value == SevenCardsTemp.Card[5].Value + 1) &&
        (SevenCardsTemp.Card[5].Value == SevenCardsTemp.Card[6].Value + 1));
    StartPosition += (3 * FastIf);
    if (StartPosition > -1)
    {
        SevenCardsResults.Card[0] = SevenCardsTemp.Card[0 + StartPosition];
        SevenCardsResults.Card[1] = SevenCardsTemp.Card[1 + StartPosition];
        SevenCardsResults.Card[2] = SevenCardsTemp.Card[2 + StartPosition];
        SevenCardsResults.Card[3] = SevenCardsTemp.Card[3 + StartPosition];
        SevenCardsResults.Card[4] = SevenCardsTemp.Card[4 + StartPosition];
        SevenCardsResults.NumberOfCards = 5;
        RankLevel = 4; // (4) straight is found
        SummarizeRankLevelAndCardValue();
        return;
    }

    // check for small straight (A,2,3,4,5)
    if ((SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 4].Value == 3) &&
        (SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 3].Value == 2) &&
        (SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 2].Value == 1) &&
        (SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 1].Value == 0) &&
        (SevenCardsTemp.Card[0].Value == 12))
    {
        SevenCardsResults.Card[0] = SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 4];
        SevenCardsResults.Card[1] = SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 3];
        SevenCardsResults.Card[2] = SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 2];
        SevenCardsResults.Card[3] = SevenCardsTemp.Card[SevenCardsTemp.NumberOfCards - 1];
        SevenCardsResults.Card[4] = SevenCardsTemp.Card[0];
        SevenCardsResults.NumberOfCards = 5;
        RankLevel = 4; // (4) straight is found
        SummarizeRankLevelAndCardValue();
        return;
    }

    // check for three of a kind
    if (CardListDuplicate.Row[0].NumberOfCards == 3)
    {
        SevenCardsResults.Card[0] = CardListDuplicate.Row[0].Card[0];
        SevenCardsResults.Card[1] = CardListDuplicate.Row[0].Card[1];
        SevenCardsResults.Card[2] = CardListDuplicate.Row[0].Card[2];
        SevenCardsResults.NumberOfCards = 3;
        for (CardNumber = 0; SevenCardsResults.NumberOfCards < 5; CardNumber++)
        {
            FastIf = (SevenCardsInOrder.Card[CardNumber].Value != SevenCardsResults.Card[0].Value);
            SevenCardsResults.Card[SevenCardsResults.NumberOfCards] = SevenCardsInOrder.Card[CardNumber];
            SevenCardsResults.NumberOfCards += FastIf;
        }
        RankLevel = 3; // (3) three is found
        SummarizeRankLevelAndCardValue();
        return;
    }

    // check for two	pair
    if (CardListDuplicate.Row[0].NumberOfCards == 2 && CardListDuplicate.Row[1].NumberOfCards == 2)
    {
        SevenCardsResults.Card[0] = CardListDuplicate.Row[0].Card[0];
        SevenCardsResults.Card[1] = CardListDuplicate.Row[0].Card[1];
        SevenCardsResults.Card[2] = CardListDuplicate.Row[1].Card[0];
        SevenCardsResults.Card[3] = CardListDuplicate.Row[1].Card[1];
        SevenCardsResults.NumberOfCards = 4;
        for (CardNumber = 0; SevenCardsResults.NumberOfCards < 5; CardNumber++)
        {
            FastIf = ((SevenCardsInOrder.Card[CardNumber].Value != SevenCardsResults.Card[0].Value) && (SevenCardsInOrder.Card[CardNumber].Value != SevenCardsResults.Card[2].Value));
            SevenCardsResults.Card[SevenCardsResults.NumberOfCards] = SevenCardsInOrder.Card[CardNumber];
            SevenCardsResults.NumberOfCards += FastIf;
        }
        RankLevel = 2; // (2) two pair is found
        SummarizeRankLevelAndCardValue();
        return;
    }

    // check for one pair
    if (CardListDuplicate.Row[0].NumberOfCards == 2)
    {
        SevenCardsResults.Card[0] = CardListDuplicate.Row[0].Card[0];
        SevenCardsResults.Card[1] = CardListDuplicate.Row[0].Card[1];
        SevenCardsResults.NumberOfCards = 2;
        for (CardNumber = 0; SevenCardsResults.NumberOfCards < 5; CardNumber++)
        {
            FastIf = (SevenCardsInOrder.Card[CardNumber].Value != SevenCardsResults.Card[0].Value);
            SevenCardsResults.Card[SevenCardsResults.NumberOfCards] = SevenCardsInOrder.Card[CardNumber];
            SevenCardsResults.NumberOfCards += FastIf;
        }
        RankLevel = 1; // (1) one pair is found
        SummarizeRankLevelAndCardValue();
        return;
    }

    // check for value cards
    SevenCardsResults.Card[0] = SevenCardsInOrder.Card[0];
    SevenCardsResults.Card[1] = SevenCardsInOrder.Card[1];
    SevenCardsResults.Card[2] = SevenCardsInOrder.Card[2];
    SevenCardsResults.Card[3] = SevenCardsInOrder.Card[3];
    SevenCardsResults.Card[4] = SevenCardsInOrder.Card[4];
    RankLevel = 0; // (0) all value cards is found
    SummarizeRankLevelAndCardValue();
    return;
}

void SummarizeRankLevelAndCardValue()
{
    Rank = ((RankLevel + 1) * 1000000);
    Rank += ((SevenCardsResults.Card[0].Value + 1) * 38416);
    Rank += ((SevenCardsResults.Card[1].Value + 1) * 2744);
    Rank += ((SevenCardsResults.Card[2].Value + 1) * 196);
    Rank += ((SevenCardsResults.Card[3].Value + 1) * 14);
    Rank += (SevenCardsResults.Card[4].Value + 1);
}

OneCardStruct FromNumberToCard(short Number)
{
    OneCard.Value = OneCard.Number = Number; OneCard.Color = 0;
    FastIf = (OneCard.Value > 12); OneCard.Value -= (13 * FastIf); OneCard.Color += FastIf;
    FastIf = (OneCard.Value > 12); OneCard.Value -= (13 * FastIf); OneCard.Color += FastIf;
    FastIf = (OneCard.Value > 12); OneCard.Value -= (13 * FastIf); OneCard.Color += FastIf;
    return OneCard;
}
