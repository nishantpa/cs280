#!/bin/bash

#Builds the array you're going to work with
ary=()
  for arg in "$@"; do
    ary+=( "$arg" )
  done
 # echo "${ary[*]}"

quicksort() {
  local  pivot i smaller=() larger=()
   quickret=()
  (($#==0)) && return 0
  pivot=$1
  shift

    for i; do
      if [[ $i < $pivot ]]; then
        smaller+=( "$i" )
    else
        larger+=( "$i" )
      fi
    done
  
  quicksort "${smaller[@]}"
  smaller=( "${quickret[@]} ")
  quicksort "${larger[@]}"
  larger=( "${quickret[@]}" )
  quickret=( "${smaller[@]}" "$pivot" "${larger[@]}" ) 
  echo "${quickret[*]}" 
}

#Runs and redirects to file. Then filters out extra whitespaces
#  and displays sorted array
quicksort "${ary[@]}" > temp.txt
filtered=$(cat temp.txt | tail -n 1)
echo ${filtered}
rm temp.txt
