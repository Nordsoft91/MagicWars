#!/bin/bash

if [[ "$0" = /* ]]
then
	echo "You must call ./patch.sh in working directory"
else
	tar -xvzf ./import.tar import
	cp -R patch/* cocos2d
	cp -R import/* Resources
	rm -rf import
	echo "Patch complete"
fi
