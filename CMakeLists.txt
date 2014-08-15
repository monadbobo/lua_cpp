list( APPEND CMAKE_CXX_FLAGS "-std=c++1y ${CMAKE_CXX_FLAGS}")

add_library(lua_cpp src/llex.cpp src/stream.cpp)
add_executable(lua_cpp_test test/test_llex.cpp)
target_link_libraries(lua_cpp_test lua_cpp)
target_include_directories(lua_cpp_test PRIVATE src/)
