#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCollider.h"
namespace ya
{
	Player::Player()
		:mSpeed(1.0f)
	{
		SetPos({ 0.0f,0.0f });
		SetScale({ 2.0f,2.0f }); 
		
		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Player", L"..\\Resources\\Image\\Player.bmp");
			//mImage->Load(L"..\\Resources\\Image\\Player.bmp");
		}

		AddComponent(new Animator());
		AddComponent(new Collider());
	}
	Player::~Player()
	{

	}
	void Player::Tick()
	{
		GameObject::Tick();

		Vector2 pos = GetPos();

		if (KEY_PREESE(eKeyCode::W))
		{
			pos.y -= 100.0f * Time::DeltaTime();
		}
		if (KEY_PREESE(eKeyCode::S))
		{
			pos.y += 100.0f * Time::DeltaTime();
		}
		if (KEY_PREESE(eKeyCode::A))
		{
			pos.x -= 100.0f *Time::DeltaTime();
		}
		if (KEY_PREESE(eKeyCode::D))
		{
			pos.x += 100.0f * Time::DeltaTime();
		}
		SetPos(pos);
	}
	void Player::Render(HDC hdc)
	{
		//플레이어 색
		HBRUSH blueBrush = CreateSolidBrush(RGB(153, 204, 255));
		Brush brush(hdc, blueBrush);

		//플레이어 테두리 색
		HPEN redPen = CreatePen(BS_SOLID, 2, RGB(255, 0, 0));
		Pen pen(hdc, redPen);

		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		
		//크기 변경이 안된다.
		//플레이어 그리기
		//BitBlt(hdc, pos.x, pos.y
		//	, mImage->GetWidth(), mImage->GetHeight()
		//	, mImage->GetDC(), 0, 0, SRCCOPY);

		//pos = Vector2::Zero;

		Vector2 finalPos;
		finalPos.x = (pos.x - mImage->GetWidth() * (scale.x / 2.0f));
		finalPos.y = (pos.y - mImage->GetHeight() * (scale.x / 2.0f));

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;


		TransparentBlt(hdc, finalPos.x, finalPos.y
			, rect.x, rect.y, mImage->GetDC(), 0, 0
			, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(hdc);
	}
}