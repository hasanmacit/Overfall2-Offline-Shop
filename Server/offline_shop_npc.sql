/*
 Navicat Premium Data Transfer

 Source Server         : turkmmo
 Source Server Type    : MySQL
 Source Server Version : 50651
 Source Host           : 78.135.111.16:3306
 Source Schema         : player

 Target Server Type    : MySQL
 Target Server Version : 50651
 File Encoding         : 65001

 Date: 05/06/2022 22:18:25
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for offline_shop_npc
-- ----------------------------
DROP TABLE IF EXISTS `offline_shop_npc`;
CREATE TABLE `offline_shop_npc`  (
  `owner_id` int(11) NOT NULL DEFAULT 0,
  `sign` varchar(32) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `name` varchar(32) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `time` int(11) NULL DEFAULT NULL,
  `x` int(11) NULL DEFAULT NULL,
  `y` int(11) NULL DEFAULT NULL,
  `z` int(11) NULL DEFAULT NULL,
  `mapIndex` int(11) NULL DEFAULT NULL,
  `channel` int(2) NULL DEFAULT NULL,
  `level` int(11) NULL DEFAULT NULL,
  `align` int(11) NULL DEFAULT NULL,
  `guild` varchar(32) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT 'NONAME',
  `npc_vnum` int(11) NULL DEFAULT NULL,
  `border_style` int(2) NULL DEFAULT 0,
  PRIMARY KEY (`owner_id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = DYNAMIC;

SET FOREIGN_KEY_CHECKS = 1;
