#!/bin/bash

if [[ "$0" = /* ]]
then
	echo "You must call ./patch.sh in working directory"
else
	cp -R patch/* cocos2d
	echo "Patch complete"
fi
