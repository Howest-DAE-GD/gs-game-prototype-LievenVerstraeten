#include "pch.h"
#include "Camera.h"

Camera::Camera(float cameraWidth, float cameraHeight, float levelW, float levelH)
	:m_CameraHeight{ cameraHeight },
	m_CameraWidth{ cameraWidth },
	m_LevelHeight{ levelH },
	m_LevelWidth{ levelW },
	m_CameraPos{ Vector2f{} }

{
}

void Camera::UpdateCamera(const Rectf& playerCenterPos)
{
	m_CameraPos.x = playerCenterPos.left - m_CameraWidth / 2;
	m_CameraPos.y = playerCenterPos.bottom - m_CameraHeight / 2;
	//create an if and else so we can lock the camera for going into the doors

}

void Camera::ViewportTransformation() const
{
	glPushMatrix();
	{
		glTranslatef(-m_CameraPos.x, -m_CameraPos.y, 0);
	}
}

void Camera::ResetCamera()
{
	glPopMatrix();
}