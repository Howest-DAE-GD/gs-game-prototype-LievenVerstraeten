#pragma once
#include <utils.h>

class Camera
{
public:
	Camera(float cameraWidth, float cameraHeight, float levelW, float levelH);

	void UpdateCamera(const Rectf& playerCenterPos);
	void ViewportTransformation() const;
	void ResetCamera();

private:
	Vector2f m_CameraPos;
	const float m_CameraWidth;
	const float m_CameraHeight;

	const float m_LevelWidth;
	const float m_LevelHeight;



};
