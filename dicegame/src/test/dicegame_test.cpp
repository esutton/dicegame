/**
\file dicegame_test.cpp
\brief Test dicegame::DiceGame
\author Ed Sutton
 */

#include "dicegame.hpp"
#include "loadeddie.hpp"

#include <CppUTest/TestHarness.h>


using namespace dicegame;

/// Test dicegame::DiceGame
TEST_GROUP(DiceGame)
{
};

/// \test Assert roll distribution is reasonable match for loaded dies used
TEST(DiceGame, PlayAGame)
{
    int numRolls = 100;
    int die1LoadedSide = 3;
    int die1LoadedAmount = 2;
    int die2LoadedSide = 6;
    int die2LoadedAmount = 10;

    LoadedDie *die1 = new LoadedDie(die1LoadedSide, die1LoadedAmount);
    LoadedDie *die2 = new LoadedDie(die2LoadedSide, die2LoadedAmount);
    DiceGame diceGame;
    diceGame.addDie(die1);
    diceGame.addDie(die2);
    for(int throwCount = 1; throwCount <= numRolls; ++throwCount)
    {
        diceGame.play();
    }

#if 0 // Debug print stats
    const DiceGame::dieCollection_t dieCollection = diceGame.dieCollection();
    for(unsigned int dieIndex = 0; dieIndex < dieCollection.size(); ++dieIndex)
    {
        printf("\nDie%i Statistics for %i rolls:\n", dieIndex+1, numRolls);
        for(int dieSide = 1; dieSide <= 6; ++dieSide)
        {
            printf("Side %i: %4.1f%%\n",
                   dieSide, (100.0f * dieCollection[dieIndex]->rollCountHistory(dieSide))/(float)numRolls);
        }
    }
#endif
}
