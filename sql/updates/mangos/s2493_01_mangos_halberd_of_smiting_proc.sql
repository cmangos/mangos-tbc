-- Fix #3891: Halberd of Smiting (item 19874) - Decapitate aura was applied on every hit
-- (spelltrigger_1 = 2), stacking infinitely and causing multiple Decapitate procs per swing.
-- Change the item spell trigger to ON_EQUIP (1) so the passive aura 25669 is applied once
-- when the weapon is equipped and procs correctly through its spell proc event.
UPDATE `item_template` SET `spelltrigger_1` = 1 WHERE `entry` = 19874;
