#!/bin/sh

# feed test data
./tail.out -2 "first line
second line
third line
last line"

./tail.out -2 "f"

./tail.out -2 "0
1
2
3
4
5
6
"