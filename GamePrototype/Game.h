#pragma once
#include "BaseGame.h"
#include <utils.h>
#include <vector>
#include "Projectile.h"

class Camera;

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:
	//DATAMEMBERS
	bool m_IsGameGoing{ true };
	Rectf m_PlayerPosition{ 700, 400, 15, 35 };
	Point2f m_EnemyPos1{ 600, 50 };
	Point2f m_EnemyPos2{ 600, 50 };
	Point2f m_EnemyPos3{ 600, 50 };
	Point2f m_EnemyPos4{ 600, 50 };
	Point2f m_EnemyPos5{ 600, 50 };

	std::vector<Rectf> orb;
	std::vector<Projectile*> m_projectilePtrVector;
	float m_ProjectileTime{0};

	int m_Score{0};
	Rectf m_Orb0{};

	Rectf m_Orb1{ -20, -20, 10, 10 };
	Rectf m_Orb2{ -20, -20, 10, 10 };
	Rectf m_Orb3{ -20, -20, 10, 10 };
	Rectf m_Orb4{ -20, -20, 10, 10 };
	bool m_GotOrb1{ false };
	bool m_GotOrb2{ false };
	bool m_GotOrb3{ false };
	bool m_GotOrb4{ false };

	bool m_GameWon{false};
	Rectf m_Altar{ -50, 950, 100, 50 };

	const float PLAYER_SPEED{ 200 };
	const float ENEMY_SPEED{ 8000 };
	bool IsCheating{ false };
	
	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( Color4f BackgroundColor = Color4f{ 0.0f, 0.0f, 0.3f, 1.0f }) const;

	void Movement(float elapsedSec);
	void CheckCollisions();

	void NewOrb();
	void EnemyShoot();
	Point2f RandomPos(int MaxX, int MaxY);
};