/**
\file loaddicegameconfiguration_test.cpp
\brief Test dicegame::LoadDiceGameConfiguration
\author Ed Sutton
 */

#include "loaddicegameconfiguration.hpp"

#include "dicegame.hpp" // remove dicegame from configuration test
#include "loadeddie.hpp" // remove loadeddie from configuration test

#include <CppUTest/TestHarness.h>

#include <math.h> // fabs
#include <stdio.h>
#include <string>

using namespace dicegame;
using namespace std;

/// Test dicegame::LoadDiceGameConfiguration class
TEST_GROUP(LoadDiceGameConfiguration)
{
};

/// \test Assert configuration is not valid when no configuration loaded
TEST(LoadDiceGameConfiguration, NoConfigurationIsNotValid)
{
    LoadDiceGameConfiguration loadConfiguration;
    CHECK( false == loadConfiguration.isValid());
}

/// \test Assert configuration is not valid when configuration file not found
TEST(LoadDiceGameConfiguration, MissingConfigurationIsNotValid)
{
    LoadDiceGameConfiguration loadConfiguration;
    string fileName = "this-file-does-not-exist.config";
    loadConfiguration.open(fileName);
    CHECK( false == loadConfiguration.isValid());
}

/// \test Assert values loaded from known configuration match expected values
/// \code
/// NumRolls=100
//
/// Dice=Die1
/// LoadedSide=3
/// LoadAmount=2
//
/// Dice=Die2
/// LoadedSide=6
/// LoadAmount=10
/// \endcode
TEST(LoadDiceGameConfiguration, LoadDiceGameConfig)
{
    LoadDiceGameConfiguration loadConfiguration;
    CHECK( false == loadConfiguration.isValid());

    string fileName = "dicegame.config";
    loadConfiguration.open(fileName);

    CHECK( true == loadConfiguration.isValid());
    CHECK(100 == loadConfiguration.numberOfRolls());
    CHECK(2 == loadConfiguration.dieConfigurationCollection().size());
    CHECK(3 == loadConfiguration.dieConfigurationCollection().at(0).loadedSide);
    CHECK(2 == loadConfiguration.dieConfigurationCollection().at(0).loadAmount);
    CHECK(6 == loadConfiguration.dieConfigurationCollection().at(1).loadedSide);
    CHECK(10 == loadConfiguration.dieConfigurationCollection().at(1).loadAmount);
}

/// \test Assert invalid if numRolls = 0
TEST(LoadDiceGameConfiguration, InvalidNumRolls)
{
    string fileName = "invalid-rolls_0.config";
    LoadDiceGameConfiguration loadConfiguration;
    int result = loadConfiguration.open(fileName);
    CHECK( 0 != result);
}

/// \test Assert invalid if numRolls = 0
TEST(LoadDiceGameConfiguration, InvalidNumRollsNotNumeric)
{
    string fileName = "invalid-numrools-not-numeric.config";
    LoadDiceGameConfiguration loadConfiguration;
    int result = loadConfiguration.open(fileName);
    CHECK( 0 != result);
}

/// \test Assert invalid if dice = 0
TEST(LoadDiceGameConfiguration, InvalidDiceCountZero)
{
    string fileName = "invalid-0dice.config";
    LoadDiceGameConfiguration loadConfiguration;
    int result = loadConfiguration.open(fileName);
    CHECK( 0 != result);
}

/// \test Assert invalid if duplicate Die sections
TEST(LoadDiceGameConfiguration, InvalidDuplicatDie1)
{
    string fileName = "invalid-duplicate-die.config";
    LoadDiceGameConfiguration loadConfiguration;
    int result = loadConfiguration.open(fileName);
    CHECK( 0 != result);
}

/// \test Assert invalid if dice > 2
TEST(LoadDiceGameConfiguration, InvalidDiceCountGreaterThan2)
{
    string fileName = "invalid-3dice.config";
    LoadDiceGameConfiguration loadConfiguration;
    int result = loadConfiguration.open(fileName);
    CHECK( 0 != result);
}

/// \test Assert invalid if dice < 2
TEST(LoadDiceGameConfiguration, InvalidDiceCountLessThan2)
{
    string fileName = "invalid-1dice.config";
    LoadDiceGameConfiguration loadConfiguration;
    int result = loadConfiguration.open(fileName);
    CHECK( 0 != result);
}

/// \test Assert invalid if LoadedSide not numeric
TEST(LoadDiceGameConfiguration, InvalidLoadedSideNotNumeric)
{
    string fileName = "invalid-loadedside-not-numeric.config";
    LoadDiceGameConfiguration loadConfiguration;
    int result = loadConfiguration.open(fileName);
    CHECK( 0 != result);
}
/// \test Assert invalid if LoadedSide not numeric
TEST(LoadDiceGameConfiguration, InvalidLoadAmountNotNumeric)
{
    string fileName = "invalid-loadamount-not-numeric.config";
    LoadDiceGameConfiguration loadConfiguration;
    int result = loadConfiguration.open(fileName);
    CHECK( 0 != result);
}

/// \test Assert invalid if too many '=" on one line
TEST(LoadDiceGameConfiguration, InvalidTooManyEqualSigns)
{
    string fileName = "invalid-too-many-equal-signs.config";
    LoadDiceGameConfiguration loadConfiguration;
    int result = loadConfiguration.open(fileName);
    CHECK( 0 != result);
}

/// \test Assert invalid if missing Dice section
TEST(LoadDiceGameConfiguration, InvalidMissingDiceSection)
{
    string fileName = "invalid-missing-dice-section.config";
    LoadDiceGameConfiguration loadConfiguration;
    int result = loadConfiguration.open(fileName);
    CHECK( 0 != result);
}
/// \test Assert loadedSide negative is not valid
TEST(LoadDiceGameConfiguration, InvalidLoadedSide)
{
    string fileName = "loaded-side-negative.config";
    LoadDiceGameConfiguration loadConfiguration;
    int result = loadConfiguration.open(fileName);
    CHECK( 0 != result);
}
/// \test Assert loadedSide negative is not valid
TEST(LoadDiceGameConfiguration, InvalidLoadedSideNegative)
{
    string fileName = "loaded-side-negative.config";
    LoadDiceGameConfiguration loadConfiguration;
    int result = loadConfiguration.open(fileName);
    CHECK( 0 != result);
}



