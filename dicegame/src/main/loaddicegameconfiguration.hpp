/*!
 * \file loaddicegameconfiguration.hpp
 *
 *  Created on: Dec 6, 2013
 *      Author: esutton
 */

#ifndef LOADDICEGAMECONFIGURATION_HPP_
#define LOADDICEGAMECONFIGURATION_HPP_

#include <fstream>
#include <string>
#include <vector>

namespace dicegame
{

    enum StatusCode
    {
	StatusSuccess = 0,
	StatusError,
	StatusFileNotFound,
	StatusFileOpenError,
	StatusFileConfigParseError,
	StatusFileConfigExpectedNumericString,
	StatusDuplicateDiceSections
    };

    class LoadDiceGameConfiguration
    {
    public:

	typedef struct StructDie_t
	{
            StructDie_t(int dieNumber=0) :
                    dieNumber(dieNumber),
                    loadedSide(0),
                    loadAmount(0)
            {
            }
            int dieNumber;
            int loadedSide;
            int loadAmount;
	} StructDie_t;

	typedef std::vector<StructDie_t> dieConfigurationCollection_t;
	typedef dieConfigurationCollection_t::iterator dieConfigurationIterator_t;

    public:
	LoadDiceGameConfiguration();
	virtual ~LoadDiceGameConfiguration();

	int open(std::string& pathToConfigurationFile);
	bool isValid() const;
	int numberOfRolls() const;
	const dieConfigurationCollection_t &dieConfigurationCollection() const;

	static bool fileExists(std::string& fileName);

    protected:
	int parse(std::ifstream& inputFile);

	static StatusCode message(StatusCode statusCode, int lineNumber=0, std::string details = "");
	static bool isNumeric(const std::string& str);
	static void trim(std::string &str);
	static void split(std::vector<std::string>& tokens, const std::string& str, const std::string& delimiters = " ");

	bool m_isValid;
	int m_numberOfRolls;
	dieConfigurationCollection_t m_dieConfigurationCollection;
    };

} /* namespace dicegame */

#endif /* LOADDICEGAMECONFIGURATION_HPP_ */
