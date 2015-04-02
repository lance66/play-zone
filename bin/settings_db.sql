
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
	auto_promotion	bit,
	arrows		bit,
	CONSTRAINT	CG_settings_pk		PRIMARY KEY (settings)
);


ALTER TABLE CG_user
	ADD settings int CONSTRAINT CG_user_settings_fk REFERENCES CG_settings(settings);

ALTER TABLE CG_user
	ADD userCountry int CONSTRAINT CG_user_countries_fk REFERENCES CG_countries(countries);

ALTER TABLE CG_user
	ADD userLanguage int CONSTRAINT CG_user_languages_fk references CG_languages(languages);