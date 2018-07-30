/**
\file loadeddie_test.cpp
\brief Test dicegame::LoadedDie
\author Ed Sutton
 */

#include "loadeddie.hpp"

#include <CppUTest/TestHarness.h>

#include <limits.h> // UINT_MAX
#include <math.h> // fabs
#include <stdio.h>

using namespace dicegame;

/// Test dicegame::LoadedDie
TEST_GROUP(LoadedDie)
{
    /// Assert the die value is in range 1 to 6
    void assertValidFaceValue(unsigned int faceValue)
    {
        CHECK(1 <= faceValue);
        CHECK(6 >= faceValue);
    }

    /// Expect roll distribution values to be evenly distributed values from 1 to 6
    void checkForExpectedLoadedDieRollDistribution(unsigned int loadedSide, unsigned int loadedSideProbabilityMultiplier, unsigned int rollCount )
    {
        CHECK(6 >= loadedSide);

        LoadedDie die(loadedSide, loadedSideProbabilityMultiplier);
        for (unsigned int i = 0; i < rollCount; ++i)
        {
            die.roll();
            assertValidFaceValue(die.faceValue());
        }

        // Sum of all roll statistics mist match rollCount
        unsigned int statisticsTotalRolls = 0;
        for( int dieSide = 1; dieSide <= 6; ++dieSide)
        {
            statisticsTotalRolls = statisticsTotalRolls + die.rollCountHistory(dieSide);
        }
        CHECK(rollCount == statisticsTotalRolls);

        // If loadedSide=0, then no side loaded.
        // Execute test as loadedSide=1 and loadedSideProbabilityMultiplier = 1
        if( 0 == loadedSide )
        {
            loadedSide = 1;
            loadedSideProbabilityMultiplier = 1;
        }

        // If probability is UINT_MAX the loaded die must account for all roll
        if( UINT_MAX == loadedSideProbabilityMultiplier)
        {
            CHECK(rollCount == die.rollCountHistory(loadedSide));
            return;
        }

        // If loadedSideProbabilityMultiplier is 0 the loaded side must never appear
        if( 0 == loadedSideProbabilityMultiplier)
        {
            CHECK(0 == die.rollCountHistory(loadedSide));
            return;
        }


        // Check probability distribution of all six sides by comparing the ratio of the loaded side to each unloaded side
        float deviationFromExpectedProbabilityTolerance = 0.05;
        for (unsigned int dieSide = 1; dieSide <= 6; ++dieSide )
        {
            if( dieSide == loadedSide)
            {
                continue;
            }

            // Check that loaded side occurrence is xTimes more than each unloaded side
            float measuredLoadedSideProbabilityMultiplier = 0;
            if( 0 < die.rollCountHistory(dieSide) )
            {
                measuredLoadedSideProbabilityMultiplier = (float)die.rollCountHistory(loadedSide) / (float)die.rollCountHistory(dieSide);
            }

            float deviationFromExpectedProbability = (float)(loadedSideProbabilityMultiplier - measuredLoadedSideProbabilityMultiplier) / loadedSideProbabilityMultiplier;
            CHECK(deviationFromExpectedProbabilityTolerance >= deviationFromExpectedProbability );
        }
    }
};

/// \test Expect initial face value to match loaded side when loadedSideProbabilityMultiplier is very high
TEST(LoadedDie, ReturnsValueProvidedAtConstruction)
{
    for(int i = 0; i < 100000; ++i)
    {
        for(int loadedSide = 1; loadedSide <= 6; ++loadedSide)
        {
            unsigned int loadedSideProbabilityMultiplier = UINT_MAX;
            LoadedDie die(loadedSide, loadedSideProbabilityMultiplier);
            CHECK(loadedSide == die.faceValue());
        }

    }
}

/// \test Expect roll distribution values to be evenly distributed values from 1 to 6
TEST(LoadedDie, RollDistributionIsReasonable)
{
    // The higher the rollCount the more accurate the statistics will match the loaded amount
    int rollCount = 100000;

    // When loadedSideProbabilityMultiplier=0, side 1 should never appear
    checkForExpectedLoadedDieRollDistribution(1, 0, rollCount);

    checkForExpectedLoadedDieRollDistribution(1, 1, rollCount);
    checkForExpectedLoadedDieRollDistribution(6, UINT_MAX, rollCount);

    checkForExpectedLoadedDieRollDistribution(3, 2, rollCount);
    checkForExpectedLoadedDieRollDistribution(6, 10, rollCount);

    checkForExpectedLoadedDieRollDistribution(3, 2, rollCount);
    checkForExpectedLoadedDieRollDistribution(6, 10, rollCount);

    // unloaded die
    checkForExpectedLoadedDieRollDistribution(0, 0, rollCount);
    checkForExpectedLoadedDieRollDistribution(0, 10, rollCount);

}

