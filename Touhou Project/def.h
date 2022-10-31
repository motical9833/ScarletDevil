#pragma once

#define KEY_PREESE(KEY) ya::Input::GetKeyState(KEY) == ya::eKeyState::PRESSED

enum class eSceneType
{
	Logo,
	Title,
	Stage_1,
	Stage_2,
	Stage_3,
	Stage_4,
	Stage_5,
	Stage_6,
	Stage_EX,
	Stage_PH,
	Ending,
	MAX,
};

enum class eComponentType
{
	Animator,
	Collider,
	Sound,
	End,
};