#!/bin/bash

dir="./out"
if [[ ! -d "$dir" ]]; then
    mkdir $dir
fi
xbase="${1##*/}"
filename="${xbase%.*}"
output="$dir/$filename" 
gcc $1 -o "$output"
$output "${@:2}"
