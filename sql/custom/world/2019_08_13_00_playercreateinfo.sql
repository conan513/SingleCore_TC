/*
Navicat MariaDB Data Transfer

Source Server         : spp-forum.de
Source Server Version : 100315
Source Host           : 164.68.103.31:3306
Source Database       : trinity_world

Target Server Type    : MariaDB
Target Server Version : 100315
File Encoding         : 65001

Date: 2019-08-13 09:45:07
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for playercreateinfo
-- ----------------------------
DROP TABLE IF EXISTS `playercreateinfo`;
CREATE TABLE `playercreateinfo` (
  `race` tinyint(3) unsigned NOT NULL DEFAULT 0,
  `class` tinyint(3) unsigned NOT NULL DEFAULT 0,
  `map` smallint(5) unsigned NOT NULL DEFAULT 0,
  `zone` mediumint(8) unsigned NOT NULL DEFAULT 0,
  `position_x` float NOT NULL DEFAULT 0,
  `position_y` float NOT NULL DEFAULT 0,
  `position_z` float NOT NULL DEFAULT 0,
  `orientation` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`race`,`class`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of playercreateinfo
-- ----------------------------
INSERT INTO `playercreateinfo` VALUES ('1', '9', '0', '9', '-8914.57', '-133.909', '80.5378', '5.13806');
INSERT INTO `playercreateinfo` VALUES ('1', '8', '0', '9', '-8914.57', '-133.909', '80.5378', '5.13806');
INSERT INTO `playercreateinfo` VALUES ('1', '5', '0', '9', '-8914.57', '-133.909', '80.5378', '5.13806');
INSERT INTO `playercreateinfo` VALUES ('1', '4', '0', '9', '-8914.57', '-133.909', '80.5378', '5.13806');
INSERT INTO `playercreateinfo` VALUES ('1', '2', '0', '9', '-8914.57', '-133.909', '80.5378', '5.13806');
INSERT INTO `playercreateinfo` VALUES ('1', '1', '0', '9', '-8914.57', '-133.909', '80.5378', '5.13806');
INSERT INTO `playercreateinfo` VALUES ('2', '1', '1', '14', '-618.518', '-4251.67', '38.718', '4.72222');
INSERT INTO `playercreateinfo` VALUES ('2', '3', '1', '14', '-618.518', '-4251.67', '38.718', '4.72222');
INSERT INTO `playercreateinfo` VALUES ('2', '4', '1', '14', '-618.518', '-4251.67', '38.718', '4.72222');
INSERT INTO `playercreateinfo` VALUES ('2', '7', '1', '14', '-618.518', '-4251.67', '38.718', '4.72222');
INSERT INTO `playercreateinfo` VALUES ('2', '9', '1', '14', '-618.518', '-4251.67', '38.718', '4.72222');
INSERT INTO `playercreateinfo` VALUES ('3', '1', '0', '1', '-6230.42', '330.232', '383.105', '6.17716');
INSERT INTO `playercreateinfo` VALUES ('3', '2', '0', '1', '-6230.42', '330.232', '383.105', '6.17716');
INSERT INTO `playercreateinfo` VALUES ('3', '3', '0', '1', '-6230.42', '330.232', '383.105', '6.17716');
INSERT INTO `playercreateinfo` VALUES ('3', '4', '0', '1', '-6230.42', '330.232', '383.105', '6.17716');
INSERT INTO `playercreateinfo` VALUES ('3', '5', '0', '1', '-6230.42', '330.232', '383.105', '6.17716');
INSERT INTO `playercreateinfo` VALUES ('4', '1', '1', '141', '10311.3', '831.463', '1326.57', '5.69632');
INSERT INTO `playercreateinfo` VALUES ('4', '3', '1', '141', '10311.3', '831.463', '1326.57', '5.69632');
INSERT INTO `playercreateinfo` VALUES ('4', '4', '1', '141', '10311.3', '831.463', '1326.57', '5.69632');
INSERT INTO `playercreateinfo` VALUES ('4', '5', '1', '141', '10311.3', '831.463', '1326.57', '5.69632');
INSERT INTO `playercreateinfo` VALUES ('4', '11', '1', '141', '10311.3', '831.463', '1326.57', '5.69632');
INSERT INTO `playercreateinfo` VALUES ('5', '9', '0', '5692', '1699.85', '1706.56', '135.928', '4.88839');
INSERT INTO `playercreateinfo` VALUES ('5', '8', '0', '5692', '1699.85', '1706.56', '135.928', '4.88839');
INSERT INTO `playercreateinfo` VALUES ('5', '5', '0', '5692', '1699.85', '1706.56', '135.928', '4.88839');
INSERT INTO `playercreateinfo` VALUES ('5', '3', '0', '5692', '1699.85', '1706.56', '135.928', '4.88839');
INSERT INTO `playercreateinfo` VALUES ('5', '1', '0', '5692', '1699.85', '1706.56', '135.928', '4.88839');
INSERT INTO `playercreateinfo` VALUES ('6', '7', '1', '221', '-2915.55', '-257.347', '59.2693', '0.302378');
INSERT INTO `playercreateinfo` VALUES ('6', '5', '1', '221', '-2915.55', '-257.347', '59.2693', '0.302378');
INSERT INTO `playercreateinfo` VALUES ('6', '2', '1', '221', '-2915.55', '-257.347', '59.2693', '0.302378');
INSERT INTO `playercreateinfo` VALUES ('6', '1', '1', '221', '-2915.55', '-257.347', '59.2693', '0.302378');
INSERT INTO `playercreateinfo` VALUES ('7', '9', '0', '5495', '-4983.42', '877.7', '274.31', '3.06393');
INSERT INTO `playercreateinfo` VALUES ('7', '1', '0', '5495', '-4983.42', '877.7', '274.31', '3.06393');
INSERT INTO `playercreateinfo` VALUES ('7', '4', '0', '5495', '-4983.42', '877.7', '274.31', '3.06393');
INSERT INTO `playercreateinfo` VALUES ('7', '8', '0', '5495', '-4983.42', '877.7', '274.31', '3.06393');
INSERT INTO `playercreateinfo` VALUES ('8', '9', '1', '5691', '-1171.45', '-5263.65', '0.847728', '5.78945');
INSERT INTO `playercreateinfo` VALUES ('8', '8', '1', '5691', '-1171.45', '-5263.65', '0.847728', '5.78945');
INSERT INTO `playercreateinfo` VALUES ('8', '7', '1', '5691', '-1171.45', '-5263.65', '0.847728', '5.78945');
INSERT INTO `playercreateinfo` VALUES ('8', '5', '1', '5691', '-1171.45', '-5263.65', '0.847728', '5.78945');
INSERT INTO `playercreateinfo` VALUES ('8', '3', '1', '5691', '-1171.45', '-5263.65', '0.847728', '5.78945');
INSERT INTO `playercreateinfo` VALUES ('8', '1', '1', '5691', '-1171.45', '-5263.65', '0.847728', '5.78945');
INSERT INTO `playercreateinfo` VALUES ('10', '2', '530', '3431', '10349.6', '-6357.29', '33.4026', '5.31605');
INSERT INTO `playercreateinfo` VALUES ('10', '3', '530', '3431', '10349.6', '-6357.29', '33.4026', '5.31605');
INSERT INTO `playercreateinfo` VALUES ('10', '4', '530', '3431', '10349.6', '-6357.29', '33.4026', '5.31605');
INSERT INTO `playercreateinfo` VALUES ('10', '5', '530', '3431', '10349.6', '-6357.29', '33.4026', '5.31605');
INSERT INTO `playercreateinfo` VALUES ('10', '8', '530', '3431', '10349.6', '-6357.29', '33.4026', '5.31605');
INSERT INTO `playercreateinfo` VALUES ('10', '9', '530', '3431', '10349.6', '-6357.29', '33.4026', '5.31605');
INSERT INTO `playercreateinfo` VALUES ('11', '1', '530', '3526', '-3961.64', '-13931.2', '100.615', '2.08364');
INSERT INTO `playercreateinfo` VALUES ('11', '2', '530', '3526', '-3961.64', '-13931.2', '100.615', '2.08364');
INSERT INTO `playercreateinfo` VALUES ('11', '3', '530', '3526', '-3961.64', '-13931.2', '100.615', '2.08364');
INSERT INTO `playercreateinfo` VALUES ('11', '5', '530', '3526', '-3961.64', '-13931.2', '100.615', '2.08364');
INSERT INTO `playercreateinfo` VALUES ('11', '7', '530', '3526', '-3961.64', '-13931.2', '100.615', '2.08364');
INSERT INTO `playercreateinfo` VALUES ('11', '8', '530', '3526', '-3961.64', '-13931.2', '100.615', '2.08364');
INSERT INTO `playercreateinfo` VALUES ('1', '3', '0', '9', '-8914.57', '-133.909', '80.5378', '5.13806');
INSERT INTO `playercreateinfo` VALUES ('11', '6', '609', '4298', '2358.17', '-5663.21', '426.027', '3.93485');
INSERT INTO `playercreateinfo` VALUES ('10', '6', '609', '4298', '2355.84', '-5664.77', '426.028', '3.93485');
INSERT INTO `playercreateinfo` VALUES ('9', '6', '609', '4298', '2355.05', '-5661.7', '426.026', '3.93485');
INSERT INTO `playercreateinfo` VALUES ('5', '4', '0', '5692', '1699.85', '1706.56', '135.928', '4.88839');
INSERT INTO `playercreateinfo` VALUES ('6', '3', '1', '221', '-2915.55', '-257.347', '59.2693', '0.302378');
INSERT INTO `playercreateinfo` VALUES ('7', '5', '0', '5495', '-4983.42', '877.7', '274.31', '3.06393');
INSERT INTO `playercreateinfo` VALUES ('8', '4', '1', '5691', '-1171.45', '-5263.65', '0.847728', '5.78945');
INSERT INTO `playercreateinfo` VALUES ('2', '6', '609', '4298', '2358.44', '-5666.9', '426.023', '3.93485');
INSERT INTO `playercreateinfo` VALUES ('3', '6', '609', '4298', '2358.44', '-5666.9', '426.023', '3.93485');
INSERT INTO `playercreateinfo` VALUES ('22', '1', '654', '4756', '-1451.53', '1403.35', '35.5561', '0.333847');
INSERT INTO `playercreateinfo` VALUES ('22', '3', '654', '4756', '-1451.53', '1403.35', '35.5561', '0.333847');
INSERT INTO `playercreateinfo` VALUES ('22', '4', '654', '4756', '-1451.53', '1403.35', '35.5561', '0.333847');
INSERT INTO `playercreateinfo` VALUES ('22', '5', '654', '4756', '-1451.53', '1403.35', '35.5561', '0.333847');
INSERT INTO `playercreateinfo` VALUES ('22', '8', '654', '4756', '-1451.53', '1403.35', '35.5561', '0.333847');
INSERT INTO `playercreateinfo` VALUES ('22', '9', '654', '4756', '-1451.53', '1403.35', '35.5561', '0.333847');
INSERT INTO `playercreateinfo` VALUES ('22', '11', '654', '4756', '-1451.53', '1403.35', '35.5561', '0.333847');
INSERT INTO `playercreateinfo` VALUES ('9', '1', '648', '4765', '-8423.81', '1361.3', '104.671', '1.55428');
INSERT INTO `playercreateinfo` VALUES ('9', '3', '648', '4765', '-8423.81', '1361.3', '104.671', '1.55428');
INSERT INTO `playercreateinfo` VALUES ('9', '4', '648', '4765', '-8423.81', '1361.3', '104.671', '1.55428');
INSERT INTO `playercreateinfo` VALUES ('9', '5', '648', '4765', '-8423.81', '1361.3', '104.671', '1.55428');
INSERT INTO `playercreateinfo` VALUES ('9', '7', '648', '4765', '-8423.81', '1361.3', '104.671', '1.55428');
INSERT INTO `playercreateinfo` VALUES ('9', '8', '648', '4765', '-8423.81', '1361.3', '104.671', '1.55428');
INSERT INTO `playercreateinfo` VALUES ('9', '9', '648', '4765', '-8423.81', '1361.3', '104.671', '1.55428');
INSERT INTO `playercreateinfo` VALUES ('8', '11', '1', '5691', '-1171.45', '-5263.65', '0.847728', '5.78945');
INSERT INTO `playercreateinfo` VALUES ('6', '11', '1', '221', '-2915.55', '-257.347', '59.2693', '0.302378');
INSERT INTO `playercreateinfo` VALUES ('22', '6', '609', '4298', '2356.21', '-5662.21', '426.026', '3.93485');
INSERT INTO `playercreateinfo` VALUES ('2', '8', '1', '14', '-618.518', '-4251.67', '38.718', '4.72222');
INSERT INTO `playercreateinfo` VALUES ('3', '7', '0', '1', '-6230.42', '330.232', '383.105', '6.17716');
INSERT INTO `playercreateinfo` VALUES ('3', '8', '0', '1', '-6230.42', '330.232', '383.105', '6.17716');
INSERT INTO `playercreateinfo` VALUES ('3', '9', '0', '1', '-6230.42', '330.232', '383.105', '6.17716');
INSERT INTO `playercreateinfo` VALUES ('4', '8', '1', '141', '10311.3', '831.463', '1326.57', '5.69632');
INSERT INTO `playercreateinfo` VALUES ('8', '6', '609', '4298', '2355.05', '-5661.7', '426.026', '3.93485');
INSERT INTO `playercreateinfo` VALUES ('7', '6', '609', '4298', '2355.05', '-5661.7', '426.026', '3.93485');
INSERT INTO `playercreateinfo` VALUES ('6', '6', '609', '4298', '2358.17', '-5663.21', '426.027', '3.93485');
INSERT INTO `playercreateinfo` VALUES ('5', '6', '609', '4298', '2356.21', '-5662.21', '426.026', '3.93485');
INSERT INTO `playercreateinfo` VALUES ('4', '6', '609', '4298', '2356.21', '-5662.21', '426.026', '3.93485');
INSERT INTO `playercreateinfo` VALUES ('10', '1', '530', '3431', '10349.6', '-6357.29', '33.4026', '5.31605');
INSERT INTO `playercreateinfo` VALUES ('1', '6', '609', '4298', '2355.84', '-5664.77', '426.028', '3.93485');
INSERT INTO `playercreateinfo` VALUES ('1', '10', '0', '9', '-8914.57', '-133.909', '80.5378', '5.13806');
INSERT INTO `playercreateinfo` VALUES ('2', '10', '1', '14', '-618.518', '-4251.67', '38.718', '4.72222');
INSERT INTO `playercreateinfo` VALUES ('3', '10', '0', '1', '-6230.42', '330.232', '383.105', '6.17716');
INSERT INTO `playercreateinfo` VALUES ('4', '10', '1', '141', '10311.3', '831.463', '1326.41', '5.69632');
INSERT INTO `playercreateinfo` VALUES ('5', '10', '0', '5692', '1699.85', '1706.56', '135.928', '4.88839');
INSERT INTO `playercreateinfo` VALUES ('6', '10', '1', '221', '-2915.55', '-257.347', '59.2693', '0.302378');
INSERT INTO `playercreateinfo` VALUES ('24', '8', '860', '5736', '1466.09', '3465.98', '181.86', '2.77359');
INSERT INTO `playercreateinfo` VALUES ('24', '10', '860', '5736', '1466.09', '3465.98', '181.86', '2.77359');
INSERT INTO `playercreateinfo` VALUES ('24', '1', '860', '5736', '1466.09', '3465.98', '181.86', '2.77359');
INSERT INTO `playercreateinfo` VALUES ('7', '10', '0', '5495', '-4983.42', '877.7', '274.31', '3.06393');
INSERT INTO `playercreateinfo` VALUES ('24', '3', '860', '5736', '1466.09', '3465.98', '181.86', '2.77359');
INSERT INTO `playercreateinfo` VALUES ('24', '4', '860', '5736', '1466.09', '3465.98', '181.86', '2.77359');
INSERT INTO `playercreateinfo` VALUES ('24', '5', '860', '5736', '1466.09', '3465.98', '181.86', '2.77359');
INSERT INTO `playercreateinfo` VALUES ('24', '7', '860', '5736', '1466.09', '3465.98', '181.86', '2.77359');
INSERT INTO `playercreateinfo` VALUES ('8', '10', '1', '5691', '-1171.45', '-5263.65', '0.847728', '5.78945');
INSERT INTO `playercreateinfo` VALUES ('10', '10', '530', '3431', '10349.6', '-6357.29', '33.4026', '5.31605');
INSERT INTO `playercreateinfo` VALUES ('11', '10', '530', '3526', '-3961.64', '-13931.2', '100.615', '2.08364');
INSERT INTO `playercreateinfo` VALUES ('25', '1', '0', '1519', '-8960.02', '516.1', '96.36', '0.67');
INSERT INTO `playercreateinfo` VALUES ('25', '3', '0', '1519', '-8960.02', '516.1', '96.36', '0.67');
INSERT INTO `playercreateinfo` VALUES ('25', '4', '0', '1519', '-8960.02', '516.1', '96.36', '0.67');
INSERT INTO `playercreateinfo` VALUES ('25', '5', '0', '1519', '-8960.02', '516.1', '96.36', '0.67');
INSERT INTO `playercreateinfo` VALUES ('25', '7', '0', '1519', '-8960.02', '516.1', '96.36', '0.67');
INSERT INTO `playercreateinfo` VALUES ('25', '8', '0', '1519', '-8960.02', '516.1', '96.36', '0.67');
INSERT INTO `playercreateinfo` VALUES ('25', '10', '0', '1519', '-8960.02', '516.1', '96.36', '0.67');
INSERT INTO `playercreateinfo` VALUES ('26', '1', '1', '14', '1357.62', '-4373.55', '26.13', '0.67');
INSERT INTO `playercreateinfo` VALUES ('26', '3', '1', '14', '1357.62', '-4373.55', '26.13', '0.67');
INSERT INTO `playercreateinfo` VALUES ('26', '4', '1', '14', '1357.62', '-4373.55', '26.13', '0.67');
INSERT INTO `playercreateinfo` VALUES ('26', '5', '1', '14', '1357.62', '-4373.55', '26.13', '0.67');
INSERT INTO `playercreateinfo` VALUES ('26', '7', '1', '14', '1357.62', '-4373.55', '26.13', '0.67');
INSERT INTO `playercreateinfo` VALUES ('26', '8', '1', '14', '1357.62', '-4373.55', '26.13', '0.67');
INSERT INTO `playercreateinfo` VALUES ('26', '10', '1', '14', '1357.62', '-4373.55', '26.13', '0.67');
INSERT INTO `playercreateinfo` VALUES ('4', '12', '1481', '6383', '1180.64', '3284.96', '70.3484', '4.76134');
INSERT INTO `playercreateinfo` VALUES ('10', '12', '1481', '6383', '1180.64', '3284.96', '70.3484', '4.76134');
INSERT INTO `playercreateinfo` VALUES ('7', '3', '0', '5495', '-4983.42', '877.7', '274.31', '3.06393');
SET FOREIGN_KEY_CHECKS=1;
