#!/bin/bash

# Filename: ex2.sh
#
# Problem: Make a script to print out the first and third arguments to 
# the script. Then combine the two arguments in var and print var out.
VAR1="Argument1"
VAR3="Argument3"
echo The first argument is "$VAR1" 
echo The third argument is "$VAR3"
var="$VAR1$VAR3"
echo The combined first and third argument in var is "$var"

