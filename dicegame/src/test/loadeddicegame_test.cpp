
/**
\file loadeddicegame_test.cpp
\brief Test dicegame::LoadedDiceGame
\author Ed Sutton
 */

#include <string>
#include "loadeddicegame.hpp"

#include <CppUTest/TestHarness.h>

using namespace std;
using namespace dicegame;

/// Test dicegame::LoadedDiceGame
TEST_GROUP(LoadedDiceGame)
{
};

/// \test Game does not return 0 if file not found
TEST(LoadedDiceGame, ConfigFileNotFound)
{
    // Play the loaded dice game using configuration file

    string fileName = "/file/does/not/exist/dice.config";
    LoadedDiceGame diceGame;
    int result = diceGame.play(fileName);
    CHECK( 0 != result );
}

///// \test Game does not return 0 if config file invalid
//TEST(LoadedDiceGame, InvalidConfigDie3)
//{
//    // Play the loaded dice game using configuration file
//
//    string fileName = "invalid-die3.config";
//    LoadedDiceGame diceGame;
//    int result = diceGame.play(fileName);
//    CHECK( 0 != result );
//}

/// \test Game returns 0 when playing a valid configuration file
TEST(LoadedDiceGame, ValidConfig)
{
    // Play the loaded dice game using configuration file

    string fileName = "dicegame.config";
    LoadedDiceGame diceGame;
    int result = diceGame.play(fileName);
    CHECK( 0 == result );
}
