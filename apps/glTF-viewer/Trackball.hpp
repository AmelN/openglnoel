#pragma once

#include <glm/glm.hpp>

struct GLFWwindow;

class Trackball {
public:
/*
	Trackball(GLFWwindow* window, float distance = 5.f, float hauteur = 0.f, float angleX = 0.f, float angleY = 0.f) :
	m_pWindow(window), m_fDistance(distance), m_fHauteur(hauteur), m_fAngleX(angleX), m_fAngleY(angleY) {}
*/

    Trackball(GLFWwindow* window) : m_pWindow(window) { }

	~Trackball() {}

    static float scrollOffset;

    void Init(glm::vec3 center, float distance, float speed);

    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    void moveFront(float delta); //permettant d'avancer / reculer la caméra. Lorsque delta est positif la caméra doit avancer, sinon elle doit reculer.
    void moveRight(float delta);
    void moveUp(float delta);
    void rotateLeft(float degrees); // permettant de tourner latéralement autour du centre de vision.
    void rotateUp(float degrees); // permettant de tourner verticalement autour du centre de vision.

    void setViewMatrix(); // calcule la ViewMatrix de la caméra

	glm::mat4 getViewMatrix() const
    {
        return m_ViewMatrix;
    }
    glm::mat4 getRcpViewMatrix() const
    {
        return m_RcpViewMatrix;
    }

    bool update(float elapsedTime);

private:
    GLFWwindow* m_pWindow = nullptr;

    float m_speed;

	float m_fDistance;		// Distance par rapport au centre de la scène
	float m_fHauteur;		// Hauteur de la caméra par rapport au centre de la scène
	float m_fAngleX;		// Angle effectuée par la caméra autour de l'axe X de la scène
	float m_fAngleY;		// Angle effectuée par la caméra autour de l'axe Y de la scène

    bool m_LeftButtonPressed = false;
	bool m_RightButtonPressed = false;
	bool m_MiddleButtonPressed = false;

    glm::dvec2 m_LastCursorPosition;

    glm::vec3 m_Center = glm::vec3(0);

    glm::mat4 m_ViewMatrix = glm::mat4(1);
    glm::mat4 m_RcpViewMatrix = glm::mat4(1);
};