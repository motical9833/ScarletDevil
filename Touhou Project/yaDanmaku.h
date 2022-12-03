#pragma once
#include "yaGameObject.h"
#include "yaImage.h"
#include "yaAnimator.h"

namespace ya
{
	//enum class STATE
	//{
	//	Nomal,
	//	Chen,
	//	End,
	//};

	class Danmaku : public GameObject
	{
	public:
		Danmaku();
		~Danmaku();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;



		void SetSpeed(float speed) { mSpeed = speed; }
		void SetStop(float time, float speed) { stopTime = time; stopBool = true; slowSpeed = speed; }
		void SetAliveTime(float time) { aliveTime = time; }
		void SetMoveTime(float time) { reMoveTime = time; }
		void SetRemoveSpeed(float speed) { reMoveSPeed = speed; }
		void SetPlusDir(Vector2 dir) { plusDir = dir; }
		void SetRotBool(bool onoff) { rotBool = onoff; }

		void DanmakuDeath();
		void DanmakuStopMove(bool stop);
		void RemoveDanmaku(float speed,bool cnt);
		void RotationDanmaku();

		void SetSrc(int w, int h)
		{
			wSrc = w;
			hSrc = h;
		}

	private:
		bool rotBool;

		float mSpeed;
		float aliveTime;
		float mTime;
		Vector2 plusDir;

	public:
		Image* mImage;
		Vector2 mDir;
		Vector2 mDestPos;

		int wSrc;
		int hSrc;

		int a;

		float slowSpeed;
		float stopTime;
		float nextMoveTime;

		bool stopBool;
		float reMoveTime;
		float reMoveSPeed;
		//STATE state;
	};
}