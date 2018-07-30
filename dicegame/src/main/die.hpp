/*!
 * \file die.hpp
 * \author: Ed Sutton
 */

#ifndef DIE_HPP_
#define DIE_HPP_
#pragma once

namespace dicegame
{

    class Die
    {
    public:
	Die(int numberOfSides = 6);
	virtual ~Die();

	virtual int roll();
	int faceValue() const;
	int numberOfSides() const;

	unsigned int rollCountHistory(int dieSide);

    protected:
	int m_rollValue;
	int m_numberOfSides;
	unsigned int m_statistics[6];

	int randomGenerator();
    };


} /* namespace dicegame */

#endif /* DIE_HPP_ */
