#include "Trackball.hpp"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glmlv/glfw.hpp>

float Trackball::scrollOffset = 0;

void Trackball::Init(glm::vec3 center, float distance, float speed)
{
    m_Center = center;
	m_fDistance = distance;
    m_speed = 30*speed;

    setViewMatrix();

    glfwSetScrollCallback(m_pWindow, scrollCallback);
}

// Move the camera towards
void Trackball::moveFront(float delta)
{
	m_fDistance -= delta;
}
// Move the center of the camera
void Trackball::moveRight(float delta)
{
    m_Center.x += delta;
}
// Move the center of the camera
void Trackball::moveUp(float delta)
{
    m_Center.y += delta;
}
// Rotate the camera on the X axis
void Trackball::rotateLeft(float degrees)
{
	m_fAngleX += degrees;
}
// Rotate the camera on the Y axis
void Trackball::rotateUp(float degrees)
{
	m_fAngleY += degrees;
}

void Trackball::setViewMatrix()
{
	m_ViewMatrix = glm::lookAt(glm::vec3(m_Center.x, m_Center.y, m_Center.z - m_fDistance), m_Center, glm::vec3(0, -1, 0));
	m_ViewMatrix = glm::rotate(m_ViewMatrix, m_fAngleX, glm::vec3(0, 1, 0));
	m_ViewMatrix = glm::rotate(m_ViewMatrix, m_fAngleY, glm::vec3(1, 0, 0));

    m_RcpViewMatrix = glm::inverse(m_ViewMatrix);
}

void Trackball::setViewMatrix(glm::mat4 matrix)
{
    m_ViewMatrix = matrix;    

    m_RcpViewMatrix = glm::inverse(m_ViewMatrix);
}

// Control the camera
bool Trackball::update(float elapsedTime)
{
    bool hasMoved = false;

	float speed = m_speed * elapsedTime;

    //left mouse button
	if (glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_LEFT) && !m_LeftButtonPressed) {
		m_LeftButtonPressed = true;
		glfwGetCursorPos(m_pWindow, &m_LastCursorPosition.x, &m_LastCursorPosition.y);
	}
	else if (!glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_LEFT) && m_LeftButtonPressed) {
		m_LeftButtonPressed = false;
	}

    //right mouse button
	if (glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_RIGHT) && !m_RightButtonPressed) {
		m_RightButtonPressed = true;
		glfwGetCursorPos(m_pWindow, &m_LastCursorPosition.x, &m_LastCursorPosition.y);
	}
	else if (!glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_RIGHT) && m_RightButtonPressed) {
		m_RightButtonPressed = false;
	}

    //middle mouse button
	if (glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_MIDDLE) && !m_MiddleButtonPressed) {
		m_MiddleButtonPressed = true;
		glfwGetCursorPos(m_pWindow, &m_LastCursorPosition.x, &m_LastCursorPosition.y);
	}
	else if (!glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_MIDDLE) && m_MiddleButtonPressed) {
		m_MiddleButtonPressed = false;
	}

    // left press + drag = Rotation
	if (m_LeftButtonPressed) {
		glm::dvec2 cursorPosition;
		glfwGetCursorPos(m_pWindow, &cursorPosition.x, &cursorPosition.y);
		
		glm::dvec2 delta = cursorPosition - m_LastCursorPosition;
		m_LastCursorPosition = cursorPosition;

		if (delta.x || delta.y)
        {
            rotateLeft(speed * float(delta.x));
            rotateUp(speed * float(delta.y));

			hasMoved = true;
		}
	}

    // right press + drag || middle press + drag = Move Center
	if (m_RightButtonPressed || m_MiddleButtonPressed) {
		glm::dvec2 cursorPosition;
		glfwGetCursorPos(m_pWindow, &cursorPosition.x, &cursorPosition.y);
		
		glm::dvec2 delta = cursorPosition - m_LastCursorPosition;
		m_LastCursorPosition = cursorPosition;

		if (delta.x || delta.y)
        {
            moveRight(speed * float(delta.x));
            moveUp(speed * float(delta.y));

			hasMoved = true;
		}
	}

    // scroll
    if (scrollOffset != 0)
    {
        moveFront(scrollOffset);
        scrollOffset = 0;
        hasMoved = true;
    }

    if (hasMoved)
    {
        setViewMatrix();
    }

	return hasMoved;
}

void Trackball::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    scrollOffset = yoffset;
}
