ALTER TABLE db_version CHANGE COLUMN required_124_7904_01_mangos_creature_template required_124_8237_01_mangos_creature_template bit;

UPDATE creature_template
  SET mindmg = ROUND(mindmg + attackpower), maxdmg=ROUND(maxdmg+attackpower);
