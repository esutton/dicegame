#!/bin/bash
###########################################
# build.sh
#
# Description: The device_test project build script
#
# Author: Ed Sutton
##########################################
projectName=device_test


# Is environment var QTDIR defined?
if [ ! -n "${QTDIR}" ]; then
   echo "*** Error - Build depends on Qt SDK: \$QTDIR variable not defined."
   exit 1
fi

# Does QTDIR directory exist?
if [ ! -d "$QTDIR" ]; then
   echo "*** Error - Qt SDK not installed: $QTDIR"
   echo "Go to http://qt-project.org"
   exit 1
fi

echo "Building with Qt version: \$QTDIR = $QTDIR\n\n"
echo "Generate Makefile..."
$QTDIR/qmake *.pro -r

# Does Makefile exist?
if [ ! -f "Makefile" ]; then
   echo "*** Error - Makefile not found"
   exit 1
fi

make clean
make
if [ $? -gt 0 ]; then
    echo "*** ERROR - make ${projectName} failed"
    exit 1
fi

# Run tests, generate coverage reports
./run-tests.sh

echo "Success! Build complete! ${projectName}"
echo
exit 0

