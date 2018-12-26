#include "Camera2D.h"

namespace Bengine
{

	Camera2D::Camera2D() :
		position(0.0f, 0.0f),
		cameraMatrix(1.0f),
		scale(1.0f),
		needsMatrixUpdate(true),
		screenWidth(500),
		screenHeight(500),
		orthoMatrix(1.0f)
	{
	}
	
	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int w, int h)
	{
		screenWidth = w;
		screenHeight = h;

		orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
	}

	void Camera2D::update()
	{
		if (needsMatrixUpdate)
		{
			// Camera translation
			glm::vec3 translateVec(-position.x + screenWidth * 0.5f, -position.y + screenHeight * 0.5f, 0.0f);
			cameraMatrix = glm::translate(orthoMatrix, translateVec);

			// Camera scale
			glm::vec3 scaleVec(scale, scale, 0.0f);
			cameraMatrix = glm::scale(glm::mat4(1.0f), scaleVec) * cameraMatrix;

			needsMatrixUpdate = false;
		}
	}

	void Camera2D::setPosition(glm::vec2 newPos)
	{
		position = newPos;
		needsMatrixUpdate = true;
	}

	void Camera2D::setScale(float ns)
	{
		scale = ns;
		needsMatrixUpdate = true;
	}

	glm::vec2 Camera2D::getPosition()
	{
		return position;
	}

	float Camera2D::getScale()
	{
		return scale;
	}

	glm::mat4 Camera2D::getCameraMatrix()
	{
		return cameraMatrix;
	}
}
