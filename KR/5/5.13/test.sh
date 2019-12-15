#!/bin/sh

# compile
cc tail.c -Wall -o tail.out

# feed test data
test1src=`cat test1.input`
./tail.out -2 $test1src > test1.result
diff test1.result test1.expected
