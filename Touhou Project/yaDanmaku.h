#pragma once
#include "yaGameObject.h"
#include "yaImage.h"
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

	private:
		float mSpeed;
		float mTime;

	public:
		//Image* image;
		Vector2 mDir;
		Vector2 mDestPos;
	};
}