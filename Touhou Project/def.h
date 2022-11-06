#pragma once

#define KEY_PREESE(KEY) ya::Input::GetKeyState(KEY) == ya::eKeyState::PRESSED
#define KEY_DOWN(KEY) ya::Input::GetKeyState(KEY) == ya::eKeyState::DOWN

enum class eSceneType
{
	Logo,
	Title,
	Play,
	End,
	MAX,
};

enum class ePenColor
{
	Red,
	Green,
	Blue,
	End,
};

enum class eBrushColor
{
	Transparent, //투명
	Blakc,
	Gray, //167 0 67
	White,
	End,
};

enum class eComponentType
{
	Animator,
	Collider,
	Sound,
	End,
};

#define _COLLIDER_LAYER 16
enum class eColliderLayer
{
	Default,
	BackGround,
	Player,
	Player_Projecttile,
	Monster,
	Monster_Projecttile,


	UI = _COLLIDER_LAYER -1,
	End = _COLLIDER_LAYER,
};

// union : 메모리 공간 공유
union ColliderID
{
	struct
	{
		UINT32 left;
		UINT32 right;
	};
	UINT64 ID;
};