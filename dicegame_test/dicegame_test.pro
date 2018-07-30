# QtCreator Project File
# Dicegame demostration of TDD using CppUTest and code coverage using gcov
# Ed Sutton
QT -= core
QT -= gui
TARGET = dicegame_test
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

# Keep clutter out of the project directory
OBJECTS_DIR = obj
MOC_DIR = obj
UI_DIR = obj
CONFIG(debug, debug|release):DEFINES += DEBUG
CONFIG(release, debug|release):DEFINES += RELEASE

# Include main when not building CppUTests tests to avoid duplicate main symbols
DEFINES += BUILDING_CPPUTESTS
INCLUDEPATH += $$PWD/../dicegame/src/main

# Code coverage with GNU gcovf
# https://wiki.jenkins-ci.org/pages/viewpage.action?pageId=45482230
# -g -pg -fprofile-arcs -ftest-coverag
GCOV_CFLAGS = "-g -pg -fprofile-arcs -ftest-coverage"
GCOV_LINK_FLAGS = "-lgcov"

# Useful GCC flags for C
# * -Werror: essential. Without "-Werror" warnings are useless; they do not *demand* to be fixed.
# * -Wextra, -Wall: essential.
# * -Wfloat-equal: useful because usually testing floating-point numbers for equality is bad.
# * -Wundef: warn if an uninitialized identifier is evaluated in an #if directive.
# * -Wshadow: warn whenever a local variable shadows another local variable, parameter or global variable or whenever a built-in function is shadowed.
# * -Wpointer-arith: warn if anything depends upon the size of a function or of void.
# * -Wcast-align: warn whenever a pointer is cast such that the required alignment of the target is increased. For example, warn if a char * is cast to an int * on machines where integers can only be accessed at two- or four-byte boundaries.
# * -Wstrict-prototypes: warn if a function is declared or defined without specifying the argument types.
# * -Wstrict-overflow=5: warns about cases where the compiler optimizes based on the assumption that signed overflow does not occur. (The value 5 may be too strict, see the manual page.)
# * -Wwrite-strings: give string constants the type const char[length] so that copying the address of one into a non-const char * pointer will get a warning.
# * -Waggregate-return: warn if any functions that return structures or unions are defined or called.
# * -Wcast-qual: warn whenever a pointer is cast to remove a type qualifier from the target type*.
# * -Wswitch-default: warn whenever a switch statement does not have a default case*.
# * -Wswitch-enum: warn whenever a switch statement has an index of enumerated type and lacks a case for one or more of the named codes of that enumeration*.
# * -Wconversion: warn for implicit conversions that may alter a value*.
# * -Wunreachable-code: warn if the compiler detects that code will never be executed*.
# * -Wformat=2: Extra format checks on printf/scanf functions.
# Lines with appended '*' sometimes give too many spurious warnings, so I use them on as-needed basis.
# #############################################################################
# This is a set of extra-paranoid flags I'm using for C++ code:
# -g -O -Wall -Weffc++ -pedantic  \
# -pedantic-errors -Wextra  -Wall -Waggregate-return -Wcast-align \
# -Wcast-qual  -Wchar-subscripts  -Wcomment -Wconversion \
# -Wdisabled-optimization \
# -Werror -Wfloat-equal  -Wformat  -Wformat=2 \
# -Wformat-nonliteral -Wformat-security  \
# -Wformat-y2k \
# -Wimplicit  -Wimport  -Winit-self  -Winline \
# -Winvalid-pch   \
# -Wunsafe-loop-optimizations  -Wlong-long -Wmissing-braces \
# -Wmissing-field-initializers -Wmissing-format-attribute   \
# -Wmissing-include-dirs -Wmissing-noreturn \
# -Wpacked  -Wpadded -Wparentheses  -Wpointer-arith \
# -Wredundant-decls -Wreturn-type \
# -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector \
# -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default \
# -Wswitch-enum -Wtrigraphs  -Wuninitialized \
# -Wunknown-pragmas  -Wunreachable-code -Wunused \
# -Wunused-function  -Wunused-label  -Wunused-parameter \
# -Wunused-value  -Wunused-variable  -Wvariadic-macros \
# -Wvolatile-register-var  -Wwrite-strings
# Make all warnings into errors - without "-Werror" warnings are useless - they do not demand to be fixed.
QMAKE_CFLAGS += "-Werror"
QMAKE_CFLAGS += "-Wall"
QMAKE_CFLAGS += "-Wextra"
QMAKE_CFLAGS += "-Wformat=2"

# Generate debug symbols then strip to separate file after build
# Symbols can be packaged in a separate rpm package that can be installed only when needed
# Unlike MSVC, the GCC -g seitch to generate debug symbols does not disable optimizations
# however you may want to disable optimizations to make debug stepping easier to follow.
# See:
# https://access.redhat.com/knowledge/docs/en-US/Red_Hat_Enterprise_Linux/4/html/Debugging_with_gdb/separate-debug-files.html
# http://stackoverflow.com/questions/866721/how-to-generate-gcc-debug-symbol-outside-the-build-target
QMAKE_CFLAGS += "-g"

# QMAKE_CFLAGS += "-Wundef"
# QMAKE_CFLAGS += "-Wshadow"
QMAKE_CFLAGS += "-Wpointer-arith"
QMAKE_CFLAGS += "-Wcast-align"

