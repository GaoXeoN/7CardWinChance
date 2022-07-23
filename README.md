2021 / C++
# 7 Card Win Chance

### A program that calculates the probability of winning with 7 cards (River) in Texas Holdem.
The program calculates all combinations with one opponent and is therefore very demanding.
When I started this project I was using Python and it was a lot of if statements and loops doing the same things over and over again.
The program was incredibly slow so I switched to C++ and replaced many of the if statements with true/false queries, which made the program much faster. then I created an array structure where I sorted the sorts into new sorts. (doubles, triples quarters) which caused the program to need even fewer if statements and loops.
I haven't done any measurements, but I can probably say that from the first to the last version, the speed has decreased by a few thousand times.
because it' s so structured with arrays within arrays, true/false requests instead of if statements and optimization of loops, this is (at the time of writing) the most advanced project I've done and the one I'm most proud of.

### How to make it:
1) import both files into a new blank C++ project in Visual Studio (2019 or newer)
2) compile and you have an exe file (check the output window and you will see where on the hard drive it is created)
3) done

### How to use:
1) start a command prompt or a powershell window
2) change the path to where the exe file is located
3) write the file name followed by 7 numbers with spaces in between

each card has a unique number between 0 and 51
           2   3   4   5   6   7   8   9   10  Jack Queen King Ace
Diamonds   0   1   2   3   4   5   6   7   8   9    10    11   12
   Clubs   13  14  15  16  17  18  19  20  21  22   23    24   25
  Hearts   26  27  28  29  30  31  32  33  34  35   36    37   38
  Spades   39  40  41  42  43  44  45  46  47  48   49    50   51

example:
C:\>7card.exe 31 25 50 37 34 49 6
0.298989898989899
Results: 29,89% chance to win
