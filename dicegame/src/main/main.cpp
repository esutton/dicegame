/*!
 * \file main.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: esutton
 */

#include "loadeddicegame.hpp"
#include "main.hpp"
#include "version.h"

#include <iostream>


using namespace std;

namespace dicegame
{

    /// Display command line usage
    void displayUsage(const char * executableName)
    {
	cout << endl;
	cout << "Version: " << VERSION_NUMBER << ", ";
	cout << "Date: " << DATE_OF_SOFTWARE_BUILD << endl;
	cout << "Usage:" << endl;
        cout << executableName << " dicegame.config\n";
    }

    /// A static method to check if file exists
    /// \remarks Prefer to use boost::filesystem or Qt QFile or QFileInfo for this
    /// but did not want added dependencies for this code project
    bool fileExists(string& fileName)
    {
        FILE *file = fopen(fileName.c_str(), "r");
        if (0 != file )
        {
            fclose(file);
            return true;
        }
        return false;
    }

    /// The dicegame program main() implementation
    ///
    /// Load game configuration and play game
    int main(int argc, char** argv)
    {
	if( 1 >= argc)
	{
            cerr << "*** Error configuration file argument not found\n";
            displayUsage(argv[0]);
            return 1;
	}
	if( 2 < argc)
	{
            cerr << "*** Error unexpected arguments\n";
            displayUsage(argv[0]);
            return 1;
	}

	string fileName(argv[1]);
        if(false == fileExists(fileName))
	{
            cerr << "*** Error file not found: " << fileName << endl;
            displayUsage(argv[0]);
            return 1;
	}

        // Play the loaded dice game using configuration file
        LoadedDiceGame diceGame;
        return diceGame.play(fileName);
    }

} /* namespace dicegame */

// Include main when not building CppUTests tests to avoid duplicate main symbols
#ifndef BUILDING_CPPUTESTS

/// The dicegame program main()
int main(int argc, char** argv)
{
    return dicegame::main(argc, argv);
}

#endif
