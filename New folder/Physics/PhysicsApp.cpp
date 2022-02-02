#include <iostream>
#include <Gizmos.h>
#include <glm/ext.hpp>

#include "PhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Circle.h"
#include "Plane.h"

#define _USE_MATH_DEFINES
#include <math.h>

PhysicsApp::PhysicsApp()
{

}

PhysicsApp::~PhysicsApp()
{

}

bool PhysicsApp::startup() {

	// Increase the 2d line count to maximise the number of objects we can draw

	aie::Gizmos::create(255U, 255U, 65535U, 65535U);
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();

	/* The lower the value the more accurate the simulation will be. 
	   but it will increase the processing time required. If it is too high
	   it will cause the sim to stutter and reduce the stability */

	m_physicsScene->SetGravity(glm::vec2(0, 0));
	m_physicsScene->SetTimeStep(0.01f);

	CreatePlane();

	//CollisionDetectionTest();
	
	Circle* ball1 = CreateCircle(glm::vec2(-20, 0), glm::vec2(0, 0), 1.7f, 4.f, glm::vec4(1, 1, 1, 1), glm::vec2(11.11f, 0));
	Circle* ball2 = CreateCircle(glm::vec2(10, 0),  glm::vec2(0, 0), 1.6f, 4.f, glm::vec4(0, 1, 0, 1), glm::vec2(0, 0));

	return true;
}

void PhysicsApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void PhysicsApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	// if (rocket->GetMass() > 1)
	// {
	// 	if (timer <= 0)
	// 	{
	// 		MoveRocket(rocket);
	// 		//MoveRocket(rocket2);
	// 		timer = timerReset;
	// 	}
	// 	else if (timer > 0)
	// 		timer -= deltaTime;
	// }
	
	m_physicsScene->Update(deltaTime);
	m_physicsScene->Draw();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

// void PhysicsApp::MoveRocket(Circle* a_rocket)
// {
// 	Circle* fuel = CreateCircle(
// 		a_rocket->GetPosition() - glm::vec2(0, 4.5f),
// 		glm::vec2(0, 0),
// 		1.f,
// 		0.4f,
// 		glm::vec4(0, 1, 0, 1),
// 		glm::vec2(0, -1));
// 
// 	a_rocket->SetMass(rocket->GetMass() - 1.f);
// 	a_rocket->ApplyForce(glm::vec2(0, 12.5f));
// }

void PhysicsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16.f / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.f, 1.f));

	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 10);

	// done drawing sprites
	m_2dRenderer->end();
}

Circle* PhysicsApp::CreateCircle(glm::vec2 a_pos, glm::vec2 a_vel, float a_mass, float a_radius, glm::vec4 a_colour, glm::vec2 a_force)
{
	Circle* circle = new Circle(a_pos, a_vel, a_mass, a_radius, a_colour);

	m_physicsScene->AddActor(circle);

	circle->ApplyForce(a_force);

	return circle;
}

void PhysicsApp::CreatePlane()
{
	// Plane* testPlane1 = new Plane(glm::vec2(1, 0), -40,  glm::vec4(0, 1, 0, 1)); // left
	// Plane* testPlane2 = new Plane(glm::vec2(-1, 0), -40, glm::vec4(0, 1, 0, 1)); // right
	// Plane* testPlane3 = new Plane(glm::vec2(0, 1), -40,  glm::vec4(0, 1, 0, 1)); // bottom
	// Plane* testPlane4 = new Plane(glm::vec2(1, 1), -32,  glm::vec4(0, 1, 0, 1)); // bottom left
	// Plane* testPlane5 = new Plane(glm::vec2(-1, 1), -32, glm::vec4(0, 1, 0, 1)); // bottom right
	// 
	// m_physicsScene->AddActor(testPlane1);
	// m_physicsScene->AddActor(testPlane2);
    // m_physicsScene->AddActor(testPlane3);
	// m_physicsScene->AddActor(testPlane4);
	// m_physicsScene->AddActor(testPlane5);
}

void PhysicsApp::CollisionDetectionTest()
{
	m_physicsScene->SetGravity(glm::vec2(0, -9.82f));

	Plane* plane = new Plane(glm::vec2(0, 1), -30, glm::vec4(0, 1, 0, 1));

	m_physicsScene->AddActor(plane);
}