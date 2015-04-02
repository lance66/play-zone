--USE TestDB; --I created a test Database for this example.


CREATE TABLE CG_countries
(
	countries 	int		IDENTITY,
	country		varchar(25),
	CONSTRAINT	CG_countries_pk		PRIMARY KEY (countries)
);


CREATE TABLE CG_languages
(
	languages	int		IDENTITY,
	language	varchar(15),
	CONSTRAINT	CG_languages_pk		PRIMARY KEY (languages)
);

CREATE TABLE CG_settings
(
	settings	int	IDENTITY,
	sound		bit,
	country_flag	int,
	languages	int,
	auto_promotion	bit,
	arrows		bit,
	CONSTRAINT	CG_settings_countries_fk	FOREIGN KEY (country_flag)	REFERENCES	CG_countries(countries),
	CONSTRAINT	CG_settings_languages_fk	FOREIGN KEY (languages)		REFERENCES	CG_languages(languages),
	CONSTRAINT	CG_settings_pk		PRIMARY KEY (settings)
);

--I added this table beause it needed in the alter table statement that you sent.
--CREATE TABLE CG_user
--(test int);

--The alter table had an issue with the key word COLUMN and you didn't really need it... the following statement does that without the COLUMN keyword.
ALTER TABLE CG_user
	ADD settings int CONSTRAINT CG_user_settings_fk REFERENCES CG_settings(settings);