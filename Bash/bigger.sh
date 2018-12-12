#!/bin/bash

# Author: lambd0x
# Date: 12/12/18
# Script name: bigger.sh
# Version: 1.0
# Purpose:
# 1 - Compare two numbers and inform which of the two is: bigger, smaller
# 2 - Or they are equal
#
# Use example: bigger 2 5
#              bigger 5 2

# Tests if $2 > $1
if test $1 -lt $2
then
	echo -e "$1 is smaller than $2\n"
	# Tests if $1 > $2
elif test $1 -gt $2
then
	echo -e "$1 is greater than $2\n"
	# Both are equal
else
	echo "$1 and $2 are equal"
fi
