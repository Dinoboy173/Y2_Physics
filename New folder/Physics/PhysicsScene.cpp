#include <list>
#include <iostream>

#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "RigidBody.h"
#include "Circle.h"

PhysicsScene::PhysicsScene() :
	m_timeStep(0.01f),m_gravity(glm::vec2(0, 0))
{

}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

void PhysicsScene::AddActor(PhysicsObject* a_actor)
{
	m_actors.push_back(a_actor);
}

void PhysicsScene::RemoveActor(PhysicsObject* a_actor)
{
	auto it = std::find(m_actors.begin(), m_actors.end(), a_actor);
	if (it != m_actors.end())
		m_actors.erase(it);
}

void PhysicsScene::Update(float a_dt)
{
	// MUST REMOVE LATER ======================

	static std::list<PhysicsObject*> dirty;
		
	// =======================================^

	// Update physics at a fixed time step.

	static float accumulatedTime = 0.0f;
	accumulatedTime += a_dt;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->FixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;

		// MUST REMOVE LATER ======================
		
		// Check for collisions. We will want to update this to have some kind of scene management in place
		for (auto pActor : m_actors)
		{
			for (auto pOther : m_actors)
			{
				if (pActor == pOther)
					continue;

				if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
					std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
					continue;

				RigidBody* pRigid = dynamic_cast<RigidBody*>(pActor);

				if (pRigid->CheckCollision(pOther))
				{
					pRigid->ApplyForceActor(dynamic_cast<RigidBody*>(pOther),
						pRigid->GetVelocity() * pRigid->GetMass());

					dirty.push_back(pRigid);
					dirty.push_back(pOther);
				}
			}
		}

		dirty.clear();
		// =======================================^
	}
}

void PhysicsScene::Draw()
{
	for (auto pActor : m_actors)
	{
		pActor->Draw();
	}
}

bool PhysicsScene::Circle2Circle(PhysicsObject* a_circle, PhysicsObject* a_otherCircle)
{
	// Tries to cast the object to circle to circle
	Circle* circle1 = dynamic_cast<Circle*>(a_circle);
	Circle* circle2 = dynamic_cast<Circle*>(a_otherCircle);

	// If successful then test for collision
	if (circle1 != nullptr && circle2 != nullptr)
	{
		// ToDo the maths required...
	}

	return false;
}
