/*
  Teleport menu item
*/


-- ----------------------------
-- Table structure for pomelo_teleport_template
-- ----------------------------

CREATE TABLE `pomelo_teleport_template`  (
  `entry` int(11) NOT NULL AUTO_INCREMENT,
  `menu_id` int(11) NOT NULL,
  `action_id` int(11) NOT NULL,
  `icon` int(11) NOT NULL DEFAULT 0,
  `menu_item_text` varchar(255) NOT NULL,
  `function` int(11) NOT NULL,
  `teleport_map` int(11) NOT NULL DEFAULT 0,
  `teleport_x` float NOT NULL,
  `teleport_y` float NOT NULL,
  `teleport_z` float NOT NULL,
  `cost_money` int(11) NOT NULL DEFAULT 0,
  `level_required` int(11) NOT NULL,
  `permission_required` int(11) NOT NULL,
  `trigger_menu` int(11) NOT NULL,
  `camp_order` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`entry`) USING BTREE,
  UNIQUE INDEX `IX_menu_id_action_id`(`menu_id`, `action_id`) USING BTREE,
  INDEX `IX_menu_id`(`menu_id`) USING BTREE,
  INDEX `IX_trigger_menu`(`trigger_menu`) USING BTREE
);
