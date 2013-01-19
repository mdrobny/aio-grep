#!/bin/bash

for i in `ls output/`
do
	time=0
	for n in `seq 1 5`
	do
		time=$(($time+`/usr/bin/time -f "%e" ./a.out -a fittest ../../usb/output/$i/* > /dev/null`))
	done
	echo $i
	echo $time >> usb-a-time.log
done

for i in `ls output/`
do
	/usr/bin/time --output=usb-s-time.log -a -f "%e" ./a.out -s fittest ../../usb/output/$i/* > /dev/null
	echo $i
done

for i in `ls output/`
do
	/usr/bin/time --output=usb-m-time.log -a -f "%e" ./a.out -m fittest ../../usb/output/$i/* > /dev/null
	echo $i
done

echo "FINISHED"
