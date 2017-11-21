#!/bin/bash

 for arg in "$@"; do
   wget -q -O all "$@"
   rm *.1 2> /dev/null 
 done
awk -F"," '!_[$1]++' all > tmp.txt
awk -F "," '(NR>1) && ($2 > 100000 ) ' tmp.txt > bar
cut -d "," -f1,3 bar
