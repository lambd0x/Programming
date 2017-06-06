#!/usr/bin/sh
#Single replace the 1st line of the .pl6 files to "use Perl6;"
var="use Perl6;"
sed -i "1s/.*/$var/" *.pl6
