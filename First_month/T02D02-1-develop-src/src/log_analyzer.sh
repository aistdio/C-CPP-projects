#!/bin/bash
cd ..

read -p 'Path to the file: ' r_path
if [[ ! $r_path == *.log ]]; then
    echo 'Not supported'
    exit 1
fi
if [ ! -s "$r_path" ]; then
    echo 'File is empty'
    exit 2
fi

lines=$(grep -c "-" $r_path)
files=$(cat $r_path | cut -d ' ' -f 1 | uniq | wc -l | awk '{print $1}')
hashes=$(cat $r_path | cut -d ' ' -f 8 | sort | uniq | wc -l)
let "hashes-=1"
echo "$lines $files $hashes"

exit 0