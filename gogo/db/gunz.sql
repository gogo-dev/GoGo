SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `account`
-- ----------------------------
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account` (
  `aid` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `username` varchar(128) NOT NULL,
  `password` varchar(128) NOT NULL,
  `ugradeid` tinyint(3) UNSIGNED NOT NULL DEFAULT '0',
  `pgradeid` tinyint(3) UNSIGNED NOT NULL DEFAULT '0',
  `name` varchar(128) NOT NULL,
  `email` varchar(128) NOT NULL,
  PRIMARY KEY (`aid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `account_inventory`
-- ----------------------------
DROP TABLE IF EXISTS `account_inventory`;
CREATE TABLE `account_inventory` (
  `itemid` int(11) UNSIGNED NOT NULL,
  `aid` int(11) UNSIGNED NOT NULL,
  `expireson` datetime NOT NULL,
  PRIMARY KEY (`itemid`),
  KEY `accountinv` (`aid`),
  CONSTRAINT `accountinv` FOREIGN KEY (`aid`) REFERENCES `account` (`aid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


-- ----------------------------
-- Table structure for `character`
-- ----------------------------
DROP TABLE IF EXISTS `character`;
CREATE TABLE `character` (
  `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  `accountid` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `name` varchar(32) DEFAULT '',
  `clanid` smallint(5) UNSIGNED NOT NULL DEFAULT '0',
  `level` tinyint(3) NOT NULL DEFAULT '0',
  `sex` tinyint(1) NOT NULL DEFAULT '0',
  `hair` tinyint(1) NOT NULL DEFAULT '0',
  `face` tinyint(1) NOT NULL DEFAULT '0',
  `xp` int(11) NOT NULL DEFAULT '0',
  `bp` int(11) NOT NULL DEFAULT '0',
  `marker` tinyint(1) UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `clanstuff` (`clanid`),
  KEY `AccountID` (`accountid`),
  CONSTRAINT `AccountID` FOREIGN KEY (`accountid`) REFERENCES `account` (`aid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `character_equip`
-- ----------------------------
DROP TABLE IF EXISTS `character_equip`;
CREATE TABLE `character_equip` (
  `charid` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `head_slot` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `chest_slot` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `hands_slot` int(11) UNSIGNED NOT NULL,
  `legs_slot` int(11) UNSIGNED NOT NULL,
  `Feet_slot` int(11) UNSIGNED NOT NULL,
  `fingerl_slot` int(11) UNSIGNED NOT NULL,
  `fingerr_slot` int(11) UNSIGNED NOT NULL,
  `melee_slot` int(11) UNSIGNED NOT NULL,
  `primary_slot` int(11) UNSIGNED NOT NULL,
  `secondary_slot` int(11) UNSIGNED NOT NULL,
  `custom1_slot` int(11) UNSIGNED NOT NULL,
  `custom2_slot` int(11) UNSIGNED NOT NULL,
  PRIMARY KEY (`charid`),
  CONSTRAINT `equipk` FOREIGN KEY (`charid`) REFERENCES `character` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `character_inventory`
-- ----------------------------
DROP TABLE IF EXISTS `character_inventory`;
CREATE TABLE `character_inventory` (
  `id` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `charid` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `itemid` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `rental` tinyint(3) UNSIGNED NOT NULL DEFAULT '0', 
  `expireson` datetime NULL,
  PRIMARY KEY (`id`),
  KEY (`charid`),
  CONSTRAINT `CharInv` FOREIGN KEY (`charid`) REFERENCES `character` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=2 CHARSET=utf8;

-- ----------------------------
-- Table structure for `clan`
-- ----------------------------
DROP TABLE IF EXISTS `clan`;
CREATE TABLE `clan` (
  `id` smallint(5) UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` varchar(16) DEFAULT '',
  `cwpoints` int(11) NOT NULL DEFAULT '1000',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;


-- ----------------------------
-- Table structure for `clan_members`
-- ----------------------------
DROP TABLE IF EXISTS `clan_members`;
CREATE TABLE `clan_members` (
  `clanid` smallint(5) UNSIGNED NOT NULL DEFAULT '0',
  `charid` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `clangrade` tinyint(3) UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`clanid`,`charid`),
  KEY `CharID` (`charid`),
  CONSTRAINT `CharID` FOREIGN KEY (`charid`) REFERENCES `character` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `ClanID` FOREIGN KEY (`clanid`) REFERENCES `clan` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

