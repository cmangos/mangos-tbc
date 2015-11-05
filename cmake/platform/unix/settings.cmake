# configure uninstaller
configure_file(
  "${ROOT_DIR}/cmake/platform/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY
)
message(STATUS "UNIX: Configuring uninstall target")

# create uninstaller target (allows for using "make uninstall")
add_custom_target(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
)
message(STATUS "UNIX: Created uninstall target")

message(STATUS "UNIX: Detected compiler: ${CMAKE_C_COMPILER}")
if(CMAKE_C_COMPILER MATCHES "gcc" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
  include("${ROOT_DIR}/cmake/compiler/gcc/settings.cmake")
elseif(CMAKE_C_COMPILER MATCHES "clang")
  include("${ROOT_DIR}/cmake/compiler/clang/settings.cmake")
else()
add_definitions(-D_BUILD_DIRECTIVE='"${CMAKE_BUILD_TYPE}"')
endif()

message(STATUS "UNIX: Use c++11")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -Wno-narrowing -Wno-deprecated-register")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -Wno-narrowing -Wno-deprecated-register")
