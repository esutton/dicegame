/*
 * die.cpp
 *
 *      Author: esutton
 */

#include "die.hpp"

#include <assert.h>
// If using C++11 prefer std::uniform_int_distribution) to rand
#include <stdlib.h>     /* srand, rand */
#include <time.h>       // time, clock

using namespace dicegame;

/// \class dicegame::Die
/// \brief A six sided die used in dicegame::DiceGame
///
/// Keeps a Die::rollCountHistory of how many times each side of the dice has appeared

/**
 * Creates a six-sided die by default
 * @param numberOfSides - defaults to 6
 */
Die::Die(int numberOfSides /* = 6 */) :
        m_rollValue(0),
        m_numberOfSides(numberOfSides)
{
    // initialize random seed and use roll to random initialize.
    srand(time(0));
    roll();
}

/// Destructor
Die::~Die()
{
}

/// The current die face value from last roll
int Die::faceValue() const { return m_rollValue; }

/// The number of sides on the dice; typically 6.
int Die::numberOfSides() const { return m_numberOfSides; }

/// Returns a random integer
/// \todo: If using C++11 prefer std::uniform_int_distribution) to rand
int Die::randomGenerator() { return rand(); }

/// generate random number between 1 and number of sides in the dice
int Die::roll()
{
    m_rollValue = rand() % m_numberOfSides + 1;
    return m_rollValue;
}

/**
 * Returns the number of rolls the specified die side has landed on
 * @param dieSide
 * @return the number of rolls the specified die side has landed on
 */
unsigned int Die::rollCountHistory(int dieSide)
{
    if( 1 > dieSide || 6 < dieSide)
    {
        return 0;
    }
    return m_statistics[dieSide-1];
}
