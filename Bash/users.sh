#!/bin/bash

# Author: lambd0x
# Date: 12/12/18
# Script name: users.sh
# Version: 1.0
# Purpose:
# 1 - Display from /etc/passwd the users and their full names
#
# Use example: users.sh
cat /etc/passwd | cut -d $':' -f 1,5
