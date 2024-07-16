#!/bin/bash

bashrc_File=~/.bashrc
if [ -f "$bashrc_File" ];then
	echo "export HELLO=$HOSTNAME" >> "$bashrc_File"
	echo "LOCAL=$(whoami)" >> "$bashrc_File"
	
	gnome-terminal &
else
	echo ".bashrc file does not exist"
fi

