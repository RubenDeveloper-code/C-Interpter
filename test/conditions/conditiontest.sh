#!/bin/bash

DIR="test/conditions"

cat /dev/null >"$DIR/log.txt"

rm $DIR/results/* 2>/dev/null
./$DIR/conditions_test.o >/dev/null

OUT=$?

if [ $OUT -ne 0 ]; then
	echo "##define -> test fail, error code: $OUT"
	exit 1
else
	echo ">test conditions -> pass"
fi
