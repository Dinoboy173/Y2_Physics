#include "Plane.h"

#include <Gizmos.h>
#include <iostream>

Plane::Plane(glm::vec2 a_normal, float a_distToOrigin, glm::vec4 a_colour) : PhysicsObject(PLANE)
{
	m_normal = a_normal;
	m_distToOrigin = a_distToOrigin;
	m_colour = a_colour;
}

Plane::Plane() : PhysicsObject(PLANE)
{
	m_normal = glm::vec2(0, 1);
	m_distToOrigin = 0.f;
	m_colour = glm::vec4(1, 1, 1, 1);
}

Plane::~Plane()
{

}

void Plane::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
	
}

void Plane::MakeGizmo()
{
	float lineSegmentLength = 300;
	glm::vec2 centerPoint = m_normal * m_distToOrigin;
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 colourFade = m_colour;
	colourFade.a = 0;
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);

	aie::Gizmos::add2DLine(start, end, m_colour);
	aie::Gizmos::add2DTri(start, end, start - m_normal * 10.f, m_colour, m_colour, colourFade);
	aie::Gizmos::add2DTri(end, end - m_normal * 10.f, start - m_normal * 10.f, m_colour, colourFade, colourFade);
}