#pragma once
#include "BaseGame.h"
#include <utils.h>
#include <vector>
#include "Projectile.h"
#include <Texture.h>
#include "Powerup.h"

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


	Rectf m_Altar{ 500, 500, 50, 40};
	//std::vector<Rectf> orb;
	std::vector<Projectile*> m_projectilePtrVector;
	float m_ProjectileTime{0};

	std::vector<Powerup*> m_powerupPtrVector;
	void SpawnPowerup();
	void DecreasePowerupTimer(float elapsedSec);
	float m_PowerSpawnTimer;

	int m_Score{0};
	Rectf m_Orb0{};

	Rectf m_Orb1{ -20, -20, 10, 0 };
	Rectf m_Orb2{ -20, -20, 10, 0 };
	Rectf m_Orb3{ -20, -20, 10, 0 };
	Rectf m_Orb4{ -20, -20, 10, 0 };
	Rectf m_Orb5{ -20, -20, 10, 0 };
	bool m_GotOrb1{ false };
	bool m_GotOrb2{ false };
	bool m_GotOrb3{ false };
	bool m_GotOrb4{ false };
	bool m_GotOrb5{ false };

	bool m_GameWon{false};
	bool m_Died{ false };

	const float PLAYER_SPEED{ 200 };
	int movementModifier{ 1 };
	float m_movementModifierTimer{};
	const float ENEMY_SPEED{ 8000 };
	bool IsCheating{ false };

	void ChangeMovementModifier(int modifier);
	void DecreaseMovementModifierTimer(float elapsedSec);
	
	void Initialize();
	void Cleanup( );
	void ClearBackground( Color4f BackgroundColor = Color4f{ 0.0f, 0.0f, 0.3f, 1.0f }) const;

	void Movement(float elapsedSec);
	void CheckCollisions();

	void Restart();
	void GameWon();

	void NewOrb();
	Point2f RandomPos(int MaxX, int MaxY);

	float shakeIntensity{ 0 };
	float shakeDuration{ 0.3 };
	float shakeStartTime{ 0 };
	void ShakeScreen() const;
	void ShakeScreen(float intensity);
	float flashingIntensity{ 0 };
	float flashingDuration{0.3};
	float flashingStartTime{ 0 };
	void FlashingScreen() const;
	void FlashingScreen(float intensity);



	Texture* m_GameOverText;
	Texture* m_TryAgain;
	Texture* m_GameWonText;

	Ellipsef m_Shield{};
	Color4f m_ShieldColor{ Color4f(0.f, 0.f, 1.f, 0.8f) };
	int m_ShieldDurability{2};
	bool m_IsShieldOn{false};
	void EnableShield(bool IsEnabled);
	void DrawShield() const;
	void UpdateShield(float elapsedSec);
	void DamageShield();

	void PowerupCollision();
	void ClearProjectiles();

};