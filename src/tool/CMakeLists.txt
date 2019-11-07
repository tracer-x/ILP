add_executable(ilp main.cpp)

# LLVM
set(LLVM_INSTALL_DIR "/home/xuanlinhha/CCXX/cmake/clang+llvm-8.0.0" CACHE STRING "Path to LLVM folder")
list(APPEND CMAKE_MODULE_PATH ${LLVM_INSTALL_DIR}/lib/cmake/llvm)
include(LLVMConfig)

target_include_directories(ilp PUBLIC ${LLVM_INCLUDE_DIRS})
target_link_libraries(ilp PUBLIC LLVMBitReader LLVMBitWriter LLVMIRReader)

# set relative include path
include_directories(..)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
