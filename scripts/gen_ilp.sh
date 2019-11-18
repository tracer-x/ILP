ROOT=/home/xuanlinhha/CCXX/cmake
CLANG=$ROOT/clang+llvm-8.0.0/bin/clang
PROJECT=$ROOT/ILP
TEST=$PROJECT/test

# create folder
if [ ! -d "$TEST/bc" ]; then
	mkdir $TEST/bc
fi
if [ ! -d "$TEST/ilp" ]; then
	mkdir $TEST/ilp
fi

# clang compile
echo "Compiling ..."
for p in $TEST/input/*.c; do
	c=$(basename "$p")
	name="${c%.*}"
	$CLANG -emit-llvm -c -g "$p" -o "$TEST/bc/$name.bc"
done

# generate ilp input
echo "Creating ilp input ..."
for bc in $TEST/bc/*.bc; do
	c=$(basename "$bc")
	name="${c%.*}"
	# echo $c
	$PROJECT/build/bin/ilp "$bc" "$TEST/ilp/$name.ilp"
done
