#include "yaTime.h"


namespace ya
{
	LARGE_INTEGER Time::mCpuFrequency;
	LARGE_INTEGER Time::mPrevFrequency;
	LARGE_INTEGER Time::mCurFrequency;
	float Time::mDeltaTime = 0.0f;
	void Time::Initialize()
	{
		// CPU 초당 반복되는 진동수를 얻어오는 함수
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램 시작 했을때 cpu 클럭 수
		QueryPerformanceCounter(&mPrevFrequency);
	}
	void Time::Tick()
	{
		QueryPerformanceCounter(&mCurFrequency);

		float differenceFrequency
			= static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);
		mDeltaTime = differenceFrequency / static_cast<float>(mCpuFrequency.QuadPart);

		// 다시 이전의 값을 새로운 지금 값으로 세팅
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;

	}
	void Time::Render(HDC hdc)
	{
		wchar_t szFloat[50] = {};

		// 델타 타임
		// 한프레임 도는 동안 걸린 시간

		float fps = 1.0f / mDeltaTime;

		swprintf_s(szFloat, 50, L"FPS : %f", fps);
		int strLen = wcsnlen_s(szFloat, 50);

		//글자출력
		TextOut(hdc, 10, 10, szFloat, strLen);
	}
}