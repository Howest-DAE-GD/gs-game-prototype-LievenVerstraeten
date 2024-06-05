#include "pch.h"
#include "Game.h"

#include "Camera.h"

#include <utils.h>
#include <vector>

#include <iostream>
Game::Game(const Window& window)
	:BaseGame{ window }, m_GameOverText(new Texture("Game Over", "Coffee Spark.otf", 100, Color4f(1.f,0.f,0.f,1.f))), 
	m_TryAgain(new Texture("Try again by pressing r dumbass", "Coffee Spark.otf", 50, Color4f(1.f, 0.f, 0.f, 1.f))),
	m_GameWonText(new Texture("You won", "Coffee Spark.otf", 120, Color4f(0.f, 0.8f, 0.f, 1.f))),
	m_Shield{0.f,0.f, 17.f, 37.f}
{
	Initialize();
	Restart();
	std::cout << m_EnemyPos2.x << std::endl << m_EnemyPos2.y << std::endl;

}

Game::~Game( )
{
	Cleanup( );
}

void Game::SpawnPowerup()
{
	m_powerupPtrVector.push_back(new Powerup{ RandomPos(int(GetViewPort().width - 10), int(GetViewPort().height - 10)), rand() % 3 });
}

void Game::DecreasePowerupTimer(float elapsedSec)
{
	m_PowerSpawnTimer -= elapsedSec;
	if (m_PowerSpawnTimer < 0)
	{
		SpawnPowerup();
		m_PowerSpawnTimer = rand() % 10 + 5;
	}
}

void Game::Initialize( )
{
}

void Game::Cleanup( )
{

	for (int index{ 0 }; index < m_projectilePtrVector.size(); ++index)
	{
		delete m_projectilePtrVector[index];
	}

	
	//delete m_CameraPtr;
	//m_CameraPtr = nullptr;
}

void Game::Update( float elapsedSec )
{
	shakeStartTime += elapsedSec;
	if (flashingIntensity > 0) flashingIntensity -= 0.01;
	if (shakeStartTime > shakeDuration )
	{
		shakeIntensity = 0;
	}

	if (!m_Died)
	{
		DecreasePowerupTimer(elapsedSec);
		for (int powerupIndex = 0; powerupIndex < m_powerupPtrVector.size(); powerupIndex++)
		{
			if (m_powerupPtrVector.at(powerupIndex) == nullptr)
				continue;
			m_powerupPtrVector[powerupIndex]->Update(elapsedSec);
			if (m_powerupPtrVector[powerupIndex]->GetLifeTime() < 0)
			{
				//m_powerupPtrVector[powerupIndex] = m_powerupPtrVector[m_powerupPtrVector.size() - 1];
				//delete m_powerupPtrVector[m_powerupPtrVector.size() - 1];
				//m_projectilePtrVector.pop_back();
				delete m_powerupPtrVector.at(powerupIndex);
				m_powerupPtrVector.at(powerupIndex) = nullptr;

			}
		}

	//std::cout << m_PlayerPosition.left << " " << m_PlayerPosition.bottom << "\n";
	if (m_IsGameGoing) Movement(elapsedSec);
	
	//enemy and player colision detection
	if (m_IsGameGoing) CheckCollisions();



	if (0 <= m_Score && m_Score <= 5)
	{
		m_Orb1.height = m_Score * 2;
	}
	if (5 < m_Score && m_Score <= 10)
	{
		int score = m_Score - 5;
		m_Orb2.height = score * 2;
	}
	if (10 < m_Score && m_Score <= 15)
	{
		int score1 = m_Score - 10;
		m_Orb3.height = score1 * 2;
	}
	if (15 < m_Score && m_Score <= 20)
	{
		int score2 = m_Score - 15;
		m_Orb4.height = score2 * 2;
	}
	if (20 < m_Score && m_Score <= 25)
	{
		int score3 = m_Score - 20;
		m_Orb5.height = score3 * 2;
	}

	if (m_IsGameGoing)
	{
		DecreaseMovementModifierTimer(elapsedSec);
		//m_CameraPtr->UpdateCamera(m_PlayerPosition);
		m_ProjectileTime += elapsedSec;
		if (m_ProjectileTime > 1.f)
		{
			m_ProjectileTime -= 1;
			Projectile* bullet = new Projectile{ Point2f{m_EnemyPos1.x + 15, m_EnemyPos1.y + 40}, Point2f{m_PlayerPosition.left + 8, m_PlayerPosition.bottom + 18} };
			m_projectilePtrVector.push_back(bullet);
			if (m_Score > 5)
			{
				Projectile* bullet2 = new Projectile{ Point2f{m_EnemyPos2.x + 15, m_EnemyPos2.y + 40}, Point2f{m_PlayerPosition.left + 8, m_PlayerPosition.bottom + 18} };
				m_projectilePtrVector.push_back(bullet2);
			}
			if (m_Score > 10)
			{
				Projectile* bullet3 = new Projectile{ Point2f{m_EnemyPos3.x + 15, m_EnemyPos3.y + 40}, Point2f{m_PlayerPosition.left + 8, m_PlayerPosition.bottom + 18} };
				m_projectilePtrVector.push_back(bullet3);
			}
			if (m_Score > 15)
			{
				Projectile* bullet4 = new Projectile{ Point2f{m_EnemyPos4.x + 15, m_EnemyPos4.y + 40}, Point2f{m_PlayerPosition.left + 8, m_PlayerPosition.bottom + 18} };
				m_projectilePtrVector.push_back(bullet4);
			}
			if (m_Score > 20)
			{
				Projectile* bullet5 = new Projectile{ Point2f{m_EnemyPos5.x + 15, m_EnemyPos5.y + 40}, Point2f{m_PlayerPosition.left + 8, m_PlayerPosition.bottom + 18} };
				m_projectilePtrVector.push_back(bullet5);
			}
		}
	}
	UpdateShield(elapsedSec);
	}

	for (int index { 0 }; index < m_projectilePtrVector.size(); ++index)
	{
		m_projectilePtrVector[index]->Update(elapsedSec);
	}
	

	
	/*if (playerPosX - playerSize / 2 < e1PosX - e1Size / 2 + e1Size &&
		playerPosX - playerSize / 2 + playerSize > e1PosX - e1Size / 2 &&
		playerPosY - playerSize / 2 < e1PosY - e1Size / 2 + e1Size &&
		playerPosY - playerSize / 2 + playerSize > e1PosY - e1Size / 2)
	{
		playerPosX = (screenWidth / 2);
		playerPosY = screenHeigth / 2;
		gameState = 2;
	}*/
}

