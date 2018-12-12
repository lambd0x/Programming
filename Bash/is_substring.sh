#!/bin/bash

# Author: lambd0x
# Date: 12/12/18
# Script name: is_substring.sh
# Version: 1.0
# Purpose:
# 1 - Verify if argument one is within argument two
#
# Use example: is_substring.sh aa bb
#              is_substring.sh aa bbaa
echo $2 | grep -q $1 && echo -e "$1 is a substring of $2\n" && exit
echo -e "$1 is not a substring of $2\n"
