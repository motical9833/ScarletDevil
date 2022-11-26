#pragma once
#include "yaGameObject.h"
#include "yaImage.h"
#include "yaAnimator.h"
namespace ya
{
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
		void SetAliveTime(float time) { aliveTime = time; }
		void SetSrc(int w, int h)
		{
			wSrc = w;
			hSrc = h;
		}

	private:
		float mSpeed;
		float aliveTime;
		float mTime;

	public:
		Image* mImage;
		Vector2 mDir;
		Vector2 mDestPos;

		int wSrc;
		int hSrc;
	};
}