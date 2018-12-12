#!/bin/bash

# Author: lambd0x
# Date: 12/12/18
# Script name: join_args.sh
# Version: 1.0
# Purpose:
# 1 - Join all args into a single string and display it
#
# Use example: join_args.sh aa bb
#              join_args.sh aa bbaa
echo $* | sed "s/ //g"
