-- Fix for paladin level health
UPDATE `classicmangos`.`player_classlevelstats` SET `basehp` = '30' WHERE (`class` = '2') and (`level` = '2');
-- Paragon Level Stuff
CREATE TABLE classiccharacters.account_paragon(guid int(11) unsigned default 0,paragon_level int(11) unsigned default 0,paragon_xp int(11) unsigned default 0);
INSERT INTO classicmangos.mangos_string (entry, content_default) VALUES (1700, 'Current Paragon level: %u');
INSERT INTO classicmangos.mangos_string (entry, content_default) VALUES (1701, 'Progress to next level: %u / %u xp');
INSERT INTO classicmangos.mangos_string (entry, content_default) VALUES (1702, 'Increasing all attributes by %u, talent points by %u, spell damage and healing done by %u, and experience earned by %u%%');
INSERT INTO classicmangos.mangos_string (entry, content_default) VALUES (1703, "%s's current paragon level: %u");
-- Create account wide money
CREATE TABLE classiccharacters.account_money (guid int(11) unsigned default 0, money int(11) unsigned default 0);
-- Make stackable items more stackable
UPDATE classicmangos.item_template SET stackable = 50 WHERE stackable = 10;
UPDATE classicmangos.item_template SET stackable = 100 WHERE stackable = 20;
-- Make hearthstone cooldown 10 minutes
UPDATE classicmangos.spell_template SET CategoryRecoveryTime = '300000' WHERE (Id = '8690');
-- Make healing potions no longer consumed
UPDATE classicmangos.item_template SET spellcharges_1 = 0 WHERE name LIKE '%Healing Potion%' AND subclass = 3;
-- Set mounts to require no skills
UPDATE classicmangos.item_template SET RequiredSkill = 0, RequiredSkillRank = 0, RequiredLevel = 1 WHERE class = 15 AND RequiredLevel = 40 AND RequiredSkill = 762;
UPDATE classicmangos.item_template SET RequiredSkill = 0, RequiredSkillRank = 0, RequiredLevel = 1 WHERE class = 15 AND RequiredLevel = 60 AND RequiredSkill = 762;
-- Make mounts instant cast
UPDATE classicmangos.spell_template SET CastingTimeIndex = 1 WHERE Mechanic = 21;
-- Make mounts faster
UPDATE classicmangos.spell_template SET EffectBasePoints2 = 129 WHERE Mechanic = 21 AND EffectBasePoints2 = 99;
UPDATE classicmangos.spell_template SET EffectBasePoints2 = 99 WHERE Mechanic = 21 AND EffectBasePoints2 = 59;
-- Add starting mounts Human
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (1,1,2414,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (1,2,2414,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (1,4,2414,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (1,5,2414,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (1,8,2414,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (1,9,2414,1);
-- Add starting mounts Orc
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (2,1,1132,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (2,3,1132,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (2,4,1132,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (2,7,1132,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (2,9,1132,1);
-- Add starting mounts Dwarf
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (3,1,5872,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (3,2,5872,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (3,3,5872,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (3,4,5872,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (3,5,5872,1);
-- Add starting mounts Nightelf
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (4,1,8629,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (4,3,8629,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (4,4,8629,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (4,5,8629,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (4,11,8629,1);
-- Add starting mounts Undead
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (5,1,13331,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (5,4,13331,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (5,5,13331,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (5,8,13331,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (5,9,13331,1);
-- Add starting mounts Tauren
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (6,1,15290,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (6,3,15290,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (6,7,15290,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (6,11,15290,1);
-- Add starting mounts Gnome
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (7,1,13322,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (7,4,13322,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (7,8,13322,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (7,9,13322,1);
-- Add starting mounts Troll
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (8,1,8588,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (8,3,8588,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (8,4,8588,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (8,5,8588,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (8,7,8588,1);
INSERT INTO classicmangos.playercreateinfo_item (race, class, itemid, amount) VALUES (8,8,8588,1);
-- Change paladin blessings to last 30 Minutes
UPDATE classicmangos.spell_template SET DurationIndex = 30 WHERE SpellName LIKE '%Blessing of%' AND DurationIndex = 5;
-- Change Battle Shout to last 30 Minutes
UPDATE classicmangos.spell_template SET DurationIndex = 30 WHERE SpellName LIKE '%Battle Shout%' AND DurationIndex = 4 AND Rank != '' AND ManaCost = 100;
-- Change druid buffs to last 30 Minutes
UPDATE classicmangos.spell_template SET DurationIndex = 30 WHERE (SpellName LIKE '%Omen of %' OR SpellName LIKE '%Thorns%') AND DurationIndex = 6;
-- Remove item class/race restrictions
UPDATE classicmangos.item_template SET AllowableClass = -1, AllowableRace = -1 WHERE (class = 2 OR class = 4);
-- Create world drops
INSERT INTO classicmangos.reference_loot_template_names (entry, name) VALUES (65300,'World Drops Item Level 0 to 15');
INSERT INTO classicmangos.reference_loot_template_names (entry, name) VALUES (65301,'World Drops Item Level 14 to 19');
INSERT INTO classicmangos.reference_loot_template_names (entry, name) VALUES (65302,'World Drops Item Level 18 to 24');
INSERT INTO classicmangos.reference_loot_template_names (entry, name) VALUES (65303,'World Drops Item Level 23 to 29');
INSERT INTO classicmangos.reference_loot_template_names (entry, name) VALUES (65304,'World Drops Item Level 28 to 34');
INSERT INTO classicmangos.reference_loot_template_names (entry, name) VALUES (65305,'World Drops Item Level 33 to 39');
INSERT INTO classicmangos.reference_loot_template_names (entry, name) VALUES (65306,'World Drops Item Level 38 to 44');
INSERT INTO classicmangos.reference_loot_template_names (entry, name) VALUES (65307,'World Drops Item Level 43 to 49');
INSERT INTO classicmangos.reference_loot_template_names (entry, name) VALUES (65308,'World Drops Item Level 48 to 54');
INSERT INTO classicmangos.reference_loot_template_names (entry, name) VALUES (65309,'World Drops Item Level 53 to 59');
INSERT INTO classicmangos.reference_loot_template_names (entry, name) VALUES (65310,'World Drops Item Level 58 to 65');
INSERT INTO classicmangos.reference_loot_template_names (entry, name) VALUES (65311,'World Drops Item Level 65 to 100');
--
INSERT INTO classicmangos.reference_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT 65300, entry, 0, 1, 1, 1, 0, name FROM classicmangos.item_template WHERE (ItemLevel >= 0 AND ItemLevel <= 15 AND (class = 2 OR class= 4) AND  Quality > 1 AND Quality < 5 AND requiredhonorrank = 0 AND RequiredSkill = 0 AND AllowableClass = -1 AND RequiredReputationFaction = 0) OR entry = 14156;
INSERT INTO classicmangos.reference_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT 65301, entry, 0, 1, 1, 1, 0, name FROM classicmangos.item_template WHERE (ItemLevel >= 14 AND ItemLevel <= 19 AND (class = 2 OR class= 4) AND  Quality > 1 AND Quality < 5 AND requiredhonorrank = 0 AND RequiredSkill = 0 AND AllowableClass = -1 AND RequiredReputationFaction = 0) OR entry = 14156;
INSERT INTO classicmangos.reference_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT 65302, entry, 0, 1, 1, 1, 0, name FROM classicmangos.item_template WHERE (ItemLevel >= 18 AND ItemLevel <= 24 AND (class = 2 OR class= 4) AND  Quality > 1 AND Quality < 5 AND requiredhonorrank = 0 AND RequiredSkill = 0 AND AllowableClass = -1 AND RequiredReputationFaction = 0) OR entry = 14156;
INSERT INTO classicmangos.reference_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT 65303, entry, 0, 1, 1, 1, 0, name FROM classicmangos.item_template WHERE (ItemLevel >= 23 AND ItemLevel <= 29 AND (class = 2 OR class= 4) AND  Quality > 1 AND Quality < 5 AND requiredhonorrank = 0 AND RequiredSkill = 0 AND AllowableClass = -1 AND RequiredReputationFaction = 0) OR entry = 14156;
INSERT INTO classicmangos.reference_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT 65304, entry, 0, 1, 1, 1, 0, name FROM classicmangos.item_template WHERE (ItemLevel >= 28 AND ItemLevel <= 34 AND (class = 2 OR class= 4) AND  Quality > 1 AND Quality < 5 AND requiredhonorrank = 0 AND RequiredSkill = 0 AND AllowableClass = -1 AND RequiredReputationFaction = 0) OR entry = 14156;
INSERT INTO classicmangos.reference_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT 65305, entry, 0, 1, 1, 1, 0, name FROM classicmangos.item_template WHERE (ItemLevel >= 33 AND ItemLevel <= 39 AND (class = 2 OR class= 4) AND  Quality > 1 AND Quality < 5 AND requiredhonorrank = 0 AND RequiredSkill = 0 AND AllowableClass = -1 AND RequiredReputationFaction = 0) OR entry = 14156;
INSERT INTO classicmangos.reference_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT 65306, entry, 0, 1, 1, 1, 0, name FROM classicmangos.item_template WHERE (ItemLevel >= 38 AND ItemLevel <= 44 AND (class = 2 OR class= 4) AND  Quality > 1 AND Quality < 5 AND requiredhonorrank = 0 AND RequiredSkill = 0 AND AllowableClass = -1 AND RequiredReputationFaction = 0) OR entry = 14156;
INSERT INTO classicmangos.reference_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT 65307, entry, 0, 1, 1, 1, 0, name FROM classicmangos.item_template WHERE (ItemLevel >= 43 AND ItemLevel <= 49 AND (class = 2 OR class= 4) AND  Quality > 1 AND Quality < 5 AND requiredhonorrank = 0 AND RequiredSkill = 0 AND AllowableClass = -1 AND RequiredReputationFaction = 0) OR entry = 17966;
INSERT INTO classicmangos.reference_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT 65308, entry, 0, 1, 1, 1, 0, name FROM classicmangos.item_template WHERE (ItemLevel >= 48 AND ItemLevel <= 54 AND (class = 2 OR class= 4) AND  Quality > 1 AND Quality < 5 AND requiredhonorrank = 0 AND RequiredSkill = 0 AND AllowableClass = -1 AND RequiredReputationFaction = 0) OR entry = 17966;
INSERT INTO classicmangos.reference_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT 65309, entry, 0, 1, 1, 1, 0, name FROM classicmangos.item_template WHERE (ItemLevel >= 53 AND ItemLevel <= 59 AND (class = 2 OR class= 4) AND  Quality > 1 AND Quality < 5 AND requiredhonorrank = 0 AND RequiredSkill = 0 AND AllowableClass = -1 AND RequiredReputationFaction = 0) OR entry = 17966;
INSERT INTO classicmangos.reference_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT 65310, entry, 0, 1, 1, 1, 0, name FROM classicmangos.item_template WHERE (ItemLevel >= 58 AND ItemLevel <= 65 AND (class = 2 OR class= 4) AND  Quality > 1 AND Quality < 5 AND requiredhonorrank = 0 AND RequiredSkill = 0 AND AllowableClass = -1 AND RequiredReputationFaction = 0) OR entry = 17966;
INSERT INTO classicmangos.reference_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT 65311, entry, 0, 1, 1, 1, 0, name FROM classicmangos.item_template WHERE (ItemLevel >= 65 AND ItemLevel <= 100 AND (class = 2 OR class= 4) AND  Quality > 1 AND Quality < 5 AND requiredhonorrank = 0 AND RequiredSkill = 0 AND AllowableClass = -1 AND RequiredReputationFaction = 0) OR entry = 17966;
--
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65300,9,1, -65300,1,0,'World Drops Item Level 0 to 15' FROM classicmangos.creature_template WHERE MaxLevel >= 0 AND MinLevel <= 10 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65301,8.5,1, -65301,1,0,'World Drops Item Level 14 to 19' FROM classicmangos.creature_template WHERE MaxLevel >= 9 AND MinLevel <= 15 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65302,8,1, -65302,1,0,'World Drops Item Level 18 to 24' FROM classicmangos.creature_template WHERE MaxLevel >= 14 AND MinLevel <= 20 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65303,7.5,1, -65303,1,0,'World Drops Item Level 23 to 29' FROM classicmangos.creature_template WHERE MaxLevel >= 19 AND MinLevel <= 25 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65304,7,1, -65304,1,0,'World Drops Item Level 28 to 34' FROM classicmangos.creature_template WHERE MaxLevel >= 24 AND MinLevel <= 30 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65305,6.5,1, -65305,1,0,'World Drops Item Level 33 to 39' FROM classicmangos.creature_template WHERE MaxLevel >= 29 AND MinLevel <= 35 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65306,6,1, -65306,1,0,'World Drops Item Level 38 to 44' FROM classicmangos.creature_template WHERE MaxLevel >= 34 AND MinLevel <= 40 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65307,5.5,1, -65307,1,0,'World Drops Item Level 43 to 49' FROM classicmangos.creature_template WHERE MaxLevel >= 39 AND MinLevel <= 45 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65308,5,1, -65308,1,0,'World Drops Item Level 48 to 54' FROM classicmangos.creature_template WHERE MaxLevel >= 44 AND MinLevel <= 50 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65309,4.5,1, -65309,1,0,'World Drops Item Level 53 to 59' FROM classicmangos.creature_template WHERE MaxLevel >= 49 AND MinLevel <= 54 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65310,4,1, -65310,1,0,'World Drops Item Level 58 to 65' FROM classicmangos.creature_template WHERE MaxLevel >= 52 AND MinLevel <= 63 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,0.6,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 54 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,0.8,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 55 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,1,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 56 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,1.2,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 57 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,1.4,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 58 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,1.6,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 59 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,1.8,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 60 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,2,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 61 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,2.2,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 62 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,2.4,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 63 AND NpcFlags = 0 AND Rank = 0 AND LootId != 0;
--
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65300,18,1, -65300,1,0,'World Drops Item Level 0 to 15' FROM classicmangos.creature_template WHERE MaxLevel >= 0 AND MinLevel <= 10 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65301,17,1, -65301,1,0,'World Drops Item Level 14 to 19' FROM classicmangos.creature_template WHERE MaxLevel >= 9 AND MinLevel <= 15 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65302,16,1, -65302,1,0,'World Drops Item Level 18 to 24' FROM classicmangos.creature_template WHERE MaxLevel >= 14 AND MinLevel <= 20 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65303,15,1, -65303,1,0,'World Drops Item Level 23 to 29' FROM classicmangos.creature_template WHERE MaxLevel >= 19 AND MinLevel <= 25 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65304,14,1, -65304,1,0,'World Drops Item Level 28 to 34' FROM classicmangos.creature_template WHERE MaxLevel >= 24 AND MinLevel <= 30 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65305,13,1, -65305,1,0,'World Drops Item Level 33 to 39' FROM classicmangos.creature_template WHERE MaxLevel >= 29 AND MinLevel <= 35 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65306,12,1, -65306,1,0,'World Drops Item Level 38 to 44' FROM classicmangos.creature_template WHERE MaxLevel >= 34 AND MinLevel <= 40 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65307,11,1, -65307,1,0,'World Drops Item Level 43 to 49' FROM classicmangos.creature_template WHERE MaxLevel >= 39 AND MinLevel <= 45 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65308,10,1, -65308,1,0,'World Drops Item Level 48 to 54' FROM classicmangos.creature_template WHERE MaxLevel >= 44 AND MinLevel <= 50 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65309,9,1, -65309,1,0,'World Drops Item Level 53 to 59' FROM classicmangos.creature_template WHERE MaxLevel >= 49 AND MinLevel <= 54 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65310,8,1, -65310,1,0,'World Drops Item Level 58 to 65' FROM classicmangos.creature_template WHERE MaxLevel >= 52 AND MinLevel <= 63 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,1.2,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 54 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,1.6,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 55 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,2,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 56 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,2.4,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 57 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,2.8,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 58 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,3.2,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 59 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,3.6,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 60 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,4,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 61 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,10,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 62 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65311,15,1, -65311,1,0,'World Drops Item Level 65 to 100' FROM classicmangos.creature_template WHERE MaxLevel = 63 AND NpcFlags = 0 AND Rank > 0 AND LootId != 0;
--
INSERT INTO classicmangos.reference_loot_template_names (entry, name) VALUES (65332,'World Drops Misc');
INSERT INTO classicmangos.reference_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT 65332, entry, 0, 1, 1, 1, 0, name FROM classicmangos.item_template WHERE entry IN (23545,23547,23548,23549,11622,11642,11644,11645,11647,13506,13510,13511,13512,13513,18329,18330,18331,18169,18170,18171,18172,18173,18182,20076,20077,20078,14156,17966,13453,13445,13452,13447,13513,13511,13506,13512,13510,13454,13461,13457,13456,13458,13459,13455);
INSERT INTO classicmangos.creature_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, condition_id, comments) SELECT DISTINCT LootId, 65332,1,1, -65332,1,0,'World Drops Misc' FROM classicmangos.creature_template WHERE MaxLevel >= 45 AND NpcFlags = 0 AND LootId != 0;
--
-- Make soul stones stackable
UPDATE classicmangos.item_template SET stackable = 20 WHERE entry = 6265;
-- Fix for warlock pet Armor
UPDATE classicmangos.creature_template SET ArmorMultiplier = '1' WHERE Entry = 1860;
UPDATE classicmangos.creature_template SET ArmorMultiplier = '1' WHERE Entry = 416;
--
-- Add enchanting stuff to vendors
INSERT INTO classicmangos.npc_vendor (entry, item, maxcount, incrtime, condition_id, comments)
SELECT entry, 6218, 0, 0, 0, 'Added For Enchanting'
FROM classicmangos.npc_vendor WHERE item = 6217;
--
INSERT INTO classicmangos.npc_vendor (entry, item, maxcount, incrtime, condition_id, comments)
SELECT entry, 6339, 0, 0, 0, 'Added For Enchanting'
FROM classicmangos.npc_vendor WHERE item = 6217;
--
INSERT INTO classicmangos.npc_vendor (entry, item, maxcount, incrtime, condition_id, comments)
SELECT entry, 11130, 0, 0, 0, 'Added For Enchanting'
FROM classicmangos.npc_vendor WHERE item = 6217;
--
INSERT INTO classicmangos.npc_vendor (entry, item, maxcount, incrtime, condition_id, comments)
SELECT entry, 11145, 0, 0, 0, 'Added For Enchanting'
FROM classicmangos.npc_vendor WHERE item = 6217;
--
INSERT INTO classicmangos.npc_vendor (entry, item, maxcount, incrtime, condition_id, comments)
SELECT entry, 16207, 0, 0, 0, 'Added For Enchanting'
FROM classicmangos.npc_vendor WHERE item = 6217;
-- Increase Bag size
UPDATE `classicmangos`.`item_template` SET `ContainerSlots` = '20' WHERE (`entry` = '14156');
UPDATE `classicmangos`.`item_template` SET `ContainerSlots` = '24' WHERE (`entry` = '17966');
UPDATE classicmangos.item_template SET ContainerSlots = ContainerSlots + 4 WHERE InventoryType = 18 AND subclass = 0;
-- Set sell price of enchanting matierials
UPDATE classicmangos.item_template SET SellPrice = BuyPrice * 0.8 WHERE Material = 2 AND SellPrice = 0 AND class = 7;
