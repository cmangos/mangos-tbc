#
# This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

set(EXECUTABLE_NAME ${CMANGOS_BINARY_TESTING_NAME})

add_definitions(-DBUILD_TESTING)

# Find all the input files
FILE(GLOB_RECURSE LIBRARY_SRCS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.h" "*.cpp")

# Create visual studio groups using folder structure
foreach(source ${LIBRARY_SRCS})
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

add_executable(${EXECUTABLE_NAME}
  ${LIBRARY_SRCS}
)

target_include_directories(${EXECUTABLE_NAME}
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Core"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Integration"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Unit"
  PRIVATE ${OPENSSL_INCLUDE_DIR}
  PRIVATE ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${EXECUTABLE_NAME}
  Catch2
  shared
  game
  gsoap
  mangosd_core
)

set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Bin")

if(WIN32)
  target_link_libraries(${EXECUTABLE_NAME}
    optimized ${MYSQL_LIBRARY}
    optimized ${OPENSSL_LIBRARIES}
    debug ${MYSQL_DEBUG_LIBRARY}
    debug ${OPENSSL_DEBUG_LIBRARIES}
    ${Boost_LIBRARIES}
  )
  if(MINGW)
    target_link_libraries(${EXECUTABLE_NAME}
      wsock32
      ws2_32
    )
  endif()

  # Define OutDir to source/bin/(platform)_(configuaration) folder.
  set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}")
  set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}")
  set_target_properties(${EXECUTABLE_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)")
  set_target_properties(${EXECUTABLE_NAME} PROPERTIES PROJECT_LABEL "testing")

  # Add provided dependency lib to dev folder
  string(REGEX REPLACE "/" "\\\\" LibFolder ${DEV_PROVIDED_LIBS_FOLDER})
  add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND copy \"${LibFolder}\\*.dll\" \"$(OutDir)\")

  # Add conf file to dev folder
  add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different \"${BASE_DIR}/realmd/realmd.conf.dist.in\" \"$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/realmd.conf.dist\")

   # Add conf file to dev folder
  add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different \"${BASE_DIR}/mangosd/mangosd.conf.dist.in\" \"$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/mangosd.conf.dist\")
endif()

if(UNIX)
  target_link_libraries(${EXECUTABLE_NAME}
    ${OPENSSL_LIBRARIES}
    ${OPENSSL_EXTRA_LIBRARIES}
    ${Boost_TEST_LIBRARIES}
  )

  if(POSTGRESQL AND POSTGRESQL_FOUND)
    target_link_libraries(${EXECUTABLE_NAME} ${PostgreSQL_LIBRARIES})
  else()
    target_link_libraries(${EXECUTABLE_NAME} ${MYSQL_LIBRARY})
  endif()
endif()

set(EXECUTABLE_LINK_FLAGS "")

if(UNIX)
  if (APPLE)
    set(EXECUTABLE_LINK_FLAGS "-pthread -framework Carbon")
  else()
    set(EXECUTABLE_LINK_FLAGS "-pthread -rdynamic")
  endif()
endif()

set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINK_FLAGS
  "${EXECUTABLE_LINK_FLAGS}"
)

install(TARGETS ${EXECUTABLE_NAME} DESTINATION ${OUTPUT_DIR})
install(FILES "${BASE_DIR}/realmd/realmd.conf.dist.in" DESTINATION ${CONF_DIR} RENAME realmd.conf.dist)
install(FILES "${BASE_DIR}/mangosd/mangosd.conf.dist.in" DESTINATION ${CONF_DIR} RENAME mangosd.conf.dist)

if(MSVC)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/\${BUILD_TYPE}/${EXECUTABLE_NAME}.pdb DESTINATION ${OUTPUT_DIR} CONFIGURATIONS Debug)
endif()
