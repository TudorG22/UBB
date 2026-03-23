for f in *.c; do 
    exe="${f%.c}"
    ./"$exe"
    code=$?
    echo "$exe exited with $code"
    [ $code -ne 0 ]
done