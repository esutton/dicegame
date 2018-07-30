#include <iostream>


#include "loadeddicegame.hpp"
#include "loadeddie.hpp"
#include "loaddicegameconfiguration.hpp"

using namespace std;
using namespace dicegame;

/// \class dicegame::LoadedDiceGame
/// \brief Plays a loaded dice game specified in a configuration file.
///
/// The DiceGame:
/// - A collection of one or more die
/// - Plays the gane by rolling all die in the game


LoadedDiceGame::LoadedDiceGame()
{
}

/// Plays a loaded dice game using specified configuration file
///
/// \returns 0 if game configuration is successfully loaded and game played
int LoadedDiceGame::play(string& pathToConfigurationFile)
{
    if(false == LoadDiceGameConfiguration::fileExists(pathToConfigurationFile))
    {
        cerr << "*** Error file not found: " << pathToConfigurationFile << endl;
        return 1;
    }

    LoadDiceGameConfiguration diceGameConfiguration;
    diceGameConfiguration.open(pathToConfigurationFile);
    if(false == diceGameConfiguration.isValid())
    {
        cerr << "*** Error game configuration is not valid\n";
        cerr << "File: " << pathToConfigurationFile << endl;
        return 1;
    }

    // Create the game from loaded configuration
    DiceGame diceGame;
    for(unsigned int die = 0; die < diceGameConfiguration.dieConfigurationCollection().size(); ++die)
    {
        int loadedSide = diceGameConfiguration.dieConfigurationCollection()[die].loadedSide;
        int loadAmount = diceGameConfiguration.dieConfigurationCollection()[die].loadAmount;
        diceGame.addDie(new LoadedDie(loadedSide, loadAmount));
    }

    // Play the game displaying status after each throw
    printf("\n");
    for(int roll = 0; roll < diceGameConfiguration.numberOfRolls(); ++roll )
    {
        diceGame.play();
        printf("Throw %3i: ",roll+1);
        for( unsigned int die = 0; die < diceGame.dieCollection().size(); ++die)
        {
            // add separator
            if( 0 < die)
            {
                printf(", ");
            }
            printf("Die%d rolled a %d", die+1, diceGame.dieCollection()[die]->faceValue());
        }
        printf("\n");
    }

    // After game over display the roll distribution statistics for each die
    const DiceGame::dieCollection_t dieCollection = diceGame.dieCollection();
    for(unsigned int dieIndex = 0; dieIndex < dieCollection.size(); ++dieIndex)
    {
        printf("\nDie%i Statistics for %i rolls:\n", dieIndex+1, diceGameConfiguration.numberOfRolls());
        for(int dieSide = 1; dieSide <= 6; ++dieSide)
        {
            printf("Side %i: %4.1f%%\n",
                   dieSide, (100.0f * dieCollection[dieIndex]->rollCountHistory(dieSide))/(float)diceGameConfiguration.numberOfRolls());
        }
    }
    printf("\n");

    // Success!
    return 0;
}
