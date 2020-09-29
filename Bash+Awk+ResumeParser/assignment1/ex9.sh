#!/bin/bash

# Filename: ex9.sh
#
# Problem: Add two input numbers together.

echo -n Input a number:
read val1
echo -n Input a second number:
read val2
total=`expr $val1 + $val2`
echo Result is $total.
