for i in 100 200 500 1000 2000
do
    for j in 1 2 3
    do
        echo "Running \`mul_BLAS $i\` for the $j-th time"
        ./target/mul_BLAS $i >/dev/null
    done
done