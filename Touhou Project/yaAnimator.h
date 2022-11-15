#pragma once
#include "yaComponent.h"
#include "yaAnimation.h"


namespace ya
{
	class Image; 
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator+=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}

			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}

			void operator()()
			{
				if (mEvent)
					mEvent();
			}


			std::function<void()>mEvent;
		};
		struct Events
		{
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;
		};


		Animator();
		~Animator();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		Animation* FindAnimation(const std::wstring& name);

		void CreateAnimation(const std::wstring& name,Image* image
			,Vector2 leftTop,Vector2 size,Vector2 offset
			,UINT spriteLegth,float duration,bool bAffectedCamera = false);

		void Play(const std::wstring& name,bool bLoop = false);

		Events* FindEvevts(const std::wstring key);

		std::function<void()>& GetStartEvent(const std::wstring key);
		std::function<void()>& GetCompleteEvent(const std::wstring key);
		std::function<void()>& GetEndEvent(const std::wstring key);
	public:



	private:
		Image* mImage;

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;


		Animation* mPlayAnimation;
		bool mbLoop;
	};

}