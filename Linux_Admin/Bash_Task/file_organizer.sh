#!/bin/bash

directory=$1
mkdir -p "$directory/images" "$directory/documents" "$directory/others"
files=$(ls "$directory")
for file in $files;do
	if [ -f "$directory/$file" ];then
		if [[ "$file" == *.jpg || "$file" == *.png || "$file" == *.gif ]];then
			mv "$directory/$file" "$directory/images/$file"	
		elif [[ $file == *.txt || $file == *.doc || $file == *.pdf ]];then			
  			mv "$directory/$file" "$directory/documents/$file"
		else
			mv "$directory/$file" "$directory/others/$file"
		fi
	fi
done
