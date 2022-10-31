#pragma once
#include "Common.h"


namespace ya
{
	//키 종류
	enum class eKeyCode
	{
		//Alphabet
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,

		//Num Pad
		NUM_0, NUM_1, NUM_2,
		NUM_3, NUM_4, NUM_5,
		NUM_6, NUM_7, NUM_8,
		NUM_9,

		End,
	};
	//키 상태
	enum class eKeyState
	{
		DOWN,
		PRESSED,
		UP,
		NONE,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode keyCode;
			eKeyState keyState;
			bool bPressed;
		};


	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);
		
		static eKeyState GetKeyState(eKeyCode keycode);
	private:

		static std::vector<Key> mKeys;
	};

}