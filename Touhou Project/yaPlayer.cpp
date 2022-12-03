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

#define DANMAKUSPEED 800.0f
#define BOMBSPEED 200.0f

namespace ya
{
	Player::Player()
		:mSpeed(1.0f)
		,nomalTime(0.0f)
		,bonusTime(0.0f)
		,danmakuLevel(1)
		,level(1)
		,mCount(0)
		,danmakuTime{0.3f,1.0f}
		,bombOnOff(true)
	{
		SetName(L"Player");
		SetPos({ 100.0f,100.0f });
		SetScale({ 2.0f,2.0f }); 
		
		if (mImage == nullptr)
		{
			//BgImageObject* bg = new BgImageObject();
			//bg->SetImage(L"TitleBG", L"BGImg\\TitleBG.bmp");
			//bg->Initialize();

			//AddGameObject(bg);

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
		//for (size_t i = 0; i < 1024; i++)
		//{
		//	danmaku[i] = new Danmaku();
		//	playScene->AddGameObject(danmaku[i], eColliderLayer::Player_Projecttile);
		//	danmaku[i]->Death();
		//}

		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 500; j++)
			{
				pDanmaku[i][j] = new Danmaku();
				playScene->AddGameObject(pDanmaku[i][j], eColliderLayer::Player_Projecttile);
				pDanmaku[i][j]->SetSpeed(1500);
				pDanmaku[i][j]->Death();
			}
		}

		for (size_t j = 0; j < 500; j++)
		{
			pDanmaku[0][j]->mImage = Resources::Load<Image>
				(L"Danmaku_2001", L"..\\Resources\\Image\\Player_Img\\Marisa\\Danmaku_2001.bmp");
			pDanmaku[0][j]->SetSrc(14, 30);

			pDanmaku[1][j]->mImage = Resources::Load<Image>
				(L"Danmaku_2002", L"..\\Resources\\Image\\Player_Img\\Marisa\\Danmaku_2002.bmp");
			pDanmaku[1][j]->SetSrc(14, 17);

			pDanmaku[2][j]->mImage = Resources::Load<Image>
				(L"Danmaku_2003", L"..\\Resources\\Image\\Player_Img\\Marisa\\Danmaku_2003.bmp");
			pDanmaku[2][j]->SetSrc(15,48);
		}

		mCoff = 0.1f;

		for (size_t i = 0; i < 24; i++)
		{
			bombDanmaku[i] = new Danmaku();
			playScene->AddGameObject(bombDanmaku[i], eColliderLayer::Player_Projecttile);
			bombDanmaku[i]->Death();
		}

		for (size_t i = 0; i < 3; i++)
		{
			firePos[i] = Vector2(0.0f, 0.0f);
		}

		fireAngle[0] = Vector2(0.0f, -1.0f);
		fireAngle[1] = Vector2(0.1f, -1.0f);
		fireAngle[2] = Vector2(-0.1f, -1.0f);

		mDanmakuDir = Vector2::One;

	}
	Player::~Player()
	{

	}
	void Player::Tick()
	{
		GameObject::Tick();

		Vector2 pos = GetPos();


		if (bombOnOff == false)
		{
			bombTime += Time::DeltaTime();

			if (bombTime > 5)
			{
				bombOnOff = true;
				bombTime = 0;
			}
		}

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
			nomalTime += Time::DeltaTime();
			bonusTime += Time::DeltaTime();

			if (nomalTime > 0.1f)
			{
				NomalAttack();

				nomalTime = 0;
			}

			if (bonusTime > danmakuTime[1] && KEY_PREESE(eKeyCode::H) == NULL)
			{
				BonusAttack();

				bonusTime = 0;
			}
			else if (bonusTime > danmakuTime[1] && KEY_PREESE(eKeyCode::H) != NULL)
			{
				MiddleAttack();
				
				bonusTime = 0;
			}
		}

		if (KEY_PREESE(eKeyCode::M))
		{
			bombTime += Time::DeltaTime();

			if (bombOnOff)
			{
				BombAttack();

				bombOnOff = false;
			}
		}
		if (KEY_DOWN(eKeyCode::P))
		{
			if (level == 8)
				return;

			DanmakuLevelUP();
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

	void Player::NomalAttack()
	{

		for (size_t i = 0; i < danmakuLevel; i++)
		{
			for (size_t j = 0; j < 1024; j++)
			{
				if (pDanmaku[0][j]->IsDeath() == true && danmakuLevel == 1)
				{
					firePos[0] = GetPos();

					DanmakuReset(pDanmaku[0][j], firePos[i],fireAngle[0]);
					break;
				}
				else if (pDanmaku[0][j]->IsDeath() == true && danmakuLevel == 2)
				{
					firePos[0] = GetPos() + Vector2(20.0f, 0.0f);
					firePos[1] = GetPos() + Vector2(-20.0f, 0.0f);

					DanmakuReset(pDanmaku[0][j], firePos[i], fireAngle[0]);
					break;
				}
				else if (pDanmaku[0][j]->IsDeath() == true && danmakuLevel == 3)
				{
					firePos[0] = GetPos();
					firePos[1] = GetPos();
					firePos[2] = GetPos();

					DanmakuReset(pDanmaku[0][j], firePos[i], fireAngle[i]);
					break;
				}
			}
		}
	}

	void Player::BonusAttack()
	{
		firePos[1] = GetPos() + Vector2(60.0f, 0.0f);
		firePos[2] = GetPos() + Vector2(-60.0f, 0.0f);

		for (size_t i = 0; i < 2; i++)
		{
			for (size_t j = 0; j < 1024; j++)
			{
				if (pDanmaku[1][j]->IsDeath() == true)
				{
					DanmakuReset(pDanmaku[1][j], firePos[i+1],fireAngle[0]);
					break;
				}
			}
		}
	}

	void Player::MiddleAttack()
	{
		firePos[1] = GetPos();

		for (size_t i = 0; i < 2; i++)
		{
		}

		for (size_t j = 0; j < 1024; j++)
		{
			if (pDanmaku[2][j]->IsDeath() == true)
			{
				DanmakuReset(pDanmaku[2][j], firePos[1], fireAngle[0]);
				break;
			}
		}
	}

	void Player::BombAttack()
	{
		firePos[0] = GetPos();

		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				DanmakuReset(bombDanmaku[j + (i* 8)], firePos[0], bombAngle[j]);
				bombDanmaku[j + (i * 8)]->mDestPos = Vector2::One;
				
				mDanmakuDir = math::Rotate(mDanmakuDir, static_cast<float>(i) - 45.0f);
				bombDanmaku[j + (i * 8)]->mDir = mDanmakuDir;
				bombDanmaku[j + (i * 8)]->SetSpeed(BOMBSPEED);
				
			}
		}
	}

	void Player::DanmakuReset(Danmaku* danmaku, Vector2 pos,Vector2 angle)
	{
		Vector2 missileScale = danmaku->GetScale();
		danmaku->SetPos((pos) - (missileScale / 2.0f));
		danmaku->mDir = angle;
		danmaku->Alive();
	}

	void Player::DanmakuLevelUP()
	{
		level++;
		if (level % 2 == 0)
		{
			danmakuTime[1] -= 0.2f;
		}
		if (level % 5 == 3)
		{
			danmakuLevel++;
		}
	}
}