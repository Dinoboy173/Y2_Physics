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
	ApplyForce(a_gravity * GetMass() * a_timeStep);
}

void RigidBody::ResolveCollision(RigidBody* a_actor2)
{
	glm::vec2 normal = glm::normalize(a_actor2->GetPosition() - m_positon);
	glm::vec2 relativeVel = a_actor2->GetVelocity() - m_velocity;

	float elasticity = 1;
	
	// impulse maginitude
	float j = (glm::dot(-(1 + elasticity) * relativeVel, normal)) /
		((1 / m_mass) + (1 / a_actor2->GetMass()));
	
	glm::vec2 force = normal * j;

	float kePre = GetKineticEnergy();
	float otherKePre = a_actor2->GetKineticEnergy();

	ApplyForceActor(a_actor2, force);
}

void RigidBody::ApplyForce(glm::vec2 a_force)
{
	m_velocity += a_force / GetMass();
}

void RigidBody::ApplyForceActor(RigidBody* a_actor2, glm::vec2 a_force)
{
	ApplyForce(-a_force);
	a_actor2->ApplyForce(a_force);
}

float RigidBody::GetKineticEnergy()
{
	float totalEnergy = (m_mass * glm::dot(m_velocity, m_velocity)) / 2;
	
	return totalEnergy;
}