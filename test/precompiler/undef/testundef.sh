#!/bin/bash

DIR="test/precompiler/undef"

cat /dev/null >"$DIR/log.txt"

rm $DIR/results/* 2>/dev/null
./$DIR/undef_test.o >/dev/null

OUT=$?

for file in $DIR/results/*.pre; do
	mv "$file" "${file%.pre}"
done

gcc -fsyntax-only $DIR/results/*.c &>$DIR/log.txt

if grep 'error:' $DIR/log.txt >/dev/null; then
	echo ">undef -> test pass"
else
	echo "##undef -> test error"
fi
