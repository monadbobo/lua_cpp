solution  "lua_cpp"
  configurations { "Debug", "Release" }
  project "lua_cpp"
    language "C++"
    kind     "SharedLib"
    files  { "src/**.h", "src/**.cpp" }

    buildoptions { "-std=c++1y" }
    configuration { "Debug*" }
      defines { "_DEBUG", "DEBUG" }
      flags   { "Symbols" }
 
    configuration { "Release*" }
      defines { "NDEBUG" }
      flags   { "Optimize" }

  project "lua_cpp_test"
    language "C++"
    kind     "ConsoleApp"
    files {"test/*.cpp"}

    buildoptions { "-std=c++1y" }
    links {"lua_cpp"}

    configuration { "Debug*" }
      defines { "_DEBUG", "DEBUG" }
      flags   { "Symbols" }
 
    configuration { "Release*" }
      defines { "NDEBUG" }
      flags   { "Optimize" }
