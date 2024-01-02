#!/bin/bash

DIR="test/includes"

cat /dev/null >"$DIR/log.txt"

rm $DIR/results/* 2>/dev/null
./$DIR/includes_test.o >/dev/null

OUT=$?

if [ $OUT -ne 0 ]; then
	echo "#test fail, error code: $OUT"
	exit 1
fi

for file in $DIR/results/*.pre; do
	mv "$file" "${file%.pre}"
done

gcc -fsyntax-only $DIR/results/*.c &>log.txt

if grep -- '-Wimplicit-function-declaration' log.txt &>/dev/null; then
	echo "#test fail: -Wimplicit-function-declaration"
else
	echo ">test pass"
fi
