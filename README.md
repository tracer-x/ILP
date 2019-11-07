# A sample LLVM analyser

This project requires LLVM & Z3. Supposed that our working folder named `ROOT`.

```
ROOT $ ls
clang+llvm-8.0.0    ILP
```

##### LLVM & Z3

Download Pre-Built Binaries of LLVM-8.0.0 from here: http://releases.llvm.org/download.html

##### Build ILP
Firstly, adjust the paths of LLVM in this line of `ROOT/ILP/src/tool/CMakeLists.txt`:

```
set(LLVM_INSTALL_DIR "ROOT/clang+llvm-8.0.0" CACHE STRING "Path to LLVM folder")
```

##### Steps to build:

```
ROOT/ILP $ mkdir build
ROOT/ILP $ cd build
ROOT/ILP/build $ cmake ..
ROOT/ILP/build $ make -j8
```

##### Run:

```
ROOT/ILP/build $ ./bin/ilp <.bc>
```

