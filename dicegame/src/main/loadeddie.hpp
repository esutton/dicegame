/*!
 * \file loadeddie.hpp
 *
 *  Created on: December 7, 2013
 *      Author: esutton
 */

#include "die.hpp"

#ifndef LOADEDDIE_HPP_
#define LOADEDDIE_HPP_
#pragma once

namespace dicegame
{

    class LoadedDie : public Die
    {
    public:
	LoadedDie(unsigned int loadedSide, unsigned int loadedSideProbabilityMultiplier);

	virtual ~LoadedDie();
	virtual int roll();

    private:
	void loadDie(unsigned int loadedSide, unsigned int loadedSideProbabilityMultiplier);

	int m_loadedSideThresholds[6];
	int m_loadedSide;
	unsigned int m_loadedSideProbabilityMultiplier;
    };

} /* namespace dicegame */

#endif /* LOADEDDIE_HPP_ */
