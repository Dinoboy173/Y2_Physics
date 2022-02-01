#pragma once
#include <glm/glm.hpp>
#include "PhysicsObject.h"
#include <iostream>

class RigidBody : public PhysicsObject
{
public:
	RigidBody(ShapeType a_shapeID, glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass);
	~RigidBody();

	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);
	virtual void Debug() { std::cout << "position: " << m_positon.x << ', ' << m_positon.y << std::endl; }
	virtual bool CheckCollision(PhysicsObject* pOther) = 0;

	void ApplyForce(glm::vec2 a_force);
	void ApplyForceActor(RigidBody* a_actor2, glm::vec2 a_force);

	glm::vec2 GetPosition() { return m_positon; }
	glm::vec2 GetVelocity() { return m_velocity; }
	float GetRotation() { return m_rotation; }
	float GetMass() { return m_mass; }

	void SetMass(float a_mass) { m_mass = a_mass; }

protected:
	glm::vec2 m_positon;
	glm::vec2 m_velocity;
	float m_rotation; // In 2D we only need a single float
	float m_mass;

};

