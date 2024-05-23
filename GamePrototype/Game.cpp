#include "pch.h"
#include "Game.h"

#include "Camera.h"

#include <utils.h>
#include <vector>

#include <iostream>
Game::Game(const Window& window)
	:BaseGame{ window }
{
	Initialize();
	NewOrb();

	//m_CameraPtr = new Camera(GetViewPort().width, GetViewPort().height, 50.f, 50.f);
	//m_CameraPtr->UpdateCamera(m_PlayerPosition);
	m_EnemyPos2 = RandomPos(int(GetViewPort().width - 10), int(GetViewPort().height - 10));
	m_EnemyPos3 = RandomPos(int(GetViewPort().width - 10), int(GetViewPort().height - 10));
	m_EnemyPos4 = RandomPos(int(GetViewPort().width - 10), int(GetViewPort().height - 10));
	m_EnemyPos5 = RandomPos(int(GetViewPort().width - 10), int(GetViewPort().height - 10));
	std::cout << m_EnemyPos2.x << std::endl << m_EnemyPos2.y << std::endl;
}

Game::~Game( )
{
	Cleanup( );
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
	//std::cout << m_PlayerPosition.left << " " << m_PlayerPosition.bottom << "\n";
	if (m_IsGameGoing) Movement(elapsedSec);
	
	//enemy and player colision detection
	if (m_IsGameGoing) CheckCollisions();

	//m_CameraPtr->UpdateCamera(m_PlayerPosition);
	m_ProjectileTime += elapsedSec;
	if (m_ProjectileTime > 1.f)
	{
		m_ProjectileTime -= 1;
		Projectile* bullet = new Projectile{ Point2f{m_EnemyPos1.x + 15, m_EnemyPos1.y + 40}, Point2f{m_PlayerPosition.left + 8, m_PlayerPosition.bottom + 18}};
		m_projectilePtrVector.push_back(bullet);
		if (m_Score > 10)	
		{
			Projectile* bullet2 = new Projectile{ Point2f{m_EnemyPos2.x + 15, m_EnemyPos2.y + 40}, Point2f{m_PlayerPosition.left + 8, m_PlayerPosition.bottom + 18} };
			m_projectilePtrVector.push_back(bullet2);
		}
		if (m_Score > 20)	
		{
			Projectile* bullet3 = new Projectile{ Point2f{m_EnemyPos3.x + 15, m_EnemyPos3.y + 40}, Point2f{m_PlayerPosition.left + 8, m_PlayerPosition.bottom + 18} };
			m_projectilePtrVector.push_back(bullet3);
		}
		if (m_Score > 30)	
		{
			Projectile* bullet4 = new Projectile{ Point2f{m_EnemyPos4.x + 15, m_EnemyPos4.y + 40}, Point2f{m_PlayerPosition.left + 8, m_PlayerPosition.bottom + 18} };
			m_projectilePtrVector.push_back(bullet4);
		}
		if (m_Score > 40)	
		{
			Projectile* bullet5 = new Projectile{ Point2f{m_EnemyPos5.x + 15, m_EnemyPos5.y + 40}, Point2f{m_PlayerPosition.left + 8, m_PlayerPosition.bottom + 18} };
			m_projectilePtrVector.push_back(bullet5);
		}

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
		utils::FillRect(Rectf{m_EnemyPos1.x, m_EnemyPos1.y, 30, 70});
		if (m_Score > 10)	utils::FillRect(Rectf{ m_EnemyPos2.x, m_EnemyPos2.y, 30, 70 });
		if (m_Score > 20)	utils::FillRect(Rectf{ m_EnemyPos3.x, m_EnemyPos3.y, 30, 70 });
		if (m_Score > 30)	utils::FillRect(Rectf{ m_EnemyPos4.x, m_EnemyPos4.y, 30, 70 });
		if (m_Score > 40)	utils::FillRect(Rectf{ m_EnemyPos5.x, m_EnemyPos5.y, 30, 70 });

		utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));
		utils::FillRect(m_Orb0);
		if (m_Score > 10) utils::FillRect(m_Orb1);
		if (m_Score > 20) utils::FillRect(m_Orb2);
		if (m_Score > 30) utils::FillRect(m_Orb3);
		if (m_Score > 40) utils::FillRect(m_Orb4);

		utils::SetColor(Color4f(1.f, 1.f, 0.f, 1.f));
		if (m_GotOrb1 && m_GotOrb2 && m_GotOrb3 && m_GotOrb4) utils::FillRect(m_Altar);

		utils::SetColor(Color4f{ 0.f,0.f,0.f,1.f });
		utils::DrawRect(Rectf{ 0, 0, 1400, 800 }, 10.f);
	}
	//glPopMatrix();
	//m_CameraPtr->ResetCamera();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
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

