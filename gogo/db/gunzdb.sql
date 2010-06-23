/*
Navicat MySQL Data Transfer

Source Server         : local
Source Server Version : 50146
Source Host           : localhost:3306
Source Database       : gunzdb

Target Server Type    : MYSQL
Target Server Version : 50146
File Encoding         : 65001

Date: 2010-06-23 17:17:24
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `account`
-- ----------------------------
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account` (
  `aid` int(11) unsigned NOT NULL DEFAULT '0',
  `username` varchar(128) NOT NULL,
  `password` varchar(128) NOT NULL,
  `ugradeid` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `pgradeid` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `name` varchar(128) NOT NULL,
  `email` varchar(128) NOT NULL,
  PRIMARY KEY (`aid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of account
-- ----------------------------
INSERT INTO `account` VALUES ('1', 'theoretical', '7815696ecbf1c96e6894b779456d330e', '255', '0', 'jacob', 'asd@lol.com');

-- ----------------------------
-- Table structure for `account_inventory`
-- ----------------------------
DROP TABLE IF EXISTS `account_inventory`;
CREATE TABLE `account_inventory` (
  `itemid` int(11) unsigned NOT NULL,
  `aid` int(11) unsigned NOT NULL,
  `expireson` datetime NOT NULL,
  PRIMARY KEY (`itemid`),
  KEY `accountinv` (`aid`),
  CONSTRAINT `accountinv` FOREIGN KEY (`aid`) REFERENCES `account` (`aid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of account_inventory
-- ----------------------------

-- ----------------------------
-- Table structure for `character`
-- ----------------------------
DROP TABLE IF EXISTS `character`;
CREATE TABLE `character` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `accountid` int(11) unsigned NOT NULL DEFAULT '0',
  `name` varchar(32) DEFAULT '',
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
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of character
-- ----------------------------
INSERT INTO `character` VALUES ('6', '1', 'Phabnz', '0', '1', '1', '0', '0', '0', '0', '0', '0');
INSERT INTO `character` VALUES ('7', '1', 'OMGMALE', '0', '1', '0', '0', '0', '0', '0', '0', '1');

-- ----------------------------
-- Table structure for `character_equip`
-- ----------------------------
DROP TABLE IF EXISTS `character_equip`;
CREATE TABLE `character_equip` (
  `charid` int(11) unsigned NOT NULL DEFAULT '0',
  `head_slot` int(11) unsigned NOT NULL DEFAULT '0',
  `chest_slot` int(11) unsigned NOT NULL DEFAULT '0',
  `hands_slot` int(11) unsigned NOT NULL DEFAULT '0',
  `legs_slot` int(11) unsigned NOT NULL DEFAULT '0',
  `Feet_slot` int(11) unsigned NOT NULL DEFAULT '0',
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
-- Records of character_equip
-- ----------------------------
INSERT INTO `character_equip` VALUES ('6', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0');
INSERT INTO `character_equip` VALUES ('7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0');

-- ----------------------------
-- Table structure for `character_inventory`
-- ----------------------------
DROP TABLE IF EXISTS `character_inventory`;
CREATE TABLE `character_inventory` (
  `id` int(11) unsigned NOT NULL DEFAULT '0',
  `charid` int(11) unsigned NOT NULL DEFAULT '0',
  `itemid` int(11) unsigned NOT NULL DEFAULT '0',
  `rental` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `expireson` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `charid` (`charid`),
  CONSTRAINT `CharInv` FOREIGN KEY (`charid`) REFERENCES `character` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of character_inventory
-- ----------------------------

-- ----------------------------
-- Table structure for `clan`
-- ----------------------------
DROP TABLE IF EXISTS `clan`;
CREATE TABLE `clan` (
  `id` smallint(5) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(16) DEFAULT '',
  `cwpoints` int(11) NOT NULL DEFAULT '1000',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of clan
-- ----------------------------

-- ----------------------------
-- Table structure for `clan_members`
-- ----------------------------
DROP TABLE IF EXISTS `clan_members`;
CREATE TABLE `clan_members` (
  `clanid` smallint(5) unsigned NOT NULL DEFAULT '0',
  `charid` int(11) unsigned NOT NULL DEFAULT '0',
  `clangrade` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`clanid`,`charid`),
  KEY `CharID` (`charid`),
  CONSTRAINT `CharID` FOREIGN KEY (`charid`) REFERENCES `character` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `ClanID` FOREIGN KEY (`clanid`) REFERENCES `clan` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of clan_members
-- ----------------------------
