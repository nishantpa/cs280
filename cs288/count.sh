#!/bin/bash
# Swami Shreeji
# Almost ready for submission. Use array

ls /bin > temp.txt

   for i in {a..z}
     do
       echo $i $(grep ^$i temp.txt | wc -l)
   done
rm temp.txt
