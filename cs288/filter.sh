#!/bin/bash
# <-- Dnd -->

# Accept directory as arg. Loop to accept mult args
    for arg in "$@"; do
      ls -s > temp.txt   
    done

# Get the correct number of files. works
  x=$(cat temp.txt | wc -l)
  x=$((`cat temp.txt | wc -l` -2))

  total=$(grep 'total' temp.txt | cut -d\   -f2)

  avg=$((total/x))

# following filters   
  sed -i -e "/total/d" temp.txt
  while read -r mem line; do
    if [[ $mem -gt $avg ]]; then
       echo $line
    fi
done < temp.txt
rm temp.txt
