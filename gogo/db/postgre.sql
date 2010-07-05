DROP SEQUENCE IF EXISTS seq_account_aid;

CREATE SEQUENCE seq_account_aid
  INCREMENT 1
  MINVALUE 1
  MAXVALUE 9223372036854775807
  START 1
  CACHE 1;

DROP SEQUENCE IF EXISTS seq_character_id;

CREATE SEQUENCE seq_character_id
  INCREMENT 1
  MINVALUE 1
  MAXVALUE 9223372036854775807
  START 1
  CACHE 1;

DROP SEQUENCE IF EXISTS seq_character_inventory_id;

CREATE SEQUENCE seq_character_inventory_id
  INCREMENT 1
  MINVALUE 1
  MAXVALUE 9223372036854775807
  START 1
  CACHE 1;

DROP SEQUENCE IF EXISTS seq_clan_id;

CREATE SEQUENCE seq_clan_id
  INCREMENT 1
  MINVALUE 1
  MAXVALUE 9223372036854775807
  START 1
  CACHE 1;

DROP TABLE IF EXISTS account;

CREATE TABLE account
(
  aid integer NOT NULL DEFAULT nextval(('public."seq_account_aid"'::text)::regclass),
  username character varying(128) NOT NULL,
  "password" character varying(128) NOT NULL,
  ugradeid smallint NOT NULL DEFAULT 0,
  pgradeid smallint NOT NULL DEFAULT 0,
  "name" character varying(128) NOT NULL,
  email character varying(128) NOT NULL,
  CONSTRAINT account_pkey PRIMARY KEY (aid),
  CONSTRAINT account_email_key UNIQUE (email),
  CONSTRAINT account_username_key UNIQUE (username),
  CONSTRAINT account_email_check CHECK (email::text ~~ '%@%.%'::text),
  CONSTRAINT account_name_check CHECK (name::text ~~ '% %'::text)
);

DROP TABLE IF EXISTS account_inventory;

CREATE TABLE account_inventory
(
  itemid integer NOT NULL,
  aid integer NOT NULL,
  id integer NOT NULL,
  expireson timestamp without time zone,
  CONSTRAINT account_inventory_pkey PRIMARY KEY (id),
  CONSTRAINT account_inventory_aid_fkey FOREIGN KEY (aid)
      REFERENCES account (aid) MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE
);

DROP TABLE IF EXISTS "character";

CREATE TABLE "character"
(
  id integer NOT NULL DEFAULT nextval(('public."seq_character_id"'::text)::regclass),
  accountid integer NOT NULL DEFAULT 0,
  "name" character varying(32) NOT NULL DEFAULT 0,
  clanid smallint NOT NULL DEFAULT 0,
  "level" smallint NOT NULL DEFAULT 1,
  sex smallint NOT NULL DEFAULT 0,
  hair smallint NOT NULL DEFAULT 0,
  face smallint NOT NULL DEFAULT 0,
  costume smallint NOT NULL DEFAULT 0,
  xp smallint NOT NULL DEFAULT 0,
  bp smallint NOT NULL DEFAULT 0,
  marker smallint NOT NULL DEFAULT 0,
  CONSTRAINT character_pkey PRIMARY KEY (id),
  CONSTRAINT character_accountid_fkey FOREIGN KEY (accountid)
      REFERENCES account (aid) MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE
);

DROP TABLE IF EXISTS character_equip;

CREATE TABLE character_equip
(
  charid integer NOT NULL,
  head_slot integer NOT NULL DEFAULT 0,
  chest_slot integer NOT NULL DEFAULT 0,
  hands_slot integer NOT NULL DEFAULT 0,
  legs_slot integer NOT NULL DEFAULT 0,
  feet_slot integer NOT NULL DEFAULT 0,
  finger1_slot integer NOT NULL DEFAULT 0,
  fingerr_slot integer NOT NULL DEFAULT 0,
  melee_slot integer NOT NULL DEFAULT 0,
  primary_slot integer NOT NULL DEFAULT 0,
  secondary_slot integer NOT NULL DEFAULT 0,
  custom1_slot integer NOT NULL DEFAULT 0,
  custom2_slot integer NOT NULL DEFAULT 0,
  CONSTRAINT character_equip_pkey PRIMARY KEY (charid),
  CONSTRAINT character_equip_charid_fkey FOREIGN KEY (charid)
      REFERENCES "character" (id) MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE
);

DROP TABLE IF EXISTS character_inventory;

CREATE TABLE character_inventory
(
  id integer NOT NULL DEFAULT nextval(('public."seq_character_inventory_id"'::text)::regclass),
  charid integer NOT NULL DEFAULT 0,
  itemid integer NOT NULL DEFAULT 0,
  expireson timestamp without time zone,
  CONSTRAINT character_inventory_pkey PRIMARY KEY (id),
  CONSTRAINT character_inventory_charid_fkey FOREIGN KEY (charid)
      REFERENCES "character" (id) MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE
);

DROP TABLE IF EXISTS clan;

CREATE TABLE clan
(
  id smallint NOT NULL DEFAULT nextval(('public."seq_clan_id"'::text)::regclass),
  "name" character varying(16) NOT NULL,
  cwpoints integer NOT NULL DEFAULT 1000,
  CONSTRAINT clan_pkey PRIMARY KEY (id)
);

DROP TABLE IF EXISTS clan_members;

CREATE TABLE clan_members
(
  clanid smallint NOT NULL DEFAULT 0,
  charid integer NOT NULL DEFAULT 0,
  clangrade smallint NOT NULL DEFAULT 0,
  CONSTRAINT clan_members_pkey PRIMARY KEY (clanid, charid),
  CONSTRAINT clan_members_charid_fkey FOREIGN KEY (charid)
      REFERENCES "character" (id) MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE,
  CONSTRAINT clan_members_clanid_fkey FOREIGN KEY (clanid)
      REFERENCES clan (id) MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE
);