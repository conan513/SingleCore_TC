/*
Navicat MariaDB Data Transfer

Source Server         : BFA
Source Server Version : 100136
Source Host           : localhost:3310
Source Database       : ashamane_world

Target Server Type    : MariaDB
Target Server Version : 100136
File Encoding         : 65001

Date: 2019-08-10 15:12:12
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for updates_include
-- ----------------------------
DROP TABLE IF EXISTS `updates_include`;
CREATE TABLE `updates_include` (
  `path` varchar(200) NOT NULL COMMENT 'directory to include. $ means relative to the source directory.',
  `state` enum('RELEASED','ARCHIVED') NOT NULL DEFAULT 'RELEASED' COMMENT 'defines if the directory contains released or archived updates.',
  PRIMARY KEY (`path`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='List of directories where we want to include sql updates.';

-- ----------------------------
-- Records of updates_include
-- ----------------------------
INSERT INTO `updates_include` VALUES ('$/sql/ashamane/old/world', 'ARCHIVED');
INSERT INTO `updates_include` VALUES ('$/sql/ashamane/world', 'RELEASED');
INSERT INTO `updates_include` VALUES ('$/sql/custom/world', 'RELEASED');
SET FOREIGN_KEY_CHECKS=1;
