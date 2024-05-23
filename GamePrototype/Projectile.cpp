#include "pch.h"
#include "Projectile.h"
#include <math.h>


Projectile::Projectile(Point2f startPos, Point2f playerpos)
	:m_position{ startPos }, m_playerPos{ playerpos }
{
	m_velocity = -(Point2f{ m_position.x,m_position.y } - m_playerPos);

}

void Projectile::Draw()
{
	utils::SetColor(Color4f{ 0.f, 0.f, 0.f, 1.f });
	utils::FillEllipse(m_position.ToPoint2f(), 5.f, 5.f);
}

void Projectile::Update(float elapsedSec)
{
	m_position.x += m_velocity.x * elapsedSec ;
	m_position.y += m_velocity.y * elapsedSec ;
}
