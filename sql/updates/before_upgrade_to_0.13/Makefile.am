# Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

## Process this file with automake to produce Makefile.in

## Sub-directories to parse

## Change installation location
#  datadir = mangos/sql/updates
pkgdatadir = $(datadir)/mangos/sql/updates/before_upgrade_to_0.13

## Files to be installed
#  Install basic SQL files to datadir
pkgdata_DATA = \
	032_7059_01_characters.sql \
	041_7932_01_characters_character_pet.sql \
	045_8098_01_characters_character_action.sql \
	045_8098_03_characters_character_pet.sql \
	045_8098_04_characters_pet_spell.sql \
	052_8072_01_characters_characters.sql \
	055_8332_01_realmd_realmcharacters.sql \
	058_7546_02_realmd_uptime.sql \
	061_7067_03_characters_character_spell.sql \
	066_8402_01_characters_guild_eventlog.sql \
	066_8402_02_characters_guild_bank_eventlog.sql \
	066_8409_01_characters_guild.sql \
	077_8728_01_realmd_account.sql \
	README

## Additional files to include when running 'make dist'
#  SQL update files, to upgrade database schema from older revisions
EXTRA_DIST = \
	032_7059_01_characters.sql \
	041_7932_01_characters_character_pet.sql \
	045_8098_01_characters_character_action.sql \
	045_8098_03_characters_character_pet.sql \
	045_8098_04_characters_pet_spell.sql \
	052_8072_01_characters_characters.sql \
	055_8332_01_realmd_realmcharacters.sql \
	058_7546_02_realmd_uptime.sql \
	061_7067_03_characters_character_spell.sql \
	066_8402_01_characters_guild_eventlog.sql \
	066_8402_02_characters_guild_bank_eventlog.sql \
	066_8409_01_characters_guild.sql \
	077_8728_01_realmd_account.sql \
	README
