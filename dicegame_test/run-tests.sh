#!/bin/bash
###########################################
# run-tests.sh
#
# Description: Run tests and publish coverage reports
#
# Author: Ed Sutton
##########################################

coverageDir=../dicegame/doc/html/test/coverage


# Use lcov to build HTML gcov reports to merge with docygen HTML docs
# http://ltp.sourceforge.net/coverage/lcov.php
if type -P lcov ; then
   # Removes the old gcov data files (.gcda)
   lcov --directory ./obj --zerocounters
fi

# Run tests to generate new gcda files
echo "Run tests and publish coverage reports..."
./dicegame_test -ojunit 2>/dev/null
echo "Output jUnit xml reports to ${PWD}"

# Use lcov to build HTML gcov reports to merge with docygen HTML docs
# http://ltp.sourceforge.net/coverage/lcov.php
if type -P lcov ; then
   echo "Clean coverage reports..."
   rm -rf ${coverageDir}/*

   echo "Generate HTML from gcov"
   lcov --capture --directory ./obj --output-file ${coverageDir}/coverage.info
   genhtml ${coverageDir}/coverage.info --output-directory ${coverageDir}
else
    echo "*** Warning - lcov not found"
fi


echo
echo "Tests Complete"
echo
exit 0
