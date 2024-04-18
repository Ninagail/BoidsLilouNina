#include "boids.hpp"
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <vector>
#include "doctest/doctest.h"
#include "glm/common.hpp"
#include "glm/geometric.hpp"
#include "p6/p6.h"

static constexpr glm::vec2 speedMax = glm::vec2(0.02f, 0.02f);

// METHODS

void Boids::update_pos()
{
    m_position += m_speed;

    // Wrap around the screen edges
    if (m_position.x <= -0.975f)
    {
        m_position.x += 1.95f;
    }
    else if (m_position.x >= 0.975f)
    {
        m_position.x -= 1.95f;
    }

    if (m_position.y <= -0.975f)
    {
        m_position.y += 1.95f;
    }
    else if (m_position.y >= 0.975f)
    {
        m_position.y -= 1.95f;
    }
}

// Update the direction of the boid based on alignment, cohesion, and separation
void Boids::update_direction(std::vector<Boids>& boids, float distance_alignment, float distance_cohesion, float distance_separation)

{
    for (auto& elem : boids)
    {
        elem.alignment(boids, distance_alignment);
        elem.cohesion(boids, distance_cohesion);
        elem.separation(boids, distance_separation);
    }
    m_position += m_speed;
    this->update_pos();
}

/*LOI DES BOIDS*/

// Cohesion
void Boids::cohesion(const std::vector<Boids>& boids, float distance_cohesion)
{
    glm::vec2 newPosition{0.0f, 0.0f};
    int       count = 0;

    for (auto& elem : boids)
    {
        if (&elem == this)
            continue;
        float distance = glm::length(elem.m_position - this->m_position);
        if (distance < distance_cohesion)
        {
            newPosition += (elem.m_position - m_position) * cohesion_force;
            count++;
        }
    }

    if (count > 0)
    {
        newPosition /= count;

        if (length(newPosition) > separation_force)
        {
            newPosition = glm::normalize(newPosition) * separation_force;
        }

        m_speed += (newPosition)*separation_force;
    }
}

// Alignement
void Boids::alignment(const std::vector<Boids>& boids, float distance_alignment)
{
    glm::vec2 newVelocity{0.0f, 0.0f};
    int       count = 0;

    for (auto& elem : boids)
    {
        const float distance = glm::length(elem.m_position - this->m_position);
        if (distance < distance_alignment)
        {
            newVelocity += elem.m_speed;
            count++;
        }
    }

    if (count > 0)
    {
        newVelocity /= count;
        if (length(newVelocity) > separation_force)
        {
            newVelocity = glm::normalize(newVelocity);
            m_speed     = newVelocity * speedMax;
        }
    }
}

// Separation
void Boids::separation(const std::vector<Boids>& boids, float distance_separation)

{
    glm::vec2 newDisplacement{0.0f, 0.0f};
    int       count = 0;
    for (auto& elem : boids)
    {
        if (&elem == this)
            continue;

        float distance = glm::length(elem.m_position - this->m_position);

        if (distance < distance_separation)
        {
            glm::vec2 difference = glm::normalize(this->m_position - elem.m_position);
            difference /= distance;
            newDisplacement += difference;
            count++;
        }
    }
    if (count > 0)
    {
        newDisplacement /= count;
        if (length(newDisplacement) > separation_force)
        {
            newDisplacement = glm::normalize(newDisplacement) * separation_force;
        }
        m_speed = newDisplacement;
    }
}

// SETTER

// Set random position
void Boids::set_position()

{
    m_position.x = p6::random::number(-0.975f, 0.975f);
    m_position.y = p6::random::number(-0.975f, 0.975f);
}

// Set random speed
void Boids::set_speed()
{
    m_speed.x = p6::random::number(-0.01f, 0.01f);
    m_speed.y = p6::random::number(-0.01f, 0.01f);
}
