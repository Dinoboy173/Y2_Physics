#include <iostream>
#include <Gizmos.h>
#include <glm/ext.hpp>

#include "PhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

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

	m_physicsScene->SetTimeStep(0.01f);

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

	m_physicsScene->Update(deltaTime);
	m_physicsScene->Draw();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16.f / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.f, 1.f));

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 10);

	// done drawing sprites
	m_2dRenderer->end();
}