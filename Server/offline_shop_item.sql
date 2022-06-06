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

 Date: 05/06/2022 22:18:18
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for offline_shop_item
-- ----------------------------
DROP TABLE IF EXISTS `offline_shop_item`;
CREATE TABLE `offline_shop_item`  (
  `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  `owner_id` int(11) UNSIGNED NOT NULL DEFAULT 0,
  `pos` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `count` smallint(3) UNSIGNED NOT NULL DEFAULT 0,
  `vnum` int(11) UNSIGNED NOT NULL DEFAULT 0,
  `socket0` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `socket1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `socket2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `socket3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `socket4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `socket5` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `attrtype0` tinyint(4) NOT NULL DEFAULT 0,
  `attrvalue0` smallint(6) NOT NULL DEFAULT 0,
  `attrtype1` tinyint(4) NOT NULL DEFAULT 0,
  `attrvalue1` smallint(6) NOT NULL DEFAULT 0,
  `attrtype2` tinyint(4) NOT NULL DEFAULT 0,
  `attrvalue2` smallint(6) NOT NULL DEFAULT 0,
  `attrtype3` tinyint(4) NOT NULL DEFAULT 0,
  `attrvalue3` smallint(6) NOT NULL DEFAULT 0,
  `attrtype4` tinyint(4) NOT NULL DEFAULT 0,
  `attrvalue4` smallint(6) NOT NULL DEFAULT 0,
  `attrtype5` tinyint(4) NOT NULL DEFAULT 0,
  `attrvalue5` smallint(6) NOT NULL DEFAULT 0,
  `attrtype6` tinyint(4) NOT NULL DEFAULT 0,
  `attrvalue6` smallint(6) NOT NULL DEFAULT 0,
  `applytype0` int(11) NOT NULL DEFAULT 0,
  `applyvalue0` int(11) NOT NULL DEFAULT 0,
  `applytype1` int(11) NOT NULL DEFAULT 0,
  `applyvalue1` int(11) NOT NULL DEFAULT 0,
  `applytype2` int(11) NOT NULL DEFAULT 0,
  `applyvalue2` int(11) NOT NULL DEFAULT 0,
  `applytype3` int(11) NOT NULL DEFAULT 0,
  `applyvalue3` int(11) NOT NULL DEFAULT 0,
  `applytype4` int(11) NOT NULL DEFAULT 0,
  `applyvalue4` int(11) NOT NULL DEFAULT 0,
  `applytype5` int(11) NOT NULL DEFAULT 0,
  `applyvalue5` int(11) NOT NULL DEFAULT 0,
  `applytype6` int(11) NOT NULL DEFAULT 0,
  `applyvalue6` int(11) NOT NULL DEFAULT 0,
  `applytype7` int(11) NOT NULL DEFAULT 0,
  `applyvalue7` int(11) NOT NULL DEFAULT 0,
  `price` bigint(255) NOT NULL DEFAULT 0,
  `price_cheque` int(11) NOT NULL DEFAULT 0,
  `status` smallint(1) NOT NULL DEFAULT 0,
  `buyer_name` varchar(64) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'NONAME',
  `transmutation` int(11) NOT NULL DEFAULT 0,
  `item_name` varbinary(50) NOT NULL DEFAULT 'NONAME',
  `refine_level` int(11) NOT NULL DEFAULT 0,
  `shop_id` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `owner_id_idx`(`owner_id`) USING BTREE,
  INDEX `item_vnum_index`(`vnum`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 2000003132 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = DYNAMIC;

SET FOREIGN_KEY_CHECKS = 1;
