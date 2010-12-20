# Copyright (C) 2005-2010 MaNGOS <http://getmangos.com/>
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
SUBDIRS = before_upgrade_to_0.13

## Change installation location
#  datadir = mangos/sql/updates
pkgdatadir = $(datadir)/mangos/sql/updates

## Files to be installed
#  Install basic SQL files to datadir
pkgdata_DATA = \
	README \
	s0084_10008_01_realmd_realmd_db_version.sql \
	s0308_7560_01_mangos_gameobject_template.sql \
	s0345_10628_01_mangos_mangos_string.sql \
	s0346_10629_01_mangos_mangos_string.sql \
	s0356_10621_01_mangos_quest_template.sql \
	s0378_xxxxx_01_mangos_spell_proc_event.sql \
	s0379_10654_01_mangos_game_event_creature_quest.sql \
	s0382_10660_01_mangos_game_event_quest.sql \
	s0384_10664_01_characters_arena_team_stats.sql \
	s0386_10662_01_characters_item_loot.sql \
	s0391_10679_01_mangos_npc_vendor_template.sql \
	s0391_10679_02_mangos_creature_template.sql \
	s0407_10704_01_mangos_gossip_menu_option.sql \
	s0418_7908_01_mangos_creature_template.sql \
	s0418_7908_02_mangos_creature_addon.sql \
	s0418_7908_03_mangos_creature_template_addon.sql \
	s0481_8249_01_mangos_spell_proc_item_enchant.sql \
	s0481_8249_02_mangos_spell_chain.sql \
	s0481_xxxxx_03_mangos_spell_bonus_data.sql \
	s0498_10867_01_mangos_npc_trainer_template.sql \
	s0498_10867_02_mangos_creature_template.sql \
	s0507_8339_01_characters_characters.sql \
	s0507_8339_02_characters_character_battleground_data.sql \
	s0511_8361_01_mangos_spell_bonus_data.sql \
	s0531_8596_01_characters_bugreport.sql

## Additional files to include when running 'make dist'
#  SQL update files, to upgrade database schema from older revisions
EXTRA_DIST = \
	README \
	s0084_10008_01_realmd_realmd_db_version.sql \
	s0308_7560_01_mangos_gameobject_template.sql \
	s0345_10628_01_mangos_mangos_string.sql \
	s0346_10629_01_mangos_mangos_string.sql \
	s0356_10621_01_mangos_quest_template.sql \
	s0378_xxxxx_01_mangos_spell_proc_event.sql \
	s0379_10654_01_mangos_game_event_creature_quest.sql \
	s0382_10660_01_mangos_game_event_quest.sql \
	s0384_10664_01_characters_arena_team_stats.sql \
	s0386_10662_01_characters_item_loot.sql \
	s0391_10679_01_mangos_npc_vendor_template.sql \
	s0391_10679_02_mangos_creature_template.sql \
	s0407_10704_01_mangos_gossip_menu_option.sql \
	s0418_7908_01_mangos_creature_template.sql \
	s0418_7908_02_mangos_creature_addon.sql \
	s0418_7908_03_mangos_creature_template_addon.sql \
	s0481_8249_01_mangos_spell_proc_item_enchant.sql \
	s0481_8249_02_mangos_spell_chain.sql \
	s0481_xxxxx_03_mangos_spell_bonus_data.sql \
	s0498_10867_01_mangos_npc_trainer_template.sql \
	s0498_10867_02_mangos_creature_template.sql \
	s0507_8339_01_characters_characters.sql \
	s0507_8339_02_characters_character_battleground_data.sql \
	s0511_8361_01_mangos_spell_bonus_data.sql \
	s0531_8596_01_characters_bugreport.sql
