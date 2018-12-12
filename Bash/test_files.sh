#!/bin/bash

# Author: lambd0x
# Date: 10/12/18
# Script name: test_files.sh
# Version: 1.0
# Purpose:
# 1 - Inform whether the informed data corresponds to either a file or a dir

# Collects information from STDIN
echo -n "Inform data, please: "
read data

# Checks whether the data is a file
test -f $data && echo "Data is a file" && exit

# Checks whether the data is a dir
test -d $date && echo "Data is a dir"
