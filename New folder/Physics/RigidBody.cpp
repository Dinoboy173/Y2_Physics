#include "RigidBody.h"
#include <iostream>

RigidBody::RigidBody(
	ShapeType a_shapeID, glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass) :
	PhysicsObject(a_shapeID)
{
	m_positon = a_position;
	m_velocity = a_velocity;
	m_rotation = a_rotation;
	m_mass = a_mass;
}

RigidBody::~RigidBody()
{

}

void RigidBody::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
	m_positon += GetVelocity() * a_timeStep;
	ApplyForce(a_gravity * GetMass() * a_timeStep, glm::vec2(0, 0));

	m_rotation += m_angularVelocity * a_timeStep;
}

void RigidBody::ResolveCollision(RigidBody* a_actor2)
{
	
}

void RigidBody::ApplyForce(glm::vec2 a_force, glm::vec2 a_contact)
{
	m_velocity += a_force / GetMass();
	m_angularVelocity += (a_force.y * a_contact.x - a_force.x * a_contact.y) / GetMoment();
}

float RigidBody::GetKineticEnergy()
{
	float totalEnergy = (m_mass * glm::dot(m_velocity, m_velocity)) / 2;
	
	return totalEnergy;
}