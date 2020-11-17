run_mul_loop () { 
    for j in 1 2 3
    do
        echo "Running \`mul_loop_$1 1000\` for the $j-th time"
        ./target/mul_loop_$1 1000 >/dev/null
    done
}

run_mul_loop O0
run_mul_loop O2
run_mul_loop O3
