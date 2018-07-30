#!/bin/bash
###########################################
# build.sh
#
# Description: The project root build script that calls
# all subdirectory build scripts.
#
# Author: Ed Sutton
##########################################

#Set the Qt Version this project is frozen at
# For QT4.6.1 add: export QTDIR=/opt/qtsdk-2010.01/qt/bin
#export QTDIR=/opt/qtsdk-2010.01/qt/bin

# Build dicegame
(
    cd dicegame_main
    ./build.sh
)
if [ $? -gt 0 ]; then
    echo "** ERROR - Build failed - dicegame_main"
    exit 1
fi


# Build dicegame_test
(
   cd dicegame_test
   ./build.sh
)
if [ $? -gt 0 ]; then
    echo "** ERROR - Build failed - dicegame_test"
    exit 1
fi

printf "Success Build complete!\n\n"

echo
echo "Run tests and publish coverage reports on successful build.."
(
   cd dicegame_test
   ./run-tests.sh
)

echo
echo "Build Complete"
echo
exit 0
