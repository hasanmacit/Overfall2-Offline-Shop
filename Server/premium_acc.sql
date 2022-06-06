/*
 Navicat Premium Data Transfer

 Source Server         : turkmmo
 Source Server Type    : MySQL
 Source Server Version : 50651
 Source Host           : 78.135.111.16:3306
 Source Schema         : account

 Target Server Type    : MySQL
 Target Server Version : 50651
 File Encoding         : 65001

 Date: 05/06/2022 22:17:43
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for premium_acc
-- ----------------------------
DROP TABLE IF EXISTS `premium_acc`;
CREATE TABLE `premium_acc`  (
  `accountId` int(30) NOT NULL DEFAULT 0,
  `premium_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`accountId`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = ascii COLLATE = ascii_general_ci ROW_FORMAT = DYNAMIC;

SET FOREIGN_KEY_CHECKS = 1;
