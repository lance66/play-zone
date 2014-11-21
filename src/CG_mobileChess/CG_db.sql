------------------------------------------------------
--Chess Games SQL Script
--Date Created: 11/04/2014
--Filename: CG_db.sql
------------------------------------------------------

--DROP TABLE CG_games;
--DROP TABLE CG_user_UserRole;
--DROP TABLE CG_user_role;
--DROP TABLE CG_user;

------------------------------------------------------
--Table: CG_user
--Purpose: Store user's information and the data to
--	calculate their ELO rating.
------------------------------------------------------
CREATE TABLE CG_user
(
	UserID				int				IDENTITY,
	Username			nvarchar(32)	NOT NULL		UNIQUE, --User nvarchar
	Passwd				nvarchar(64)	NOT NULL,				--for unicode standards.
	Email				nvarchar(64)	NOT NULL,
	JoinDate			date,
	CurrentELO			float			DEFAULT 0,
	NumGames			int				DEFAULT 0,
	TotalScore			float			DEFAULT 0,
	TotalOpponentELO	decimal(38, 1)	DEFAULT 0,
	Banned				bit				NOT NULL DEFAULT 0,
	LoggedIn			bit				NOT NULL DEFAULT 0,
	CONSTRAINT CG_user_pk PRIMARY KEY (UserID)
);

------------------------------------------------------
--Table: CG_user_role
--Purpose: Stores a user's individual roles.
--	A user can have many roles.
--	EX: Standard user, premium, admin, moderator
------------------------------------------------------
CREATE TABLE CG_user_role
(
	RoleID				int				IDENTITY,
	CG_Role				varchar(12),
	CONSTRAINT CG_role_pk PRIMARY KEY (RoleID)
);

------------------------------------------------------
--Table: CG_user_UserRole
--Purpose: An intermediate table for the many to many
--	relationship between CG_user and CG_user_UserRole.
------------------------------------------------------
CREATE TABLE CG_user_UserRole
(
	UserID				int				NOT NULL,
	RoleID				int				NOT NULL,
	CONSTRAINT CG_user_UserRole_UserID_fk Foreign Key (UserID) REFERENCES CG_user(UserID),
	CONSTRAINT CG_user_UserRole_RoleID_fk Foreign Key (RoleID) REFERENCES CG_user_role(RoleID),
	CONSTRAINT CG_user_UserRole_pk PRIMARY KEY (UserID, RoleID)
);

------------------------------------------------------
--Table: CG_games
--Purpose: Store all the info about a game and two
--	foreign keys for the white and black players from
--	the CG_user table.
------------------------------------------------------
CREATE TABLE CG_games
(
	GameID				bigint			IDENTITY, --Using a bigint to account for many
	CG_Date				datetime,				  --games being played in the future.
	CG_Result			decimal(2, 1),
	WhiteELO			float			NOT NULL,
	BlackELO			float			NOT NULL,
	PlayerWhite			int				NOT NULL,
	PlayerBlack			int				NOT NULL,
	AlgebraicNotation	varchar(4000),
	CONSTRAINT CG_games_PlayerWhite_fk Foreign Key (PlayerWhite) REFERENCES CG_user(UserID),
	CONSTRAINT CG_games_PlayerBlack_fk Foreign Key (PlayerBlack) REFERENCES CG_user(UserID),
	CONSTRAINT CG_games_pk PRIMARY KEY (GameID)
);

INSERT INTO CG_user
(Username, Passwd, Email, JoinDate, CurrentELO, NumGames, TotalScore, TotalOpponentELO, Banned, LoggedIn)
VALUES('Raffael', 'newuser1', 'Raffael@something.com', '10-28-2014', 2851, 340, 250, 918000, 0, 0);

INSERT INTO CG_user
(Username, Passwd, Email, JoinDate, CurrentELO, NumGames, TotalScore, TotalOpponentELO, Banned, LoggedIn)
VALUES('Trudodyr', 'newuser1', 'Trudodyr@something.com', '07-07-2015', 2724, 4050, 3000, 10732500, 0, 0);

INSERT INTO CG_user
(Username, Passwd, Email, JoinDate, CurrentELO, NumGames, TotalScore, TotalOpponentELO, Banned, LoggedIn)
VALUES('lolololololol', 'LMFAO245636', 'lolololololol@something.com', '07-01-2015', 2735, 5000, 2500, 918000, 0, 0);

