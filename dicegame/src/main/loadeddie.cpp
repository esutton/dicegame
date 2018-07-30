/*
 * loadeddie.cpp
 *
 *      Author: esutton
 */

#include "loadeddie.hpp"

#include <assert.h>
#include <limits.h> // UINT_MAX

using namespace dicegame;

/**
 * \class dicegame::LoadedDie
 *
 * Simulates a six sided loaded die as a roulette wheel that has N-possibilities.
 * The loaded side is simulated by creating loadedSideProbabilityMultiplier-1 duplicates
 * of the die's loadedSide.
 * - If loadedSideProbabilityMultiplier == 0, then loaded side will never appear
 * - If loadedSideProbabilityMultiplier == UINT_MAX, then loaded side will always appear
 * - If loadedSide == 0, then die is not a loaded die and will behave normally
 *
 * For example, to load the 3 side of the dice so that it is twice as likely to occur,
 * 2x duplicates of side 3 are created.  Effectively a 7-sided dice with two side 3's,
 * or more realistically a roulette wheel with 7 numbers of which two are duplicated 3's.
 *
 * Example: loadedSide = 3, loadedSideProbabilityMultiplier = 2
 *
 * | Side 1 | Side 2 | Side 3 | Side 3 | Side 4 | Side 5 | Side 6 |
 * |--------| -------|--------|--------|--------|--------|--------|
 * | 1      | 2      | 3      | 3      | 4      | 5      | 6      |
 */

/**
 * Creates a LoadeDie
 *
 * @param loadedSide the side of the dice 1-6 that should appear more frequently. Use 0 to create an unloaded die.
 * @param loadedSideProbabilityMultiplier the probability multiplier that increases the chances
 *        N-times that the loaded side will appear.
 *        Set to 0 to never appear.  Set to UINT_MAX to always appear.
 */
LoadedDie::LoadedDie(unsigned int loadedSide, unsigned int loadedSideProbabilityMultiplier) :
        m_loadedSide(loadedSide),
        m_loadedSideProbabilityMultiplier(loadedSideProbabilityMultiplier)
{
    // load the die then roll once to generate an initial non-constant loaded-die value
    loadDie(m_loadedSide, m_loadedSideProbabilityMultiplier );
    roll();
    // zero statistics
    for(int i = 0; i < 6; ++i)
    {
        m_statistics[i] = 0;
    }
}

/// Destructor
LoadedDie::~LoadedDie()
{
    // TODO Auto-generated destructor stub
}



/**
 * Simulate six sided die as a roulette wheel that has m_possibilities.
 * The loaded side is simulated by creating loadedSideProbabilityMultiplier-1 duplicates
 * of the die's loadedSide.
 * \todo Research statistics and probabilities equations to see if there is a better
 * "more mathematical" way to implement this.
 * @param loadedSide the side of the dice that should more frequently appear
 * @param loadedSideProbabilityMultiplier the probability multiplier that increases the chances
 * the loaded side will appear.
 */
void LoadedDie::loadDie(unsigned int loadedSide, unsigned int loadedSideProbabilityMultiplier)
{
    assert( 6 >= loadedSide );

    // Allow loadedSide=0 to be used to specify an unloaded die
    if(0 < loadedSide)
    {
        m_numberOfSides = m_numberOfSides + loadedSideProbabilityMultiplier - 1;
    }

    int thresholdValue = 0;
    for( unsigned int dieSide = 1; dieSide <= 6; ++dieSide )
    {
        if( dieSide == loadedSide )
        {
            // The loaded side will have a wider thresholdValue to load the die
            thresholdValue = thresholdValue + loadedSideProbabilityMultiplier;
        }
        else
        {
            thresholdValue = thresholdValue + 1;
        }

        m_loadedSideThresholds[dieSide-1] = thresholdValue;
    }
}

/// Rolls the dice and returns a resulting value in the range of 1 - 6
/// \returns value 1 through 6
int LoadedDie::roll()
{
    // If UINT_MAX always return laded side
    if(UINT_MAX == m_loadedSideProbabilityMultiplier)
    {
        m_rollValue = m_loadedSide;
        ++m_statistics[m_rollValue-1];
        return m_rollValue;
    }

    // generate random number between 1 and m_possibilities
    // and translate into the loaded die's rollvalue
    int chanceValue = randomGenerator() % m_numberOfSides + 1;
    for( int i = 0; i < 6; ++i )
    {
        if( chanceValue <= m_loadedSideThresholds[i] )
        {
            // Make sure we never see the loaded side when m_loadedSideProbabilityMultiplier = 0;
            assert(false == (0 == m_loadedSideProbabilityMultiplier && i+1 == m_loadedSide));

            m_rollValue = i + 1;
            ++m_statistics[m_rollValue-1];
            return m_rollValue;
        }
    }

    // we should never get here, return last roll value if we do
    assert(false);
    return m_rollValue;
}