# QMAKE_CFLAGS += "-Wwrite-strings"
# QMAKE_CFLAGS += "-Waggregate-return"
QMAKE_CFLAGS += "-Wcast-qual"

# QMAKE_CFLAGS += "-Wswitch-default"
# QMAKE_CFLAGS += "-Wswitch-enum"
QMAKE_CFLAGS += "-Wconversion"
QMAKE_CFLAGS += "-fno-common"
QMAKE_CXXFLAGS += $${GCOV_CFLAGS}

# Experiment using Gnu profiler.  gprof is incompatible with -fomit-frame-pointer
# QMAKE_CFLAGS += "-pg"
# QMAKE_LFLAGS += "-pg"
# Use the above C warnings for C++ as well
QMAKE_CXXFLAGS += $$QMAKE_CFLAGS

# These additional options are valid for C only or came later than g++ version 4.1.2
QMAKE_CFLAGS += "-Wmissing-prototypes"
QMAKE_CFLAGS += "-Wstrict-prototypes"

# QMAKE_CFLAGS += "-Wstrict-overflow=5"
# These options are valid for C/C++, came later than g++ version 4.1.2, or cause too much "noise" in C++
QMAKE_CFLAGS += "-Wunreachable-code"

# Additional C++ warnings
# QMAKE_CXXFLAGS += "-Weffc++"
QMAKE_CXXFLAGS += "-Wunused-variable"
QMAKE_CXXFLAGS += "-Wunused-value"
QMAKE_CXXFLAGS += "-Wmissing-braces"
QMAKE_CXXFLAGS += "-Wmissing-field-initializers"
QMAKE_CXXFLAGS += "-Wmissing-format-attribute"
QMAKE_CXXFLAGS += "-Wmissing-include-dirs"

# MAKE_CXXFLAGS += "-Wmissing-noreturn"
QMAKE_CXXFLAGS += "-Wparentheses"

# QMAKE_CXXFLAGS += "-Wredundant-decls"    <- gcc 4.1.2 Does not like multiple new() overloads in CppUTest MemorylLeakDetectorMacros.h
QMAKE_CXXFLAGS += "-Wreturn-type"
QMAKE_CXXFLAGS += "-Wsign-compare"
QMAKE_CXXFLAGS += "-Wstack-protector"

# QMAKE_CXXFLAGS += "-Wuninitialized"
QMAKE_CXXFLAGS += "-Wunused-function"
QMAKE_CXXFLAGS += "-Wunused-label"
QMAKE_CXXFLAGS += "-Wunused-parameter"
QMAKE_CXXFLAGS += "-Wvolatile-register-var"

# Silence: warning class has virtual functions but non-virtual destructor
QMAKE_CXXFLAGS_WARN_ON = -Wno-non-virtual-dtor

# ToDo: How to programmatically run ../common/scripts/updatelibversioninfo.py ../ if version-svn.h does not exists?
# Or make Qmake gerenate a makefile that always runs updatelibversioninfo.py and just put up with the network delays accessing the svn repo?
# Or change buildhelper.py getSvnRevision
# GCOV
LIBS += $${GCOV_LINK_FLAGS}

# CppUTest
INCLUDEPATH += $$PWD/../cpputest/include
LIBS += -L$$PWD/../cpputest/lib
LIBS += -lCppUTest
HEADERS += ../dicegame/src/main/version.h \
    ../dicegame/src/main/main.hpp \
    ../dicegame/src/main/loadeddie.hpp \
    ../dicegame/src/main/loaddicegameconfiguration.hpp \
    ../dicegame/src/main/die.hpp \
    ../dicegame/src/main/dicegame.hpp \
    ../dicegame/src/main/loadeddicegame.hpp
SOURCES += ../dicegame/src/main/main.cpp \
    ../dicegame/src/main/loadeddie.cpp \
    ../dicegame/src/main/loaddicegameconfiguration.cpp \
    ../dicegame/src/main/die.cpp \
    ../dicegame/src/main/dicegame.cpp \
    ../dicegame/src/test/RunAllTests.cpp \
    ../dicegame/src/test/main_test.cpp \
    ../dicegame/src/test/loadeddie_test.cpp \
    ../dicegame/src/test/loaddicegameconfiguration_test.cpp \
    ../dicegame/src/test/die_test.cpp \
    ../dicegame/src/test/dicegame_test.cpp \
    ../dicegame/src/main/loadeddicegame.cpp \
    ../dicegame/src/test/loadeddicegame_test.cpp
OTHER_FILES += build.sh \
    run-tests.sh \
    invalid-die3.config \
    dicegame.config \
    invalid-rolls_0.config \
    invalid-3dice.config \
    invalid-1dice.config \
    invalid-0dice.config \
    invalid-numrolls-not-numeric.config \
    invalid-duplicate-die.config \
    invalid-loadedside-not-numeric.config \
    invalid-loadamount-not-numeric.config \
    invalid-too-many-equal-signs.config \
    invalid-missing-die1-section.config \
    invalid-loadedside-gt-6.config \
    invalid-loadedside-negative.config \
    invalid-loadedside-gt-6.config \
    invalid-missing-die2-section.config \
    invalid-loadamount-negative.config \
    invalid-missing-key-value.config
