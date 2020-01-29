INSERT INTO `script_texts` (`entry`, `content_default`, `comment`) VALUES ('-1999930', 'Welcome to Honor Hold, $n.  It\'s good to have you.', 'Force Commander Danath Trollbane (Entry: 16819)');
DELETE FROM dbscript_string WHERE entry = "2000001300";
DELETE FROM dbscripts_on_quest_end WHERE id = "10254";
UPDATE quest_template SET CompleteScript = "0" WHERE entry = "10254";