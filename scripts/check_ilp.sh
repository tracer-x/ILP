ROOT=/home/xuanlinhha/CCXX/cmake
CLANG=$ROOT/clang+llvm-8.0.0/bin/clang
PROJECT=$ROOT/ILP
TEST=$PROJECT/test

# create folder
if [ ! -d "$TEST/output" ]; then
	mkdir $TEST/output
fi

echo "Running ..."
for p in $TEST/ilp/*.ilp; do
	c=$(basename "$p")
	name="${c%.*}"
	lp_solve "$p" &> "$TEST/output/$name.txt"
done
