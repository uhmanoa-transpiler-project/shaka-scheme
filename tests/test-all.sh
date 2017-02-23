#! /bin/bash

for prog in ./*.out; do
    $prog
    read -n1 -r -p "Press any key to continue..." key
    clear
done
