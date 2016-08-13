# This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

cmake_minimum_required (VERSION 2.6)
set(EXECUTABLE_NAME "vmap_extractor")
project (${EXECUTABLE_NAME})

add_executable(${EXECUTABLE_NAME} adtfile.cpp  dbcfile.cpp gameobject_extract.cpp model.cpp  mpq_libmpq.cpp  vmapexport.cpp  wdtfile.cpp  wmo.cpp)

target_link_libraries(${EXECUTABLE_NAME} mpq bz2 z)
install(TARGETS ${EXECUTABLE_NAME} DESTINATION ${BIN_DIR}/tools)
