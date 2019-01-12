ALTER TABLE db_version CHANGE COLUMN required_s2391_01_mangos_creature_cooldown required_s2392_01_mangos_quest_template_emote_delays bit;

ALTER TABLE quest_template ADD COLUMN IncompleteEmoteDelay INT(11) UNSIGNED NOT NULL DEFAULT '0' AFTER IncompleteEmote;
ALTER TABLE quest_template ADD COLUMN CompleteEmoteDelay INT(11) UNSIGNED NOT NULL DEFAULT '0' AFTER CompleteEmote;