INSERT INTO CG_user
(Username, Passwd, Email, JoinDate, CurrentELO, NumGames, TotalScore, TotalOpponentELO, Banned, LoggedIn)
VALUES('MrPickles', 'M0re0ver', 'MrPickles@something.com', '12-12-2016', 2610, 6500, 4500, 15600000, 0, 0);

INSERT INTO CG_user
(Username, Passwd, Email, JoinDate, CurrentELO, NumGames, TotalScore, TotalOpponentELO, Banned, LoggedIn)
VALUES('Daniel Freeman', '+_)(*&^%$#@!', 'chess@chessgames.com', '10-28-2014', 1900, 7500, 5000, 11250000, 1, 0);

INSERT INTO CG_user
(Username, Passwd, Email, JoinDate, CurrentELO, NumGames, TotalScore, TotalOpponentELO, Banned, LoggedIn)
VALUES('Cindy Phillips', 'Im huge', 'Cindy@something.com', '10-31-2014', 2830, 200, 150, 520000, 1, 0);

INSERT INTO CG_user
(Username, Passwd, Email, JoinDate, CurrentELO, NumGames, TotalScore, TotalOpponentELO, Banned, LoggedIn)
VALUES('StarWars', 'LYbf773h8dh', 'StarWars@something.com', '12-09-2015', 2798, 10000, 5121, 27400000, 1, 0);

INSERT INTO CG_user
(Username, Passwd, Email, JoinDate, CurrentELO, NumGames, TotalScore, TotalOpponentELO, Banned, LoggedIn)
VALUES('DarkNolan', '<>?:"{}|', 'DarkNolan@something.com', '06-02-2016', 2740, 3400, 3100,  8160000, 0, 0);

INSERT INTO CG_user
(Username, Passwd, Email, JoinDate, CurrentELO, NumGames, TotalScore, TotalOpponentELO, Banned, LoggedIn)
VALUES('YaaCovn', 'Play1nthe9ark', 'YaaCovn@something.com', '05-07-2018', 2450, 7850, 3000,  20410000, 0, 0);

INSERT INTO CG_user
(Username, Passwd, Email, JoinDate, CurrentELO, NumGames, TotalScore, TotalOpponentELO, Banned, LoggedIn)
VALUES('SnoopDogg', 'GeorgiaTb5isli$*$(', 'SnoopDogg@something.com', '02-09-2018', 2550, 6485, 3401, 16536750, 0, 0);

