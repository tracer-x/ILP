BENCHMARK=$1
cp src/$BENCHMARK.c .
echo "Running " $BENCHMARK
#clang -Isrc/include -emit-llvm -S -g $BENCHMARK.c -o $BENCHMARK.ll
clang -Isrc/include -emit-llvm -c -g $BENCHMARK.c -o $BENCHMARK.bc &> $BENCHMARK.clang
../build/bin/ilp ../test/$BENCHMARK.bc &> $BENCHMARK.ilp
