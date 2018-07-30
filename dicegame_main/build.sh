#!/bin/bash
###########################################
# build.sh
#
# Description: The devicegame project build script
#
# Author: Ed Sutton
##########################################
projectName=dicegame

# Use of markdown required doxygen 1.8
doxygenVersionRequired="1.8"

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

# Build documentation if Doxygen installed
echo "Check if doxygen installed..."
doxygenVersionRequired="1.8"
if type -p doxygen; then
   versionDoxygen=$(doxygen --version)
   echo "doxygen ${versionDoxygen}"
   if [[ "$versionDoxygen" > ${doxygenVersionRequired} ]]; then
   (
      echo "Building doxygen content..."
      cd ../dicegame/doc
      doxygen DiceGame.doxyfile
   )
   else
       echo "Documentation uses markdown, requires Doxygen version: ${doxygenVersionRequired} or greater"
   fi
fi


echo
echo "Success! Build complete! ${projectName}"
exit 0

