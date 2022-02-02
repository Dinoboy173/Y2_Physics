#pragma once

#include "Application.h"
#include "Renderer2D.h"

#include "PhysicsScene.h"

class Circle;

class PhysicsApp : public aie::Application {
public:

	PhysicsApp();
	virtual ~PhysicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	PhysicsScene* m_physicsScene;

	float timer = 0.f;
	float timerReset = 0.1f;

//====================
public:
	Circle* CreateCircle(glm::vec2 a_pos, glm::vec2 a_vel, float a_mass, float a_radius, glm::vec4 a_colour, glm::vec2 a_force);
	
	void CreatePlane();

	void CollisionDetectionTest();

};