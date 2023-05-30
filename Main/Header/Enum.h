#pragma once

#pragma region HEEJUNE

enum class TERRIAN_TYPE { ACT1, ACT2, ACT3, TYPEEND };

#pragma region HEEJUNE


#pragma endregion

#pragma region CHAN

enum class OBJ_TYPE		{ PLAYER, MONSTER, NPC, ITEM, TERRAIN, ENVIORMENT, UI, TYPEEND };

enum class OBJ_STATE	{ STAND, WALK, DASH, ATTACK, DAMAGE, SKILL, DIE, TYPEEND };

enum class OBJ_DIR		{ UP, RIGHT_UP, RIGHT, RIGHT_DOWN, DOWN, LEFT_DOWN, LEFT, LEFT_UP, TYPEEND };

#pragma endregion

enum TEXTYPE			{ TEX_SINGLE, TEX_MULTI, TEX_END };

enum OBJID				{ OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_MOUSE, OBJ_SHIELD, OBJ_UI, OBJ_END };

enum class TOP_TAB_TYPE { UNIT, MAP, TILE, TYPEEND }; // »ó´Ü ÅÇ

enum class MID_TAB_TYPE { PLAYER, MONSTER, ITEM, NONE, TYPEEND }; // Áß°£ ÅÇ (°¢ »ó´ÜÅÇ ³»ºÎ¿¡ Æ÷ÇÔµÇ¾î ÀÖ´Â ÅÇ) 




