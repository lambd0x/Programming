#!/bin/bash

# Author: lambd0x
# Date: 12/12/18
# Script name: reset_n.sh
# Version: 1.0
# Purpose:
# 1 - Take a number as input and decrement it in th same line til 0
#
# Use example: reset_n.sh 5
#              reset_n.sh 2

# Uses seq -s to change default spacing between numbers (\n) to (' ')
# seq $1 is the start of the sequence
# seq $2 is the increment
# seq $3 is the stop condition
seq -s ' ' $1 -1 0 && echo
