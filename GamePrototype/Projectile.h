#pragma once
#include <utils.h>
#include <vector>

#include <iostream>
class Projectile
{
public:
	Projectile(Point2f startPos, Point2f playerpos);

	void Draw();
	void Update(float elapsedsec);

	Vector2f m_position;
	Vector2f m_velocity;

	Point2f m_playerPos;

	Rectf m_ProjectileHitBox;
	
private:

};

