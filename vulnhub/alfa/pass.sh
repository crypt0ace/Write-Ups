#!/bin/bash
for i in {0..9}; do
 for j in {0..9}; do
  for k in {0..9}; do
   echo "milo$i$j$k" >> pass.txt
  done
 done
done
