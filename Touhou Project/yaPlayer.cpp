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
		,mTime(0.0f)
		,danmakuLevel(1)
		,mCount(0)
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
				(L"Player", L"..\\Resources\\Image\\Player_Img\\Reimu\\Player.bmp");
			//mImage->Load(L"..\\Resources\\Image\\Player.bmp");
		}
		
	    mAnimator = new Animator();

		mAnimator->CreateAnimation(L"Idle", mImage
			, Vector2(0.0f, 0.0f), Vector2(31.75f, 50.5f)
			, Vector2(0.0f, 0.0f), 4, 0.1f);

		mAnimator->CreateAnimation(L"LeftMove", mImage
			, Vector2(0.0f, 50.5f), Vector2(31.75f, 50.5f)
			, Vector2(0.0f, 0.0f), 7, 0.1f);
		
		mAnimator->CreateAnimation(L"RightMove", mImage
			, Vector2(0.0f, 101.0f), Vector2(31.75f, 50.5f)
			, Vector2(0.0f, 0.0f), 7, 0.1f);

		mAnimator->Play(L"Idle",true);

		//애니메이션 마지막 프레임에서 이벤트 실행
		mAnimator->GetCompleteEvent(L"Idle") = std::bind(&Player::MoveComplete, this);
		//mAnimator->FindEvevts(L"Idle")->mCompleteEvent = std::bind(&Player::MoveComplete, this);

 
		AddComponent(mAnimator);
		AddComponent(new Collider());

		Scene* playScene = SceneManager::GetScene();
		for (size_t i = 0; i < 1024; i++)
		{
			danmaku[i] = new Danmaku();
			playScene->AddGameObject(danmaku[i], eColliderLayer::Player_Projecttile);
			danmaku[i]->Death();
		}
		mCoff = 0.1f;

		for (size_t i = 0; i < 5; i++)
		{
			firePos[i] = Vector2(0.0f, 0.0f);
		}
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


		if (KEY_DOWN(eKeyCode::W))
		{
			mAnimator->Play(L"Idle", true);
		}
		if (KEY_DOWN(eKeyCode::S))
		{
		}
		if (KEY_DOWN(eKeyCode::A))
		{
			mAnimator->Play(L"LeftMove", false);
		}
		if (KEY_DOWN(eKeyCode::D))
		{
			mAnimator->Play(L"RightMove", false);
		}

		if (KEY_PREESE(eKeyCode::J))
		{
			mTime += Time::DeltaTime();

			if (mTime > 0.1f)
			{
				Attack();

				mTime = 0;
			}
		}
		SetPos(pos);
	}

	//Danmaku* danmaku = new Danmaku();

//Scene* playScene = SceneManager::GetPlayScene();
//playScene->AddGameObject(danmaku, eColliderLayer::Player_Projecttile);

//Vector2 playerPos = GetPos();
//Vector2 playerScale = GetScale() / 2.0f;
//Vector2 missileScale = danmaku->GetScale();

//danmaku->SetPos((playerPos + playerScale) - (missileScale / 2.0f));
//danmaku->mDestPos = Vector2::One; // = Input::GetMousePos();

//danmaku->mDir = Vector2(mCoff, -1.0f + mCoff);
//mCoff -= 0.1f;


	void Player::Render(HDC hdc)
	{
		////플레이어 색
		//HBRUSH blueBrush = CreateSolidBrush(RGB(153, 204, 255));
		//Brush brush(hdc, blueBrush);

		////플레이어 테두리 색
		//HPEN redPen = CreatePen(BS_SOLID, 2, RGB(255, 0, 0));
		//Pen pen(hdc, redPen);

		//Vector2 pos = GetPos();
		//Vector2 scale = GetScale();
		//
		////크기 변경이 안된다.
		////플레이어 그리기
		////BitBlt(hdc, pos.x, pos.y
		////	, mImage->GetWidth(), mImage->GetHeight()
		////	, mImage->GetDC(), 0, 0, SRCCOPY); 

		////pos = Vector2::Zero;


		//Vector2 finalPos;
		//finalPos.x = (pos.x - mImage->GetWidth() * (scale.x / 2.0f));
		//finalPos.y = (pos.y - mImage->GetHeight() * (scale.y / 2.0f));

		//Vector2 rect;
		//rect.x = mImage->GetWidth() * scale.x;
		//rect.y = mImage->GetHeight() * scale.y;

		//TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
		//	, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
		//	, RGB(255, 0, 255));

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
	//애니메이션 Complete 이벤트 
	void Player::MoveComplete()
	{

	}
	void Player::Attack()
	{
		for (size_t i = 0; i < 1024; i++)
		{
			if (danmaku[i]->IsDeath() == true && danmakuLevel == 1)
			{
				DanmakuReset(danmaku[i],firePos);
				break;
			}
			else if (danmaku[i]->IsDeath() == true && danmakuLevel == 2)
			{
				DanmakuReset(danmaku[i],firePos);
				mCount++;
			}
		}
	}

	void Player::DanmakuReset(Danmaku* danmaku, Vector2 pos[5])
	{
		Vector2 firePos = GetPos() + Vector2(100.0f, 100.0f);
		//Vector2 playerScale = GetScale() / 2.0f;
		Vector2 missileScale = danmaku->GetScale();
		danmaku->SetPos((firePos)-(missileScale / 2.0f));
		danmaku->Alive();
	}

	void Player::DanmakuLevel(int level)
	{
		
	}
}