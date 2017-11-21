#!/bin/bash

   for arg in "$@"; do
      ls "$@" > temp1.txt
      tac temp1.txt
   done
rm temp1.txt

