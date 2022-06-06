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

 Date: 05/06/2022 22:18:32
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for offline_shop_sales
-- ----------------------------
DROP TABLE IF EXISTS `offline_shop_sales`;
CREATE TABLE `offline_shop_sales`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `buyer_id` int(11) NOT NULL DEFAULT 0,
  `buyer_name` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  `item_owner` int(11) NOT NULL DEFAULT 0,
  `item_vnum` int(11) NOT NULL DEFAULT 0,
  `item_count` int(11) NOT NULL DEFAULT 0,
  `item_price` bigint(255) NOT NULL DEFAULT 0,
  `item_cheque` int(11) NOT NULL DEFAULT 0,
  `datetime` bigint(20) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 21290 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = DYNAMIC;

SET FOREIGN_KEY_CHECKS = 1;
