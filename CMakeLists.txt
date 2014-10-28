list( APPEND CMAKE_CXX_FLAGS "-std=c++1y ${CMAKE_CXX_FLAGS}")

# this is my configure
set(CMAKE_C_COMPILER "/usr/local/Cellar/llvm/HEAD/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/local/Cellar/llvm/HEAD/bin/clang++")
set(ENV{DYLD_LIBRARY_PATH} "/Users/pagefault/opensource/llvm/build/lib")
include_directories("/Users/pagefault/opensource/llvm/projects/libcxx/include")
set(CMAKE_LIBRARY_PATH "/Users/pagefault/opensource/llvm/projects/libcxx/lib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -stdlib=libc++ -nostdinc++")

add_library(lua_cpp src/llex.cpp src/token.cpp src/dictionary.cpp)
add_executable(lua_cpp_test test/test_llex.cpp)
target_link_libraries(lua_cpp_test lua_cpp)
target_include_directories(lua_cpp_test PRIVATE src/)
