/*
 * loaddicegameconfiguration.cpp
 *
 *  Created on: Dec 6, 2013
 *      Author: esutton
 */

#include "loaddicegameconfiguration.hpp"

// Removed boost dependencies to make easier to build on unknown machines
//#include <boost/filesystem.hpp> filesystem is a compiled boost lib
//#include <boost/algorithm/string.hpp>
//#include "boost/format.hpp"

#include <stdlib.h>     /* atoi */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace dicegame;


//NumRolls=100
//Dice=Die1
//LoadedSide=3
//LoadAmount=2
//Dice=Die2
//LoadedSide=6
//LoadAmount=10

/// \todo Consider changing configuration file format to XML
//XML Data:
//	<diceGame>
//		<numberRolls>100</numberRolls>
//		<diceList>
//			<die>
//				<loadedSide>3</loadedSide>
//				<loadedAmount>2</loadedAmount>
//			</die>
//			<die>
//				<loadedSide>6</loadedSide>
//				<loadedAmount>10</loadedAmount>
//			</die>
//		</diceList>
// 	</diceGame
//
//XML Schema:
//

/// \todo Add Unicode support
const char * const StatusMessagesEnglish[] =
{
    "Success",
    "Error",
    "File not found",
    "File open error",
    "File Parsing Error",
    "Expected a numeric string value",
    "Duplicate Dice sections with identical values"
};

const char * const * LocaleStrings = StatusMessagesEnglish;

// Configuration File Key Name Strings
const string KeyNumberOfRolls = "NumRolls";
const string KeyDice = "Dice";
const string KeyLoadedSide = "LoadedSide";
const string KeyLoadAmount = "LoadAmount";

/// \class dicegame::LoadDiceGameConfiguration
/// Loads a dice game configuration from a file

/// \var LoadDiceGameConfiguration::StructDie_t
/// A structure containing values used to create a loaded die

/// \var LoadDiceGameConfiguration::m_isValid
/// true when loaded config valid
///
/// \var LoadDiceGameConfiguration::m_numberOfRolls
/// number of rolls game config specifies
///
/// \var LoadDiceGameConfiguration::m_dieConfigurationCollection
/// vector of Die*

/// Constructor
LoadDiceGameConfiguration::LoadDiceGameConfiguration() :
        m_isValid(false),
        m_numberOfRolls(0),
        m_dieConfigurationCollection(2)
{
}
// Destructor
LoadDiceGameConfiguration::~LoadDiceGameConfiguration()
{
}

/// A static method to display status
/// \todo Add logging
StatusCode LoadDiceGameConfiguration::message(StatusCode statusCode, int lineNumber, string details)
{
    if(StatusSuccess == statusCode)
    {
        return StatusSuccess;
    }

    // If here we have an error
    cerr << "*** " << LocaleStrings[StatusError];
    if(StatusError < statusCode)
    {
        cerr << " : " << LocaleStrings[statusCode];
    }

    // Display line number if one provided
    if(0 < lineNumber)
    {
        cerr << ", Line " << lineNumber;
    }

    if( 0 < details.length())
    {
        cerr << ", " << details;
    }
    cerr << endl;
    return statusCode;
}

/// true when a valid configuration file is opened
bool LoadDiceGameConfiguration::isValid() const { return m_isValid; }

/// Number of rolls specified for this game configuration
int LoadDiceGameConfiguration::numberOfRolls() const { return m_numberOfRolls; }

/// A vector<StructDie_t> collection
const LoadDiceGameConfiguration::dieConfigurationCollection_t &LoadDiceGameConfiguration::dieConfigurationCollection() const { return m_dieConfigurationCollection; }


