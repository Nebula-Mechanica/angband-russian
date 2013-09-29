#!/bin/bash

# Converts the whole source tree to CP-1251 line endings
# Note! This will mess file permissions

find . -type f > /tmp/to-dos-list

for file in `cat /tmp/to-dos-list` ; do
	if file $file | cut -d: -f2 | grep text >/dev/null 2>&1 ; then
		recode -f KOI8-R..CP1251 > < $file $file.new
		mv $file.new $file
	fi
done

rm /tmp/to-dos-list
