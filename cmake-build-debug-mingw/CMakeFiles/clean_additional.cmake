# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\launcher_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\launcher_autogen.dir\\ParseCache.txt"
  "launcher_autogen"
  )
endif()
