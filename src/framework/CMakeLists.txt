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

set(LIBRARY_NAME framework)

file(GLOB_RECURSE SRC_GRP_DYNAMIC             Dynamic/*.cpp Dynamic/*.h)
file(GLOB_RECURSE SRC_GRP_GAMESYSTEM          GameSystem/*.cpp GameSystem/*.h)
file(GLOB_RECURSE SRC_GRP_PLATFORM            Platform/*.cpp Platform/*.h)
file(GLOB_RECURSE SRC_GRP_POLICIES            Policies/*.cpp Policies/*.h)
file(GLOB_RECURSE SRC_GRP_UTIL                Utilities/*.cpp Utilities/*.h)
file(GLOB_RECURSE SRC_GRP_LINKED_REFERENCE    Utilities/LinkedReference/*.cpp Utilities/LinkedReference/*.h)

set(LIBRARY_SRCS
    ${SRC_GRP_DYNAMIC}
    ${SRC_GRP_GAMESYSTEM}
    ${SRC_GRP_PLATFORM}
    ${SRC_GRP_POLICIES}
    ${SRC_GRP_UTIL}
    ${SRC_GRP_LINKED_REFERENCE}
)

source_group("Dynamic"                    FILES    ${SRC_GRP_DYNAMIC})
source_group("GameSystem"                 FILES    ${SRC_GRP_GAMESYSTEM})
source_group("Platform"                   FILES    ${SRC_GRP_PLATFORM})
source_group("Policies"                   FILES    ${SRC_GRP_POLICIES})
source_group("Utilities"                  FILES    ${SRC_GRP_UTIL})
source_group("Utilities\\LinkedReference" FILES    ${SRC_GRP_LINKED_REFERENCE})

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(${LIBRARY_NAME} OBJECT
  ${LIBRARY_SRCS}
)
