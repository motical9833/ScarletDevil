#include "yaPlayer.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaDanmaku.h"
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
		SetName(L"Player");
		SetPos({ 100.0f,100.0f });
		SetScale({ 2.0f,2.0f }); 
		
		if (mImage == nullptr)
		{
			/*BgImageObject* bg = new BgImageObject();
			bg->SetImage(L"TitleBG", L"BGImg\\TitleBG.bmp");
			bg->Initialize();

			AddGameObject(bg);*/

			mImage = Resources::Load<Image>
				(L"Player", L"..\\Resources\\Image\\Player_Img\\Reimu\\Reimu_1.bmp");
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
		if (KEY_DOWN(eKeyCode::J))
		{
			Danmaku* danmaku = new Danmaku();

			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(danmaku, eColliderLayer::Player_Projecttile);

			Vector2 playerPos = GetPos();
			Vector2 playerScale = GetScale() / 2.0f;
			Vector2 missileScale = danmaku->GetScale();

			danmaku->SetPos((playerPos + playerScale) - (missileScale / 2.0f));
		}

		SetPos(pos);
	}
	void Player::Render(HDC hdc)
	{
		////플레이어 색
		//HBRUSH blueBrush = CreateSolidBrush(RGB(153, 204, 255));
		//Brush brush(hdc, blueBrush);

		////플레이어 테두리 색
		//HPEN redPen = CreatePen(BS_SOLID, 2, RGB(255, 0, 0));
		//Pen pen(hdc, redPen);

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
		finalPos.y = (pos.y - mImage->GetHeight() * (scale.y / 2.0f));

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));

		GameObject::Render(hdc);
	}
	void Player::OnCollisionEnter(Collider* other)
	{
	}
	void Player::OnCollisionStay(Collider* other)
	{
	}
	void Player::OnCollisionExit(Collider* other)
	{
	}
}