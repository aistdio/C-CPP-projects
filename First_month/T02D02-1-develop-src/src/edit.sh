#!/bin/bash
cd ..

read -p 'Path from root: ' r_path
if [ ! -f "$r_path" ]; then
    echo 'File is not found'
    exit 1
fi

if [ ! -s "$r_path" ]; then
    echo 'File is empty'
    exit 2
fi

read -p 'String to replace: ' s1
if [ -z "$s1" ]; then
    echo 'Empty string'
    exit 3
fi
if ! grep -q "$s1" $r_path
then
    echo 'String not found'
    exit 4
fi

read -p 'Replacement: ' s2

sed -i '' "s/$s1/$s2/g" $r_path

sa="$(shasum -a 256 $r_path | cut -f1 -d' ')"
dateah="$(stat -f%Sm -t%H $r_path)"
dateam="$(stat -f%Sm -t%M $r_path)"
dateay="$(stat -f%Sm -t%Y $r_path)"
dateamo="$(stat -f%Sm -t%m $r_path)"
datead="$(stat -f%Sm -t%d $r_path)"
datea="${dateay}-${dateamo}-${datead} ${dateah}:${dateam}"
sizea=$(stat -f%z $r_path)
echo -e "${r_path} - ${sizea} - ${datea} - ${sa} - sha256" >> src/files.log


exit 0