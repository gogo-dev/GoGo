/*
Target Server Type    : MYSQL
Target Server Version : 50141
File Encoding         : 65001
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `account`
-- ----------------------------
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account` (
  `aid` int(11) NOT NULL DEFAULT '0',
  `username` varchar(128) NOT NULL,
  `password` varchar(128) NOT NULL,
  `ugradeid` tinyint(3) NOT NULL DEFAULT '0',
  `pgradeid` tinyint(3) NOT NULL DEFAULT '0',
  `name` varchar(128) NOT NULL,
  `email` varchar(128) NOT NULL,
  PRIMARY KEY (`aid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `account_inventory`
-- ----------------------------
DROP TABLE IF EXISTS `account_inventory`;
CREATE TABLE `account_inventory` (
  `itemid` int(11) NOT NULL,
  `aid` int(11) NOT NULL,
  `expireson` datetime NOT NULL,
  KEY `accountinv` (`aid`),
  CONSTRAINT `accountinv` FOREIGN KEY (`aid`) REFERENCES `account` (`aid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `character`
-- ----------------------------
DROP TABLE IF EXISTS `character`;
CREATE TABLE `character` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `accountid` int(11) NOT NULL DEFAULT '0',
  `name` varchar(32) DEFAULT '',
  `clanid` smallint(5) NOT NULL DEFAULT '0',
  `level` tinyint(3) NOT NULL DEFAULT '0',
  `sex` tinyint(1) NOT NULL DEFAULT '0',
  `hair` tinyint(1) NOT NULL DEFAULT '0',
  `face` tinyint(1) NOT NULL DEFAULT '0',
  `xp` int(11) NOT NULL DEFAULT '0',
  `bp` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `clanstuff` (`clanid`),
  KEY `AccountID` (`accountid`),
  CONSTRAINT `AccountID` FOREIGN KEY (`accountid`) REFERENCES `account` (`aid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `character_inventory`
-- ----------------------------
DROP TABLE IF EXISTS `character_inventory`;
CREATE TABLE `character_inventory` (
  `itemid` int(11) NOT NULL DEFAULT '0',
  `charid` int(11) NOT NULL DEFAULT '0',
  `expireson` datetime NOT NULL,
  KEY `CharInv` (`charid`),
  CONSTRAINT `CharInv` FOREIGN KEY (`charid`) REFERENCES `character` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `clan`
-- ----------------------------
DROP TABLE IF EXISTS `clan`;
CREATE TABLE `clan` (
  `id` smallint(5) NOT NULL AUTO_INCREMENT,
  `name` varchar(16) DEFAULT '',
  `cwpoints` int(11) NOT NULL DEFAULT '1000',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `clan_members`
-- ----------------------------
DROP TABLE IF EXISTS `clan_members`;
CREATE TABLE `clan_members` (
  `clanid` smallint(5) NOT NULL DEFAULT '0',
  `charid` int(11) NOT NULL DEFAULT '0',
  `clangrade` tinyint(3) NOT NULL DEFAULT '0',
  KEY `CharID` (`charid`),
  KEY `ClanID` (`clanid`),
  CONSTRAINT `CharID` FOREIGN KEY (`charid`) REFERENCES `character` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `ClanID` FOREIGN KEY (`clanid`) REFERENCES `clan` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
