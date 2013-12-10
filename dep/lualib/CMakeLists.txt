#
# This code is part of MaNGOS. Contributor & Copyright details are in AUTHORS/THANKS.
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

set(LIBRARY_NAME lualib)

set(LIBRARY_SRCS
  lapi.c
  lapi.h
  lauxlib.h
  lbaselib.c
  lbitlib.c
  lcode.c
  lcode.h
  lcorolib.c
  lctype.c
  lctype.h
  ldblib.c
  ldebug.c
  ldebug.h
  ldo.c
  ldo.h
  ldump.c
  lfunc.c
  lfunc.h
  lgc.c
  lgc.h
  linit.c
  liolib.c
  llex.c
  llex.h
  llimits.h
  lmathlib.c
  lmem.c
  lmem.h
  loadlib.c
  lobject.c
  lobject.h
  lopcodes.c
  lopcodes.h
  loslib.c
  lparser.c
  lparser.h
  lstate.c
  lstate.h
  lstring.c
  lstring.h
  lstrlib.c
  ltable.c
  ltable.h
  ltablib.c
  ltm.c
  ltm.h
  lua.c
  lua.h
  luaconf.h
  lualib.h
  lundump.c
  lundump.h
  lvm.c
  lvm.h
  lzio.c
  lzio.h
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(${LIBRARY_NAME} STATIC
  ${LIBRARY_SRCS}
)