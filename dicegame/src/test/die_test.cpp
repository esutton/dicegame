/**
\file die_test.cpp
\brief Test dicegame::Die
\author Ed Sutton
 */

#include "die.hpp"

#include <CppUTest/TestHarness.h>
#include <stdio.h>
#include <time.h>       // time, clock


using namespace dicegame;


/// Test dicegame::Die class
TEST_GROUP(Die)
{
    /// A single dice
    Die die;

    /// Assert the die value is in range 1 to 6
    void assertValidFaceValue()
    {
        CHECK(die.faceValue() >= 1);
        CHECK(die.faceValue() <= 6);
    }
};

/// \test Assert faceValue after instantiation to be a value from 1 to 6
TEST(Die, InitialValueAfterCreationIsValid)
{
    assertValidFaceValue();
}


/// \test Assert faceValue after instantiation to be a value from 1 to 6
TEST(Die, DiceHasSixSides)
{
    CHECK(6 == die.numberOfSides());
}

/// \test Assert roll count history not zero for valid sides
TEST(Die, RollCountHistoryNotZeroForValidSides)
{
    for (int i = 0; i < 10000; ++i)
    {
        die.roll();
        assertValidFaceValue();;
    }

    for(int side = 1; side <= 6; ++side)
    {
        int rollCountHistory = die.rollCountHistory(side);
        CHECK(0 != rollCountHistory);
    }
}

/// \test Assert roll count history zero for invalid sides
TEST(Die, RollCountHistoryZeroForInvalidSides)
{
    for (int i = 0; i < 10000; ++i)
    {
        die.roll();
        assertValidFaceValue();;
    }

    int rollCountHistory = die.rollCountHistory(-1);
    CHECK(0 == rollCountHistory);
    rollCountHistory = die.rollCountHistory(0);
    CHECK(0 == rollCountHistory);
    rollCountHistory = die.rollCountHistory(7);
    CHECK(0 == rollCountHistory);
}

/// \test All rolls to return values from 1 to 6
TEST(Die, ValuesRolledValid)
{
    for (int i = 0; i < 60000; ++i)
    {
        die.roll();
        assertValidFaceValue();;
    }
}

/// \test Assert roll distribution values to be evenly distributed values from 1 to 6
/// \remarks The fewer the rolls, the more uneven the distribution
TEST(Die, RollDistributionIsReasonable)
{
    int valuesRolled[6] = {0};
    for (int i = 0; i < 60000; ++i)
    {
        die.roll();
        ++valuesRolled[die.faceValue() - 1];
        assertValidFaceValue();
    }

    // Check distribution
    for (int i = 0; i < 6; ++i)
    {
        CHECK(valuesRolled[i] >= 9500);
    }
}

/// \test Assert initial dice state to be random
TEST(Die, InitialValueIsRandom)
{
    int lastValue = 0;
    int i = 0;
    for (i = 0; i < 100; ++i)
    {
        Die die;
        if( 0 != lastValue && die.faceValue() != lastValue )
        {
            // success
            return;
        }
        lastValue = die.faceValue();

        // Add time delay to insure seed value used by Die has changed from previous
        // Without this, testing under RHEL 5.2 VM fails this test because
        // same clock value is used as random seed for multiple iterations
        long timeValue = time(0);
        while( timeValue == time(0)) {};
    }

    printf("value[%i] = %i\n", i, die.faceValue());
    FAIL("Initial values not random");
}


