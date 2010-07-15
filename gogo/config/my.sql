/*
GoGo Database
Last Updated: 2010-07-14 13:26:00
*/

SET FOREIGN_KEY_CHECKS=1;
-- ----------------------------
-- Table structure for `account`
-- ----------------------------
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account` (
  `aid` int(11) unsigned AUTO_INCREMENT,
  `username` varchar(128) NOT NULL UNIQUE,
  `password` varchar(128) NOT NULL,
  `ugradeid` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `pgradeid` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `name` varchar(128) NOT NULL,
  `email` varchar(128) NOT NULL UNIQUE,
  PRIMARY KEY (`aid`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `account_inventory`
-- ----------------------------
DROP TABLE IF EXISTS `account_inventory`;
CREATE TABLE `account_inventory` (
  `id` int(11) unsigned AUTO_INCREMENT,
  `itemid` int(11) unsigned NOT NULL,
  `aid` int(11) unsigned NOT NULL,
  `expireson` datetime,
  PRIMARY KEY (`id`),
  CONSTRAINT `accountinv` FOREIGN KEY (`aid`) REFERENCES `account` (`aid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `character`
-- ----------------------------
DROP TABLE IF EXISTS `character`;
CREATE TABLE `character` (
  `id` int(11) unsigned AUTO_INCREMENT,
  `accountid` int(11) unsigned NOT NULL DEFAULT '0',
  `name` varchar(32) NOT NULL,
  `clanid` smallint(5) unsigned NOT NULL DEFAULT '0',
  `level` tinyint(3) NOT NULL DEFAULT '1',
  `sex` tinyint(1) NOT NULL DEFAULT '0',
  `hair` tinyint(1) NOT NULL DEFAULT '0',
  `face` tinyint(1) NOT NULL DEFAULT '0',
  `costume` tinyint(1) NOT NULL DEFAULT '0',
  `xp` int(11) NOT NULL DEFAULT '0',
  `bp` int(11) NOT NULL DEFAULT '0',
  `marker` tinyint(1) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `clanstuff` (`clanid`),
  KEY `AccountID` (`accountid`),
  CONSTRAINT `AccountID` FOREIGN KEY (`accountid`) REFERENCES `account` (`aid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `character_equip`
-- ----------------------------
DROP TABLE IF EXISTS `character_equip`;
CREATE TABLE `character_equip` (
  `charid` int(11) unsigned DEFAULT '0',
  `head_slot` int(11) unsigned NOT NULL DEFAULT '0',
  `chest_slot` int(11) unsigned NOT NULL DEFAULT '0',
  `hands_slot` int(11) unsigned NOT NULL DEFAULT '0',
  `legs_slot` int(11) unsigned NOT NULL DEFAULT '0',
  `feet_slot` int(11) unsigned NOT NULL DEFAULT '0',
  `fingerl_slot` int(11) unsigned NOT NULL DEFAULT '0',
  `fingerr_slot` int(11) unsigned NOT NULL DEFAULT '0',
  `melee_slot` int(11) unsigned NOT NULL DEFAULT '0',
  `primary_slot` int(11) unsigned NOT NULL DEFAULT '0',
  `secondary_slot` int(11) unsigned NOT NULL DEFAULT '0',
  `custom1_slot` int(11) unsigned NOT NULL DEFAULT '0',
  `custom2_slot` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`charid`),
  CONSTRAINT `equipk` FOREIGN KEY (`charid`) REFERENCES `character` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `character_inventory`
-- ----------------------------
DROP TABLE IF EXISTS `character_inventory`;
CREATE TABLE `character_inventory` (
  `id` int(11) unsigned,
  `charid` int(11) unsigned NOT NULL,
  `itemid` int(11) unsigned NOT NULL,
  `rental` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `expireson` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  CONSTRAINT `CharInv` FOREIGN KEY (`charid`) REFERENCES `character` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `clan`
-- ----------------------------
DROP TABLE IF EXISTS `clan`;
CREATE TABLE `clan` (
  `id` smallint(5) unsigned AUTO_INCREMENT,
  `name` varchar(16) NOT NULL UNIQUE,
  `cwpoints` int(11) NOT NULL DEFAULT '1000',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `clan_members`
-- ----------------------------
DROP TABLE IF EXISTS `clan_members`;
CREATE TABLE `clan_members` (
  `clanid` smallint(5) unsigned,
  `charid` int(11) unsigned,
  `clangrade` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`clanid`,`charid`),
  CONSTRAINT `CharID` FOREIGN KEY (`charid`) REFERENCES `character` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `ClanID` FOREIGN KEY (`clanid`) REFERENCES `clan` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
