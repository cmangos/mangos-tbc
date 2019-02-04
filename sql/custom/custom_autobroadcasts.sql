CREATE TABLE custom_autobroadcasts (
	id TINYINT NOT NULL AUTO_INCREMENT,
	`text` varchar(255) NOT NULL,
	`type` tinyint NOT NULL,
	CONSTRAINT custom_autobroadcasts_PK PRIMARY KEY (id)
)
ENGINE=InnoDB
DEFAULT CHARSET=utf8
COLLATE=utf8_general_ci;

