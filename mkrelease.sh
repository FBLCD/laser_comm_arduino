#!/bin/bash

PROJECT_VERSION="0.1"

if [ "$(which zip)" != "/usr/bin/zip" ]; then
	echo "!. Missing tools"
	exit 1
fi

echo "1. Regen release folder"
rm -rf release
mkdir release

echo "2. Copy sq2c"
mkdir release/sq2c
cp -r dist/sq2c/{win,linux} release/sq2c/

echo "3. Install .ino scripts"
mkdir release/src
cp -r src/ino/v2/{ldr,laser} release/src/

echo "4. Zip release package ($PROJECT_VERSION)"
zip -r laser_comm_arduino-r${PROJECT_VERSION}.zip release/

echo "+. All done"
exit 0