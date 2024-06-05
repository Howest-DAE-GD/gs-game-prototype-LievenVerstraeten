#include "pch.h"
#include "Powerup.h"
#include <utils.h>

Powerup::Powerup(Point2f spawnPosition, int type)
	:m_type{PowerupType(type)}, m_Shape{Circlef(spawnPosition, 7.f)}
{
}

void Powerup::Update(float elapsedSec)
{
	m_lifeTime -= elapsedSec;
}

void Powerup::Draw()
{
	if (m_type == Shield) utils::SetColor(Color4f(0.2f, 0.2f, 1.f, 1.f));
	if (m_type == Clear) utils::SetColor(Color4f(0.9f, 0.5f, 0.f, 1.f));
	if (m_type == SpeedIsKey) utils::SetColor(Color4f(0.8f, 0.8f, 0.f, 1.f));
		
	utils::FillEllipse(m_Shape.center,m_Shape.radius,m_Shape.radius);
	utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
	utils::DrawEllipse(m_Shape.center, m_Shape.radius, m_Shape.radius);
}

float Powerup::GetLifeTime()
{
	return m_lifeTime;
}

Circlef Powerup::GetShape() const
{
	return m_Shape;
}

PowerupType Powerup::GetType() const
{
	return m_type;
}
