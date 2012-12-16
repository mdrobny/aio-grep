#!/bin/bash

for i in `seq 100 100 20000`
do
	sed s/bufsize\([0-9]\)/bufsize\($i\)/ ./src/asynchronousfilereader.cpp > ./src/_asynchronousfilereader.cpp
	mv ./src/_asynchronousfilereader.cpp ./src/asynchronousfilereader.cpp
	make
	/usr/bin/time --output=time.log -a -f "%e" ./aio-grep -a domek ../../testfiles/* > /dev/null
	echo $i
	echo "\n"
done
echo "FINISHED"
