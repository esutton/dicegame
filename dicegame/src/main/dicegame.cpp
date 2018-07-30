/*
 * \file dicegame.cpp
 *
 *      Author: esutton
 */
#include "die.hpp"

#include "dicegame.hpp"
#include "loadeddie.hpp"
#include "loaddicegameconfiguration.hpp"


using namespace dicegame;

/// \class dicegame::DiceGame
/// \brief A collection on one or more die that may be rolled
///
/// The DiceGame:
/// - A collection of one or more die
/// - Plays the gane by rolling all die in the game

/// Default constructor
DiceGame::DiceGame()
{
}

/**
 * Destructor
 *
 * \remarks CppUTest can detect memory leaks.
 * While not a substitute for Valgrind and commercial tools it is useful.
 *
 * For example, commenting-out the destructor code will result in CppUTest
 * displaying "Memory leak(s) found" when DiceGame_test.cpp is run:
 \code
   ../DiceGame_test.cpp:36: error: Failure in TEST(DiceGame, LoseWhenRollLessThan7)
   Memory leak(s) found.
   Alloc num (253) Leak size: 72 Allocated at: ../DiceGame_test.cpp and line: 23. Type: "new"
   Memory: <0x103001200> Content: "0??"
   Alloc num (251) Leak size: 72 Allocated at: ../DiceGame_test.cpp and line: 22. Type: "new"
   Memory: <0x103001170> Content: "0??"
   Total number of leaks:  2
   DiceGame::~DiceGame()
 \endcode
 */
DiceGame::~DiceGame()
{
    // I could have used boost::shared_ptr<Die> but I like this better anyway
    // to demonstrate CppUTest memory leak detect
    for( DiceGame::dieIterator_t iter = m_dieCollection.begin(); iter != m_dieCollection.end(); ++iter)
    {
        delete (*iter);
    }
}

/// Rolls all dice belonging to this game
void DiceGame::play()
{
    for( DiceGame::dieIterator_t iter = m_dieCollection.begin(); iter != m_dieCollection.end(); ++iter)
    {
        (*iter)->roll();
    }
}

/// Adds a new die to the game's dieCollection
///
/// \remarks DiceGame is responsible for deleting the Die
void DiceGame::addDie(Die* die)
{
    m_dieCollection.push_back(die);
}

/// returns a read-only collection of game dice
const DiceGame::dieCollection_t &DiceGame::dieCollection() const { return m_dieCollection; }



