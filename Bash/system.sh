#!/bin/bash

# Author: lambd0x
# Date: 10/12/18
# Script name: system.sh
# Version: 1.0
# Purpose:
# 1 - Display all logged users
# 2 - Display disk usage
# 3 - Display complete current date

# All logged users
echo "Logged users now on this host:"
w
echo

# Disk usage
echo "Current disk usage:"
df -h
echo

# Complete current date
echo "Present date:"
date +"%c"
echo
