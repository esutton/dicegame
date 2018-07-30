/*
 * DieTest.cpp
 *
 *      Author: esutton
 */
#include "main.hpp"

#include <CppUTest/TestHarness.h>

/**
\file main_test.cpp
\brief Test dicegame::main
\author Ed Sutton
 */

using namespace dicegame;

/// Test the dice game main()
TEST_GROUP(Main)
{
};

/// \test Assert error(1) is returned when arguments are too few
TEST(Main, ArgumentsTooFew)
{
    char * argv[] = { (const char*)"dicegame" };
    int argc = sizeof(argv)/(sizeof(char*));
    int result = main(argc, argv);
    CHECK(1 ==  result);
}
/// \test Assert error(1) is returned when arguments are too many
TEST(Main, ArgumentsTooMany)
{
    char *argv[] = { (const char*)"dicegame", (const char*)"one", (const char*)"two" };
    int argc = sizeof(argv)/(sizeof(char*));
    int result = main(argc, argv);
    CHECK(1 == result);
}
/// \test Assert error(1) is returned when configuration file is not found
TEST(Main, ArgumentsConfigFileNotFound)
{
    char *argv[] = { (const char*)"dicegame", (const char*)"this-file-does-not-exist.config" };
    int argc = sizeof(argv)/(sizeof(char*));
    int result = main(argc, argv);
    CHECK(1 == result);
}
/// \test Assert success(0) is returned when arguments are valid
TEST(Main, ArgumentsCorrect)
{
    char *argv[] = { (const char*)"dicegame", (const char*)"dicegame.config" };
    int argc = sizeof(argv)/(sizeof(char*));
    int result = main(argc, argv);
    printf("Dbg main result=%d\n", result);
    CHECK(0 == result);
}



