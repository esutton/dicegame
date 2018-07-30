/*!
 * \file loadeddicegame.hpp
 *
 *      Author: esutton
 */

#ifndef LOADEDDICEGAME_H
#define LOADEDDICEGAME_H

#include <string>

#include "dicegame.hpp"

namespace dicegame
{

    class LoadedDiceGame : public DiceGame
    {
    public:
        LoadedDiceGame();

        int play(std::string& pathToConfigurationFile);

    };

} /* namespace dicegame */

#endif // LOADEDDICEGAME_H
