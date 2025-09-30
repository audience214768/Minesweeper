make clean
make
./server < ../../testcases/basic/13.in > ans.out
if diff -w -q ../../testcases/basic/13.out ans.out; then
    echo "AC"
else
    echo "WA"
fi