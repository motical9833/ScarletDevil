#include "yaInput.h"
namespace ya
{
	int ASCII[(UINT)eKeyCode::End] =
	{
		'Q','W','E','R','T','Y','U','I','O','P',
		'A','S','D','F','G','H','J','K','L',
		'Z','X','C','V','B','N','M',

		//NumPad
		VK_NUMPAD0,VK_NUMPAD1,VK_NUMPAD2,
		VK_NUMPAD3,VK_NUMPAD4,VK_NUMPAD5,
		VK_NUMPAD6,VK_NUMPAD7,VK_NUMPAD8,
		VK_NUMPAD9,
	};

	std::vector<Input::Key> Input::mKeys;

	void Input::Initialize()
	{
		for (size_t i = 0; i < (UINT)eKeyCode::End; i++)
		{
			Key key;
			key.keyCode = (eKeyCode)i;
			key.keyState = eKeyState::NONE;
			key.bPressed = false;

			mKeys.push_back(key);
		}
	}
	void Input::Tick()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::End; i++)
		{
			//해당키가 현재 눌려 있다.
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				//이전 프레임에 눌려있었다.
				if (mKeys[i].bPressed)
				{
					mKeys[i].keyState = eKeyState::PRESSED;
				}
				else
				{
					mKeys[i].keyState = eKeyState::DOWN;
				}
				mKeys[i].bPressed = true;
			}
			else //해당키가 현재 눌려져 있지 않다
			{
				if (mKeys[i].bPressed)
				{
					mKeys[i].keyState = eKeyState::UP;
				}
				else
				{
					mKeys[i].keyState = eKeyState::NONE;
				}

				mKeys[i].bPressed = false;
			}
		}
	}
	void Input::Render(HDC hdc)
	{

	}
	eKeyState Input::GetKeyState(eKeyCode keycode)
	{
		return mKeys[(UINT)keycode].keyState;
	}
}