#!/bin/bash

cat $1 | tr " " "\n" | sort -g | sed ':a;N;$!ba;s/\n/ /g'
