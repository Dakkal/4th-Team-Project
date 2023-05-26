#pragma once

enum TEXTYPE			{ TEX_SINGLE, TEX_MULTI, TEX_END };

enum  OBJID				{ OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_MOUSE, OBJ_SHIELD, OBJ_UI, OBJ_END };

enum class TOP_TAB_TYPE { UNIT, MAP, TILE, TYPEEND };		// 상단 탭

enum class MID_TAB_TYPE { PLAYER, MONSTER, ITEM, NONE, TYPEEND }; // 중간 탭 (각 상단탭 내부에 포함되어 있는 탭) 