void Game::Movement(float elapsedSec)
{
	//enemy movement
	

	//if (m_GameWon)
	//{
	//m_Enemy1.left += (m_PlayerPosition.left - m_Enemy1.left ) * elapsedSec * (ENEMY_SPEED / 10000);
	//m_Enemy1.bottom += (m_PlayerPosition.bottom - m_Enemy1.bottom ) * elapsedSec * 2;
	//	if (m_GotOrb2)
	//	{
	//		m_Enemy2.left += (m_PlayerPosition.left - m_Enemy2.left) * elapsedSec * (ENEMY_SPEED / 10000);
	//		m_Enemy2.bottom += (m_PlayerPosition.bottom - m_Enemy2.bottom) * elapsedSec * 2;
	//	}
	//	if (m_GotOrb3)
	//	{
	//		m_Enemy3.left += (m_PlayerPosition.left - m_Enemy3.left) * elapsedSec * (ENEMY_SPEED / 10000);
	//		m_Enemy3.bottom += (m_PlayerPosition.bottom - m_Enemy3.bottom) * elapsedSec * 2;
	//	}
	//	if (m_GotOrb4)
	//	{
	//		m_Enemy4.left += (m_PlayerPosition.left - m_Enemy4.left) * elapsedSec * (ENEMY_SPEED / 10000);
	//		m_Enemy4.bottom += (m_PlayerPosition.bottom - m_Enemy4.bottom) * elapsedSec * 2;
	//	}
	//	if (m_GotOrb1)
	//	{
	//		m_Enemy5.left += (m_PlayerPosition.left - m_Enemy5.left) * elapsedSec * (ENEMY_SPEED / 10000);
	//		m_Enemy5.bottom += (m_PlayerPosition.bottom - m_Enemy5.bottom) * elapsedSec * 2;
	//	}
	//}

	//player movement
	{
		const Uint8* KeyScan = SDL_GetKeyboardState(nullptr);

		const int m_MovementMultiplier{ int(PLAYER_SPEED) };

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
	if (m_Score > 10)	m_Orb1 = Rectf{ m_PlayerPosition.left , m_PlayerPosition.bottom + 60, 10, 10 };
	if (m_Score > 20)	m_Orb2 = Rectf{ m_PlayerPosition.left + 20 , m_PlayerPosition.bottom + 60, 10, 10 };
	if (m_Score > 30)	m_Orb3 = Rectf{ m_PlayerPosition.left , m_PlayerPosition.bottom + 40, 10, 10 };
	if (m_Score > 40)	m_Orb4 = Rectf{ m_PlayerPosition.left + 20 , m_PlayerPosition.bottom + 40, 10, 10 };
}

void Game::CheckCollisions()
{
	/*
	if (utils::IsOverlapping(m_PlayerPosition, m_Enemy1)) m_IsGameGoing = false;
	if (utils::IsOverlapping(m_PlayerPosition, m_Enemy2)) m_IsGameGoing = false;
	if (utils::IsOverlapping(m_PlayerPosition, m_Enemy3)) m_IsGameGoing = false;
	if (utils::IsOverlapping(m_PlayerPosition, m_Enemy4)) m_IsGameGoing = false;*/


	if (utils::IsOverlapping(m_PlayerPosition, m_Orb0)) 
	{
		++m_Score;
		if (IsCheating)m_Score += 4;
		NewOrb();
	}
	//if (utils::IsOverlapping(m_PlayerPosition, m_Orb1)) m_GotOrb1 = true;
	//if (utils::IsOverlapping(m_PlayerPosition, m_Orb2)) m_GotOrb2 = true;
	//if (utils::IsOverlapping(m_PlayerPosition, m_Orb3)) m_GotOrb3 = true;
	//if (utils::IsOverlapping(m_PlayerPosition, m_Orb4)) m_GotOrb4 = true;


	if (m_GotOrb1 && m_GotOrb2 && m_GotOrb3 && m_GotOrb4 && utils::IsOverlapping(m_PlayerPosition, m_Altar)) m_GameWon = true;
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