void Game::Draw( ) const
{

	ClearBackground( Color4f{0.8f,0.8f,0.8f,1.f});
	FlashingScreen();
	glPushMatrix();
	ShakeScreen();
	if ( !m_Died && m_IsGameGoing)
	{
	for (int index{ 0 }; index < m_projectilePtrVector.size(); ++index)
	{
		m_projectilePtrVector[index]->Draw();
	}
	//m_CameraPtr->ViewportTransformation();
	//glPushMatrix();
	{
		utils::SetColor(Color4f(0.4f, 0.f, 0.f, 1.f));
		utils::FillRect(m_PlayerPosition);

		utils::SetColor(Color4f(0.1f, 0.1f, 0.7f, 1.f));
		utils::FillRect(Rectf{ m_EnemyPos1.x, m_EnemyPos1.y, 30, 70 });
		if (m_Score > 5)	utils::FillRect(Rectf{ m_EnemyPos2.x, m_EnemyPos2.y, 30, 70 });
		if (m_Score > 10)	utils::FillRect(Rectf{ m_EnemyPos3.x, m_EnemyPos3.y, 30, 70 });
		if (m_Score > 15)	utils::FillRect(Rectf{ m_EnemyPos4.x, m_EnemyPos4.y, 30, 70 });
		if (m_Score > 20)	utils::FillRect(Rectf{ m_EnemyPos5.x, m_EnemyPos5.y, 30, 70 });


		utils::SetColor(Color4f(1.f, 1.f, 0.f, 1.f));
		if (m_Score > 24)	utils::FillRect(m_Altar);

		for (int powerupIndex = 0; powerupIndex < m_powerupPtrVector.size(); powerupIndex++)
		{
			if (m_powerupPtrVector.at(powerupIndex) == nullptr)
				continue;
			m_powerupPtrVector[powerupIndex]->Draw();
		}

		DrawShield();


		utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));
		if (m_Score > 24)	utils::DrawRect(m_Altar, 5);


		
		utils::FillRect(m_Orb0);

		utils::FillRect(m_Orb1);
		if (m_Score > 5)  utils::FillRect(m_Orb2);
		if (m_Score > 10) utils::FillRect(m_Orb3);
		if (m_Score > 15) utils::FillRect(m_Orb4);
		if (m_Score > 20) utils::FillRect(m_Orb5);

		utils::SetColor(Color4f(0.f, 0.5f, 0.f, 1.f));

		if (m_Score >= 5)  utils::DrawRect(m_Orb1);
		if (m_Score >= 10) utils::DrawRect(m_Orb2);
		if (m_Score >= 15) utils::DrawRect(m_Orb3);
		if (m_Score >= 20) utils::DrawRect(m_Orb4);
		if (m_Score >= 25) utils::DrawRect(m_Orb5);


		utils::SetColor(Color4f{ 0.f,0.f,0.f,1.f });
		utils::DrawRect(Rectf{ 0, 0, 1400, 800 }, 10.f);
	}
	}
	//glPopMatrix();
	//m_CameraPtr->ResetCamera();
	if (m_Died)
	{
		m_GameOverText->Draw(Point2f{GetViewPort().width / 2 - m_GameOverText->GetWidth() / 2, 400});
		m_TryAgain->Draw(Point2f{ GetViewPort().width / 2 - m_TryAgain->GetWidth() / 2, 300 });
	}

	if (!m_IsGameGoing)
	{
		m_GameWonText->Draw(Point2f{ GetViewPort().width / 2 - m_GameOverText->GetWidth() / 2, 400 });
		m_TryAgain->Draw(Point2f{ GetViewPort().width / 2 - m_TryAgain->GetWidth() / 2, 300 });
	}
	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_l:
		++m_Score;
		break;
	case SDLK_r:
		if (m_Died or !m_IsGameGoing)
		{
			Restart();
		}
		break;
	case SDLK_b:
		SpawnPowerup();
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground(Color4f BackgroundColor) const
{
	glClearColor( BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, BackgroundColor.a);
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::Restart()
{
	m_Died = false;
	m_IsGameGoing = true;
	m_Score = 0;
	NewOrb();
	m_PowerSpawnTimer = rand() % 10 + 5;


	for (int powerupIndex = 0; powerupIndex < m_powerupPtrVector.size(); powerupIndex++)
	{
			delete m_powerupPtrVector.at(powerupIndex);
			m_powerupPtrVector.at(powerupIndex) = nullptr;
		
	}
	m_powerupPtrVector.clear();

	ClearProjectiles();


	m_Altar = Rectf(float(rand() % 1350), float(rand() % 760), 50, 40);
	m_EnemyPos1 = RandomPos(int(GetViewPort().width - 30), int(GetViewPort().height - 70));
	m_EnemyPos2 = RandomPos(int(GetViewPort().width - 30), int(GetViewPort().height - 70));
	m_EnemyPos3 = RandomPos(int(GetViewPort().width - 30), int(GetViewPort().height - 70));
	m_EnemyPos4 = RandomPos(int(GetViewPort().width - 30), int(GetViewPort().height - 70));
	m_EnemyPos5 = RandomPos(int(GetViewPort().width - 30), int(GetViewPort().height - 70));
}

void Game::Movement(float elapsedSec)
{
	//enemy movement
	

	

	//player movement
	{
		const Uint8* KeyScan = SDL_GetKeyboardState(nullptr);

		const int m_MovementMultiplier{ int(PLAYER_SPEED) * movementModifier };

		const bool UP{ bool(KeyScan[SDL_SCANCODE_W]) };
		const bool DOWN{ bool(KeyScan[SDL_SCANCODE_S]) };
		const bool LEFT{ bool(KeyScan[SDL_SCANCODE_A]) };
		const bool RIGHT{ bool(KeyScan[SDL_SCANCODE_D]) };
		const bool P{ bool(KeyScan[SDL_SCANCODE_P]) };

		if (UP)
		{
			m_PlayerPosition.bottom += 1 * elapsedSec * m_MovementMultiplier;
			if (LEFT) m_PlayerPosition.left -= 1 * elapsedSec * m_MovementMultiplier;

			else if (RIGHT) m_PlayerPosition.left += 1 * elapsedSec * m_MovementMultiplier;
		}
		else if (DOWN)
		{
			m_PlayerPosition.bottom -= 1 * elapsedSec * m_MovementMultiplier;
			if (LEFT) m_PlayerPosition.left -= 1 * elapsedSec * m_MovementMultiplier;

			else if (RIGHT) m_PlayerPosition.left += 1 * elapsedSec * m_MovementMultiplier;
		}
		else if (LEFT) m_PlayerPosition.left -= 1 * elapsedSec * m_MovementMultiplier;
		else if (RIGHT) m_PlayerPosition.left += 1 * elapsedSec * m_MovementMultiplier;
		else if (P) IsCheating = true;
		if (m_PlayerPosition.bottom > GetViewPort().bottom + GetViewPort().height) m_PlayerPosition.bottom = GetViewPort().bottom - 30;
		if (m_PlayerPosition.bottom < GetViewPort().bottom - 30) m_PlayerPosition.bottom = GetViewPort().bottom + GetViewPort().height;
		if (m_PlayerPosition.left > GetViewPort().left + GetViewPort().width) m_PlayerPosition.left = GetViewPort().left;
		if (m_PlayerPosition.left < GetViewPort().left) m_PlayerPosition.left = GetViewPort().left + GetViewPort().width;
		//else m_Velocity = Vector2f(0, 0) * elapsedSec;
	}
	 
	
	//orb movement
	m_Orb1 = Rectf{ m_PlayerPosition.left - 15 , m_PlayerPosition.bottom + 30, 10, m_Orb1.height};
	m_Orb3 = Rectf{ m_PlayerPosition.left - 15 , m_PlayerPosition.bottom + 15, 10, m_Orb2.height};
	m_Orb4 = Rectf{ m_PlayerPosition.left + 20 , m_PlayerPosition.bottom + 15, 10, m_Orb3.height};
	m_Orb2 = Rectf{ m_PlayerPosition.left + 20 , m_PlayerPosition.bottom + 30, 10, m_Orb4.height};
	m_Orb5 = Rectf{ m_PlayerPosition.left + 2  , m_PlayerPosition.bottom + 40, 10, m_Orb5.height};
}

void Game::CheckCollisions()
{
	/*
	if (utils::IsOverlapping(m_PlayerPosition, m_Enemy1)) m_IsGameGoing = false;
	if (utils::IsOverlapping(m_PlayerPosition, m_Enemy2)) m_IsGameGoing = false;
	if (utils::IsOverlapping(m_PlayerPosition, m_Enemy3)) m_IsGameGoing = false;
	if (utils::IsOverlapping(m_PlayerPosition, m_Enemy4)) m_IsGameGoing = false;*/

	PowerupCollision();

	for (int bulletIndex = 0; bulletIndex < m_projectilePtrVector.size(); ++bulletIndex)
	{
		if (m_projectilePtrVector.at(bulletIndex) == nullptr)
			continue;
		if (utils::IsPointInRect(m_projectilePtrVector[bulletIndex]->m_position.ToPoint2f(),m_PlayerPosition))
		{
			if (m_IsShieldOn) {
				DamageShield();
			}
			else if (m_Score > 4)
			{
				m_Score -= 5;
				//m_projectilePtrVector[bulletIndex] = m_projectilePtrVector[m_projectilePtrVector.size()-1];
				//delete m_projectilePtrVector[bulletIndex];
				//m_projectilePtrVector.pop_back();
				ShakeScreen(5);
				FlashingScreen(0.8f);
			}
			else
			{
				m_Died = true;
				FlashingScreen(1.f);
			}
			m_projectilePtrVector[bulletIndex] = m_projectilePtrVector[m_projectilePtrVector.size() - 1];
			m_projectilePtrVector.pop_back();

		}
	}

	if (utils::IsOverlapping(m_PlayerPosition, m_Orb0)) 
	{
		++m_Score;
		if (IsCheating)m_Score += 4;
		NewOrb();
		if (m_Score > 25) m_Score = 25;
	}
	//if (utils::IsOverlapping(m_PlayerPosition, m_Orb1)) m_GotOrb1 = true;
	//if (utils::IsOverlapping(m_PlayerPosition, m_Orb2)) m_GotOrb2 = true;
	//if (utils::IsOverlapping(m_PlayerPosition, m_Orb3)) m_GotOrb3 = true;
	//if (utils::IsOverlapping(m_PlayerPosition, m_Orb4)) m_GotOrb4 = true;


	if (m_Score > 24 && utils::IsOverlapping(m_PlayerPosition, m_Altar)) GameWon();
}

void Game::NewOrb()
{
	Point2f NewPosition{  RandomPos(int(GetViewPort().width-10) , int(GetViewPort().height-10)) };
	m_Orb0 = Rectf{ NewPosition.x,NewPosition.y, 10, 10 };
	if (utils::IsOverlapping(m_PlayerPosition, m_Orb0)) NewOrb();
	std::cout << m_Score << std::endl;
}

Point2f Game::RandomPos(int MaxX, int MaxY)
{
	return Point2f{ float(rand() % MaxX), float ( rand() % MaxY) };
}

void Game::ChangeMovementModifier(int modifier)
{
	movementModifier = modifier;
}

void Game::GameWon()
{
	m_IsGameGoing = false;
	FlashingScreen(1.f);
	for (int index{ 0 }; index < m_projectilePtrVector.size(); ++index)
	{
		delete m_projectilePtrVector[index];
	}
	m_projectilePtrVector.clear();


}

void Game::DecreaseMovementModifierTimer(float elapsedSec)
{
	if (m_movementModifierTimer < 0)
	{
		ChangeMovementModifier(1);
	}
	else
	{
		m_movementModifierTimer -= elapsedSec;
	}
}

void Game::FlashingScreen() const
{
	utils::SetColor(Color4f{ 1.f, 0.f, 0.f, flashingIntensity });
	if (!m_IsGameGoing) utils::SetColor(Color4f{ 0.f, 1.f, 0.f, flashingIntensity });
	utils::FillRect(Rectf{ 0, 0, GetViewPort().width, GetViewPort().height });
}

void Game::FlashingScreen(float intensity)
{
	flashingIntensity = intensity;
	flashingStartTime = 0;
}

void Game::EnableShield(bool IsEnabled)
{
	if (IsEnabled)
	{
		m_ShieldDurability = 2;
	}
		m_IsShieldOn = IsEnabled;
	
}

void Game::DrawShield() const
{
	if (!m_IsShieldOn) return;
	utils::SetColor(m_ShieldColor);
	utils::DrawEllipse(m_Shield, 4.f);
}

void Game::UpdateShield(float elapsedSec)
{
	if (m_ShieldDurability == 2) m_ShieldColor = Color4f(0.f, 0.f, 1.f, 0.8f);
	if (m_ShieldDurability == 1) m_ShieldColor = Color4f(0.8f, 0.5f, 0.f, 0.8f);
	m_Shield.center.x = m_PlayerPosition.left + m_PlayerPosition.width/2;
	m_Shield.center.y = m_PlayerPosition.bottom + m_PlayerPosition.height/2;

}

void Game::DamageShield()
{
	m_ShieldDurability -= 1;
	if (m_ShieldDurability == 0)
	{
		EnableShield(false);
		ShakeScreen(3);
		return;
	}
	ShakeScreen(1);
}

void Game::PowerupCollision()
{

	for (int powerupIndex = 0; powerupIndex < m_powerupPtrVector.size(); powerupIndex++)
	{
		if (m_powerupPtrVector.at(powerupIndex) == nullptr)
		{
			continue;
		}
		auto powerup = m_powerupPtrVector.at(powerupIndex);
		if (utils::IsOverlapping(m_PlayerPosition, powerup->GetShape()))
		{
			switch (powerup->GetType())
			{
			case PowerupType::Shield:
				EnableShield(true);
				break;
			case PowerupType::Clear: 
				ClearProjectiles();
				break;
			case PowerupType::SpeedIsKey:
				ChangeMovementModifier(2);
				m_movementModifierTimer = 5;
				break;
			default:
				break;
			}
			delete m_powerupPtrVector.at(powerupIndex);
			m_powerupPtrVector.at(powerupIndex) = nullptr;

		}

	}
}

void Game::ClearProjectiles()
{
	for (int index{ 0 }; index < m_projectilePtrVector.size(); ++index)
	{
		delete m_projectilePtrVector[index];
	}
	m_projectilePtrVector.clear();
}

void Game::ShakeScreen(float intensity)
{
	shakeIntensity = intensity;
	shakeStartTime = 0;
}

void Game::ShakeScreen() const
{
	if (shakeIntensity > 0)
	{
		int maxIntensity = 2 * shakeIntensity;
		float dx = rand() % maxIntensity - shakeIntensity;
		float dy = rand() % maxIntensity - shakeIntensity;

		glTranslatef(dx, dy, 0);
	}
}
