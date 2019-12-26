#!/bin/sh

# feed test data
./tail.out -5 "first line
second line
third line
last line"

./tail.out -2 "0
1
2
3
4
5
6"

# ./tail.out -2 "f"