/// Internal method to parse the open configuration file
int LoadDiceGameConfiguration::parse(ifstream& inputFile)
{
    unsigned int dieNumber = 0;
    int dieCount = 0;
    string line;
    vector<std::string> keyValuePair;
    string details;
    int lineNumber = 0;
    while (getline(inputFile, line))
    {
        ++lineNumber;
        trim(line);
        if( 0 >= line.size())
        {
            //empty line
            continue;
        }
        // comments may start with '#', ';'
        std::size_t found = line.find_first_of("#;");
        if( 0 == found)
        {
            // comment line
            continue;
        }

        // If this a key=value line, it should split into exactly 2 strings
        split(keyValuePair, line, "=" );
        if(2 != keyValuePair.size())
        {
            // parsing error - too many delimiters
            return LoadDiceGameConfiguration::message( StatusFileConfigParseError, lineNumber, line);
        }

        string key = keyValuePair[0];
        string value = keyValuePair[1];
        if( 0 == key.compare(KeyNumberOfRolls))
        {
            if(false == LoadDiceGameConfiguration::isNumeric(value))
            {
                return LoadDiceGameConfiguration::message( StatusFileConfigExpectedNumericString, lineNumber, line);
            }
            this->m_numberOfRolls = atoi(value.c_str());
        }
        else if( 0 == key.compare(KeyDice))
        {
            if(0 != value.compare("Die1") && 0 != value.compare("Die2"))
            {
                details = "Expected \"Die1\" or \"Die2\"";
                return message( StatusFileConfigParseError, lineNumber, details);
            }

            char dieNumberChar = value.at(value.length()-1);
            dieNumber = dieNumberChar - '0';
            ++dieCount;

            StructDie_t structDie(dieNumber);
            if(structDie.dieNumber == m_dieConfigurationCollection[dieNumber-1].dieNumber)
            {
                return message( StatusDuplicateDiceSections, lineNumber, line);
            }
            m_dieConfigurationCollection[dieNumber-1] = structDie;
        }
        else if( 0 == key.compare(KeyLoadedSide))
        {
            if(false == LoadDiceGameConfiguration::isNumeric(value))
            {
                return message( StatusFileConfigExpectedNumericString, lineNumber, line);
            }
            if(0 == dieNumber)
            {
                // parsing error missing Dice section header
                return message( StatusFileConfigParseError, lineNumber, line);
            }
            // Zero is allowed to indicated no loaded side
            int loadedSide = atoi(value.c_str());
            if(-1 >= loadedSide || 6 < loadedSide)
            {
                // parsing error invalid loaded side value
                return message( StatusFileConfigParseError, lineNumber, line);
            }
            m_dieConfigurationCollection[dieNumber-1].loadedSide = loadedSide;
        }
        else if( 0 == key.compare(KeyLoadAmount))
        {
            if(false == LoadDiceGameConfiguration::isNumeric(value))
            {
                return message( StatusFileConfigExpectedNumericString, lineNumber, line);
            }
            if(0 == dieNumber)
            {
                // parsing error missing Dice section heaader
                return message( StatusFileConfigParseError, lineNumber, line);
            }
            // Zero is allowed to indicated no loading
            int loadAmount = atoi(value.c_str());
            if(0 > loadAmount)
            {
                // parsing error invalid loaded side value
                return message( StatusFileConfigParseError, lineNumber, line);
            }
            m_dieConfigurationCollection[dieNumber-1].loadAmount = loadAmount;
        }
    }

    if(0 == dieNumber)
    {
        details = "No 'Dice' sections specified in config file";
        message( StatusFileConfigParseError, 0, details);
        return 1;
    }

    if(2 > dieCount)
    {
        string details = "Expected two 'Dice' sections specified in config file";
        message( StatusFileConfigParseError, 0, details);
        return 1;
    }

    if(0 >= m_numberOfRolls)
    {
        string details = KeyNumberOfRolls + " is missing or 0";
        message( StatusFileConfigParseError, 0, details);
        return 1;
    }

    m_isValid = true;
    return 0;
}

/// Opens the game configuration file and returns 0 if valid.
///
/// \remarks prefer use of Qt's QSettings for this
/// or regex for parsing but need to avoid dependencies for this example.
/// \returns 0 if game configuration is successfully loaded
int LoadDiceGameConfiguration::open(std::string& pathToConfigurationFile)
{
    m_isValid = false;

    if ( false == LoadDiceGameConfiguration::fileExists( pathToConfigurationFile ) )
    {
        return message(StatusFileNotFound, 0, pathToConfigurationFile);
    }

    ifstream inputFile(pathToConfigurationFile.c_str(), std::ifstream::in);
    if (0 == inputFile)
    {
        return message(StatusFileOpenError, 0, pathToConfigurationFile);
    }

    int result = parse(inputFile);
    inputFile.close();

    m_isValid = true;
    return result;
}


/// A static method to check if file exists
/// \remarks Prefer to use boost::filesystem or Qt QFile or QFileInfo for this
/// but did not want added dependencies for this code project
bool LoadDiceGameConfiguration::fileExists(string& fileName)
{
    FILE *file = fopen(fileName.c_str(), "r");
    if (0 != file )
    {
        fclose(file);
        return true;
    }
    return false;
}

/**
 * Static method to trim leading and trailing whitespace.
 * Replacement for boost::trim to remove boost dependencies from project
 * @param str
 */
void LoadDiceGameConfiguration::trim(string &str)
{
    // Trim right
    std::string whitespaces (" \t\f\v\n\r");
    std::size_t endPosition = str.find_last_not_of(whitespaces);
    if (std::string::npos == endPosition)
    {
        // String is all whitespace
        str.clear();
        return;
    }
    str.erase(endPosition+1);

    // Trim left
    size_t startPosition = str.find_first_not_of(whitespaces);
    if( string::npos == startPosition )
    {
        // No leading whitespace - nothing to trim
        return;
    }
    str = str.substr( startPosition );
}

/**
 * Static method to replace boost::split to remove boost dependencies from project
 * @param tokens
 * @param str
 * @param delimiters
 */
void LoadDiceGameConfiguration::split(vector<string>& tokens, const string& str, const string& delimiters)
{
    tokens.clear();
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

/// A static method to check if std::string is numeric
bool LoadDiceGameConfiguration::isNumeric(const std::string& numericString)
{
    if(numericString.empty())
    {
        return false;
    }

    std::string::const_iterator it = numericString.begin();
    while (it != numericString.end() && std::isdigit(*it))
    {
        ++it;
    }
    return it == numericString.end();
}



