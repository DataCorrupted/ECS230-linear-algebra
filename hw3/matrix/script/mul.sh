for i in 100 200 500 1000 2000
do
    echo "Running \`mul $i\`"
    ./target/mul $i
done