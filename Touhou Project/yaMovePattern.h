#pragma once
#include "Common.h"
#include "yaTime.h"

namespace ya
{
	namespace movePattern
	{
		void WidthMove(float direction, Vector2& enemyPos, bool& moveBool)
		{
			if (moveBool != true)
				return;

			enemyPos.x += direction * Time::DeltaTime();
		}
		void VerticalMove(float direction, Vector2& enemyPos, bool& moveBool)
		{
			if (moveBool != true)
				return;

			enemyPos.y += direction * Time::DeltaTime();
		}
		void CircleMove(float speed, Vector2& enemyPos,bool& moveBool,float& deg, float& circleR)
		{
			if (moveBool != true)
				return;

			deg += Time::DeltaTime() * speed;
			if (deg < 360)
			{
				float rad = math::DegreeToRadian(deg);
				float x = circleR * sinf(rad);
				float y = circleR * cosf(rad);

				enemyPos.x += x;
				enemyPos.y += y;
			}
			else
			{
				deg = 0;
			}
		}
		void CoordinateMove(const float& speed, Vector2 targetPos, Vector2& enemyPos, bool& moveBool)
		{
			if (moveBool != true)
				return;

			//정확한 거리x
			int distance = math::Distance(enemyPos, targetPos);

			if (distance <= 20)
			{
				enemyPos = targetPos;
				moveBool = false;
				return;
			}
			else
			{
				Vector2 dir = enemyPos - targetPos;
				dir = Vector2::MinusOne * dir;
				dir.Normailize();

				enemyPos.y += speed * dir.y * Time::DeltaTime();
				enemyPos.x += speed * dir.x * Time::DeltaTime();
			}
		}
	}

	namespace ChenNomalAttack
	{
		void NomalAttack_A(bool boolctr)
		{
			if (boolctr != true)
				return;

			int a = 0;

			for (size_t i = 0; i < 6; i++)
			{
				a++;
			}

		}
	}
}

