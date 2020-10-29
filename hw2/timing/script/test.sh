#!/usr/bin/sh

for bin in timing1 timing2
do
    for arg in 5000000 10000000 20000000
    do
        echo "Running ${bin} ${arg} for 10 times"
        for n in $(seq 10)
        do
            echo "$n"
            ./bin/${bin} ${arg}
        done
    done
done