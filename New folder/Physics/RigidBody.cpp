#include "RigidBody.h"

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
	ApplyForce(a_gravity * GetMass() * a_timeStep);
	m_positon += GetVelocity() * a_timeStep;
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