INSERT INTO CG_games
(CG_Date, CG_Result, WhiteELO, BlackELO, PlayerWhite, PlayerBlack, AlgebraicNotation)
VALUES('10-28-2014', 1, 2785, 2635, 1, 2, '1.Nf3 Nc6 2.e4 e5 3.Bc4 Nf6 4.d3 Be7 5.O-O O-O 6.Re1 d6 7.c3
h6 8.h3 Re8 9.Nbd2 Bf8 10.Nf1 g6 11.Ne3 Bg7 12.b4 Ne7 13.Bb3
c6 14.Bb2 a5 15.a3 Nh5 16.d4 Nf4 17.c4 Qc7 18.Qc2 Be6 19.dxe5
dxe5 20.c5 axb4 21.axb4 Rxa1 22.Bxa1 Rd8 23.Bxe6 Nxe6 24.Nc4
Nd4 25.Bxd4 exd4 26.Nd6 Rxd6 27.cxd6 Qxd6 28.Qc5 Qd8 29.Rd1 b6
30.Qc4 Qd6 31.Ne1 Qe5 32.Qc2 g5 33.Nd3 Qe6 34.Rc1 h5 35.Qe2
Ng6 36.Qxh5 Qxe4 37.Qf3 Qxf3 38.gxf3 Ne5 39.Nxe5 Bxe5 40.Rxc6
d3 41.Kf1 d2 42.Ke2 Bd4 43.Rd6 d1=Q+ 44.Kxd1 Bxf2+ 45.Ke2 Bg1
46.Rd5 f6 47.Rd7');

INSERT INTO CG_games
(CG_Date, CG_Result, WhiteELO, BlackELO, PlayerWhite, PlayerBlack, AlgebraicNotation)
VALUES('10-28-2014', 0.5, 2795, 2627, 1, 2,'1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e6
7. f3 b5 8. g4 h6 9. Qd2 b4 10. Na4 Nbd7 11. O-O-O Ne5 12. b3
Bd7 13. Nb2 d5 14. Bf4 Nxf3 15. Nxf3 Nxe4 16. Qd4 f6 17. Bd3
Bc5 18. Bxe4 Bxd4 19. Bg6+ Kf8 20. Rxd4 a5 21. Re1 Be8 22. Nh4
e5 23. Rd2 a4 24. bxa4 Kg8 25. Bg3 d4 26. Rd3 h5 27. Bxe8 Qxe8
28. g5 Rc8 29. g6 Rh6 30. Rxd4 Rxg6 31. Nxg6 Qxg6 32. Rd2 Rc3
33. Red1 Kh7 34. Kb1 Qf5 35. Be1 Ra3 36. Rd6 Rh3 37. a5 Rxh2
38. Rc1 Qe4 39. a6 Qa8 40. Bxb4 h4 41. Bc5 h3 42. Nd3 Rd2
43. Rb6 h2 44. Nf2 Qd5 45. Be3 Re2 46. Rb3 f5 47. a7 Rxe3
48. Rxe3 Qb7+ 49. Rb3 Qxa7 50. Nh1 f4 51. c4 e4 52. c5 e3
53. c6 e2 54. c7 Qxc7 55. Rxc7 e1=Q+ 56. Rc1 Qe4+ 57. Ka1 Qd4+
58. Kb1 Qe4+ 59. Ka1 Qd4+ 60. Kb1 Qe4+');

INSERT INTO CG_games
(CG_Date, CG_Result, WhiteELO, BlackELO, PlayerWhite, PlayerBlack, AlgebraicNotation)
VALUES('10-28-2014', 0.5, 2792, 2632, 1, 2,'1.Nf3 d5 2.d4 Nf6 3.c4 c6 4.Nc3 e6 5.Bg5 h6 6.Bh4 dxc4 7.e4 g5
8.Bg3 b5 9.Be2 Bb7 10.h4 g4 11.Ne5 h5 12.O-O Nbd7 13.Qc2 Nxe5
14.Bxe5 Bg7 15.Bg3 Qxd4 16.Rfd1 Qc5 17.Bd6 Qb6 18.a4 a6 19.e5
Nd7 20.a5 Qa7 21.Ne4 c5 22.Ng5 Nxe5 23.Bxe5 Bxe5 24.Bxc4 bxc4
25.Qa4+ Kf8 26.Rd7 Bd5 27.Rd1 Bd4 28.Rxa7 Rxa7 29.b3 Kg7
30.bxc4 Ba8 31.Qc2 g3 32.Rxd4 cxd4 33.Qe2 gxf2+ 34.Qxf2 Rd8
35.Qg3 Kf8 36.Qe5 Ke8 37.Nxe6 fxe6 38.Qh8+ Ke7 39.Qg7+ Ke8
40.Qh8+ Ke7 41.Qg7+');

INSERT INTO CG_games
(CG_Date, CG_Result, WhiteELO, BlackELO, PlayerWhite, PlayerBlack, AlgebraicNotation)
VALUES('10-28-2014', 1, 2789, 2635, 1, 2, '1.d4 d5 2.c4 c6 3.Nf3 Nf6 4.Nc3 e6 5.Bg5 h6 6.Bh4 dxc4 7.e4 g5
8.Bg3 b5 9.Be2 Bb7 10.O-O Nbd7 11.Ne5 Bg7 12.Nxf7 Kxf7 13.e5
Nd5 14.Ne4 Ke7 15.Nd6 Qb6 16.Bg4 Raf8 17.Qc2 Qxd4 18.Qg6 Qxg4
19.Qxg7+ Kd8 20.Nxb7+ Kc8 21.a4 b4 22.Rac1 c3 23.bxc3 b3 24.c4
Rfg8 25.Nd6+ Kc7 26.Qf7 Rf8 27.cxd5 Rxf7 28.Rxc6+ Kb8 29.Nxf7
Re8 30.Nd6 Rh8 31.Rc4 Qe2 32.dxe6 Nb6 33.Rb4 Ka8 34.e7 Nd5
35.Rxb3 Nxe7 36.Rfb1 Nd5 37.h3 h5 38.Nf7 Rc8 39.e6 a6 40.Nxg5
h4 41.Bd6 Rg8 42.R3b2 Qd3 43.e7 Nf6 44.Be5 Nd7 45.Ne6');

INSERT INTO CG_games
(CG_Date, CG_Result, WhiteELO, BlackELO, PlayerWhite, PlayerBlack, AlgebraicNotation)
VALUES('10-31-2014', 1, 2700, 2648, 3, 10, '1.d4 Nf6 2.c4 e6 3.Nf3 b6 4.g3 Ba6 5.b3 Bb4+ 6.Bd2 Be7 7.Bg2
c6 8.Bc3 d5 9.Ne5 Nfd7 10.Nxd7 Nxd7 11.Nd2 O-O 12.O-O Nf6
13.e4 b5 14.exd5 exd5 15.Re1 Rb8 16.c5 Bc8 17.Nf3 Ne4 18.Rxe4
dxe4 19.Ne5 Qd5 20.Qe1 Bf5 21.g4 Bg6 22.f3 b4 23.fxe4 Qe6
24.Bb2 Bf6 25.Nxc6 Qxc6 26.e5 Qa6 27.exf6 Rfe8 28.Qf1 Qe2
29.Qf2 Qxg4 30.h3 Qg5 31.Bc1 Qh5 32.Bf4 Rbd8 33.c6 Be4 34.c7
Rc8 35.Re1 Qg6 36.Rxe4 Rxe4 37.d5 Rce8 38.d6 Re1+ 39.Kh2 Qf5
40.Qg3 g6 41.Qg5 Qxg5 42.Bxg5 Rd1 43.Bc6 Re2+ 44.Kg3');

INSERT INTO CG_games
(CG_Date, CG_Result, WhiteELO, BlackELO, PlayerWhite, PlayerBlack, AlgebraicNotation)
VALUES('10-31-2014', 1, 2400, 2335, 4, 9, '1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. Nf3 Bc5 5. e3 Nc6 6. a3 a5
7. b3 O-O 8. Bb2 Re8 9. Nc3 d6 10. e6 Rxe6 11. Be2 Nxf2
12. Kxf2 Rxe3 13. Kf1 Qf6 14. b4 Ba7 15. b5 Bf5 16. bxc6 Rae8
17. Qd2 Rxf3+ 18. Bxf3 Bh3 19. Qd5 Qh4 20. c5 Bxc5 21. Qxc5
dxc5 22. cxb7 Bf5 23. Rd1 h5 24. g3 Qf6 25. Kg2 Bh3+ 26. Kxh3
Qxf3 27. Rhe1 Rb8 28. Ne4 f6 29. Rd2 Qf5+ 30. Kg2 Rxb7
31. Bxf6 gxf6 32. Rf2 Qd5 33. Kg1 Rb6 34. Nxf6+ Rxf6 35. Rxf6
c4 36. Rf2 h4 37. gxh4 Qc5 38. Kg2 c3 39. Rc2 a4 40. Rd1 Qc6+
41. Kg1 Kh8 42. Rdc1 Qc5+ 43. Kh1 Qd5+ 44. Kg1 Qd4+ 45. Kh1
Qe4+ 46. Kg1 Qe3+ 47. Kg2 Qe4+ 48. Kg1 Qd4+ 49. Kh1 Qd5+');

INSERT INTO CG_games
(CG_Date, CG_Result, WhiteELO, BlackELO, PlayerWhite, PlayerBlack, AlgebraicNotation)
VALUES('01-25-2015', 0, 2585, 2735, 5, 6,'1.d4 Nf6 2.c4 g6 3.Nc3 Bg7 4.e4 d6 5.Nf3 O-O 6.Be2 e5 7.d5 a5
8.Bg5 h6 9.Bh4 Na6 10.O-O Bd7 11.Nd2 Nc5 12.b3 Nfxe4 13.Bxd8
Nxc3 14.Qe1 Rfxd8 15.Rc1 Nxa2 16.Ra1 Nb4 17.Bd1 e4 18.Rb1 Re8
19.Qe3 f5 20.h4 Rf8 21.g3 Rae8 22.Kg2 Nbd3 23.Rg1 f4 24.gxf4
Rxf4 25.h5 g5 26.Rf1 Rh4 27.Rh1 Rf4 28.Rf1 Ref8 29.f3 Rh4
30.fxe4 Nf4+ 31.Kg1 Ncd3 32.e5 Nxe5 33.Rc1 Rh3 34.Nf3 g4
35.Nxe5 Rxe3 36.Nxd7 Nh3+ 37.Kg2 Rxf1 38.Kxf1 g3 39.Kg2 Nf4+');

INSERT INTO CG_games
(CG_Date, CG_Result, WhiteELO, BlackELO, PlayerWhite, PlayerBlack, AlgebraicNotation)
VALUES('03-14-2015', 1, 2785, 2635, 7, 8, '1.e4 e5 2.Nf3 d6 3.d4 Bg4 {This is a weak move
already.--Fischer} 4.dxe5 Bxf3 5.Qxf3 dxe5 6.Bc4 Nf6 7.Qb3 Qe7
8.Nc3 c6 9.Bg5 b5 10.Nxb5 cxb5 11.Bxb5+ Nbd7 12.O-O-O Rd8
13.Rxd7 Rxd7 14.Rd1 Qe6 15.Bxd7+ Nxd7 16.Qb8+ Nxb8 17.Rd8#');

INSERT INTO CG_games
(CG_Date, CG_Result, WhiteELO, BlackELO, PlayerWhite, PlayerBlack, AlgebraicNotation)
VALUES('10-28-2014', 0, 2285, 2535, 7, 2,'1. b3 e5 2. Bb2 Nc6 3. e3 Nf6 4. Bb5 Bd6 5. Na3 a6 6. Bxc6
dxc6 7. Nc4 Qe7 8. Ne2 b5 9. Nxd6+ cxd6 10. a4 b4 11. O-O O-O
12. Ng3 Nd5 13. f4 f6 14. a5 c5 15. fxe5 fxe5 16. Rxf8+ Qxf8
17. Qe2 Qe7 18. Qd3 Bb7 19. Rf1 Qd7 20. Qc4 Kh8 21. Qh4 Qe6
22. Qe4 Bc6 23. Qf5 Qe7 24. Ne4 Rd8 25. h4 Kg8 26. h5 Bd7
27. Qf3 Bb5 28. d3 h6 29. Ng3 Qe6 30. Nf5 Ne7 31. Nh4 Bd7
32. Bc1 Re8 33. e4 Kh7 34. Nf5 Nxf5 35. exf5 Qf6 36. Qb7 Bb5
37. Qe4 d5 38. Qxd5 e4 39. Bf4 exd3 40. cxd3 Re2 41. Qf3 Qd4+
42. Kh2 Qxd3 43. Qg4 Rxg2+ 44. Qxg2 Qxf1 45. Qg6+ Kh8 46. Bxh6
Qf2+ 47. Kh1 Qe1+ 48. Kh2 Qe5+ 49. Kh1 gxh6 50. Qxh6+ Kg8
51. Qg6+ Qg7 52. Qe6+ Qf7 53. Qc8+ Qf8 54. Qe6+ Qf7 55. Qc8+
Qe8 56. Qxc5 Qc6+');

INSERT INTO CG_games
(CG_Date, CG_Result, WhiteELO, BlackELO, PlayerWhite, PlayerBlack, AlgebraicNotation)
VALUES('10-28-2014', 0, 2685, 2605, 8, 6,'1. Nf3 d6 2. d4 Nf6 3. Nbd2 g6 4. e4 Bg7 5. Bd3 O-O 6. O-O Nc6
7. c3 e5 8. h3 Nh5 9. dxe5 Nf4 10. Bb5 Nxe5 11. Nxe5 Qg5
12. Ng4 Qxb5 13. Nb3 Ne2+ 14. Kh1 Bxg4 15. hxg4 Rae8 16. Be3
Rxe4 17. Re1 Qh5+');

INSERT INTO CG_user_role (CG_Role) VALUES('Standard');
INSERT INTO CG_user_role (CG_Role) VALUES('Premium');
INSERT INTO CG_user_role (CG_Role) VALUES('Admin');
INSERT INTO CG_user_role (CG_Role) VALUES('Moderator');

INSERT INTO CG_user_UserRole (UserID, RoleID) VALUES(1, 2);
INSERT INTO CG_user_UserRole (UserID, RoleID) VALUES(2, 2);
INSERT INTO CG_user_UserRole (UserID, RoleID) VALUES(3, 2);
INSERT INTO CG_user_UserRole (UserID, RoleID) VALUES(4, 1);
INSERT INTO CG_user_UserRole (UserID, RoleID) VALUES(5, 3);
INSERT INTO CG_user_UserRole (UserID, RoleID) VALUES(6, 3);
INSERT INTO CG_user_UserRole (UserID, RoleID) VALUES(7, 2);
INSERT INTO CG_user_UserRole (UserID, RoleID) VALUES(8, 2);
INSERT INTO CG_user_UserRole (UserID, RoleID) VALUES(9, 2);
INSERT INTO CG_user_UserRole (UserID, RoleID) VALUES(10, 2);

