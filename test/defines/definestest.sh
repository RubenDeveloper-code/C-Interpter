#!/bin/bash

DIR="test/defines"

cat /dev/null >"$DIR/log.txt"

rm $DIR/results/* 2>/dev/null
./$DIR/defines_test.o >/dev/null

OUT=$?

if [ $OUT -ne 0 ]; then
	echo "##define -> test fail, error code: $OUT"
	exit 1
fi

for file in $DIR/results/*.pre; do
	mv "$file" "${file%.pre}"
done

gcc -fsyntax-only $DIR/results/*.c &>$DIR/log.txt

if grep -- '-Wimplicit-function-declaration' $DIR/log.txt &>/dev/null; then
	echo "##define -> test fail: -Wimplicit-function-declaration"
	cat $DIR/results/*
elif grep 'error:' $DIR/log.txt; then
	echo "##define -> test fail: error"
else
	echo ">define -> test pass"
fi
