CREATE TABLE custom_spellregulator (
	spellid bigint NOT NULL,
	modifier FLOAT NOT NULL,
    allranks tinyint NOT NULL,
	CONSTRAINT custom_spellregulator_PK PRIMARY KEY (spellid)
)
ENGINE=InnoDB
DEFAULT CHARSET=utf8
COLLATE=utf8_general_ci;

