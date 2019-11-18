ROOT=/home/xuanlinhha/CCXX/cmake
CLANG=$ROOT/clang+llvm-8.0.0/bin/clang
CLANG_FORMAT=$ROOT/clang+llvm-8.0.0/bin/clang-format
PROJECT=$ROOT/ILP
SRC=$PROJECT/src
TEST=$PROJECT/test
echo "=== PATH ==="
echo $CLANG_FORMAT
echo $SRC 
echo "============"

# echo "=== CLANG COMPILE ==="
# $CLANG -Isrc/include -emit-llvm -c -g -S $TEST/test.c -o $TEST/test.ll
# $CLANG -Isrc/include -emit-llvm -c -g $TEST/test.c -o $TEST/test.bc
# echo "====================="

echo "=== CLANG FORMAT ==="
$CLANG_FORMAT -i $SRC/tool/*.cpp
$CLANG_FORMAT -i $SRC/graph/*.cpp
$CLANG_FORMAT -i $SRC/graph/*.h
$CLANG_FORMAT -i $SRC/util/*.cpp
$CLANG_FORMAT -i $SRC/util/*.h
echo "====================="
