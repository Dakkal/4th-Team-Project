#pragma once

#pragma region HEEJUNE

enum class TERRIAN_TYPE { ACT1, ACT2, ACT3, TYPEEND };


#pragma endregion

enum TEXTYPE			{ TEX_SINGLE, TEX_MULTI, TEX_END };

enum OBJID				{ OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_MOUSE, OBJ_SHIELD, OBJ_UI, OBJ_END };

enum class TOP_TAB_TYPE { UNIT, MAP, TILE, TYPEEND }; // ��� ��

enum class MID_TAB_TYPE { PLAYER, MONSTER, ITEM, NONE, TYPEEND }; // �߰� �� (�� ����� ���ο� ���ԵǾ� �ִ� ��) 

enum class OBJ_TYPE		{ PLAYER, MONSTER, NPC, ITEM, TERRAIN, UI, TYPEEND };

enum class OBJ_STATE	{ STAND, WALK, DASH, ATTACK, DAMAGE, SKILL, DIE, TYPEEND };



