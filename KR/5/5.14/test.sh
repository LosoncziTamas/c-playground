#!/bin/sh

# feed test data
printf '%s\n' --------------------
printf 'aaaa\nbbbb\ncccc\ndddd\n' | ./sort.out
printf '%s\n' --------------------
printf 'aaaa\nbbbb\ncccc\ndddd\n' | ./sort.out -r
printf '%s\n' --------------------
printf '0.12\n2.0\n4.0\n3.0\n' | ./sort.out -r -n
printf '%s\n' --------------------
printf '0.12\n2.0\n4.0\n3.0\n' | ./sort.out -n -r
printf '%s\n' --------------------
printf '0.12\n2.0\n4.0\n3.0\n' | ./sort.out -n
printf '%s\n' --------------------
printf '0.12\n2.0\n4.0\n3.0\n' | ./sort.out -r