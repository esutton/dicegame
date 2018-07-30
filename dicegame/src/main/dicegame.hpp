/*!
 * \file dicegame.hpp
 *
 *      Author: esutton
 */

#ifndef DICEGAME_HPP_
#define DICEGAME_HPP_
#pragma once



#include <string>
#include <vector>
#include <memory>

// remove boost dependencies to make easier to build on unknown environment
// boost::shared_ptr not needed if using tr1 or C++11
//#include <boost/shared_ptr.hpp>

namespace dicegame
{

    // Forward declarations
    class Die;


    class DiceGame
    {
    public:
	typedef std::vector<Die*> dieCollection_t;
	typedef dieCollection_t::iterator dieIterator_t;

	DiceGame();
	virtual ~DiceGame();
	void addDie(Die* die);
	const dieCollection_t &dieCollection() const;
	void play();

    protected:
	dieCollection_t m_dieCollection;
    };

} /* namespace dicegame */

#endif /* DICEGAME_HPP_ */
