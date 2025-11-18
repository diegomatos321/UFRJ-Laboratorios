#!/bin/bash

if [ "$1" -gt "$2" ]; then
	echo "$1 é maior que $2"
elif [ "$1" -lt "$2" ]; then
	echo "$1 menor que $2"
else 
	"$1 é igual a $2"
fi
