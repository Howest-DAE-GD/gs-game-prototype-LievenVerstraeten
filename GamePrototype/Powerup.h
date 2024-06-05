#pragma once

enum PowerupType
{
	Shield = 0,
	SpeedIsKey = 1,
	Clear = 2

};

class Powerup
{
public:
	Powerup(Point2f spawnPosition, int type);

	void Update(float elapsedSec);
	void Draw();

	float GetLifeTime();
	Circlef GetShape() const;
	PowerupType GetType() const;


private:
	float m_lifeTime{5.f};
	Circlef m_Shape;
	PowerupType m_type;

};

