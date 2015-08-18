#! /bin/sh

rm -rf BUILD
mkdir BUILD
cd BUILD && cmake -G Ninja .. && ninja && bin/test-strlcpy -r compact -s

