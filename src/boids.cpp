#include "boids.hpp"
#include <stdlib.h>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <vector>
#include "doctest/doctest.h"
#include "glm/common.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "p6/p6.h"

static constexpr glm::vec2 speedMax = glm::vec2(0.02f, 0.02f);

// METHODS UPDATE

void Boids ::update_pos()
{
    m_position.x += m_speed.x;
    m_position.y += m_speed.y;
    if (m_position.x <= -0.975f)
    {
        m_position.x += 1.95;
    }
    if (m_position.x >= 0.975f)
    {
        m_position.x -= 1.95;
    }
    if (m_position.y <= -0.975f)
    {
        m_position.y += 1.95;
    }
    if (m_position.y >= 0.975f)
    {
        m_position.y -= 1.95;
    }
}

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

// NEIGHBORS
std::vector<Boids> Boids::get_neighbors(const std::vector<Boids>& boids, const float& distance_max)
{
    std::vector<Boids> neighbors;

    for (const auto& other : boids)
    {
        if (&other != this)
        {
            float distance = glm::distance(m_position, other.m_position);
            if (distance < distance_max)
            {
                neighbors.push_back(other);
            }
        }
    }

    return neighbors;
}

/*LOI DES BOIDS*/

// Cohésion
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
            newPosition += (elem.m_position - m_position) * 0.5f;
            count++;
        }
    }

    if (count > 0)
    {
        newPosition /= count;

        if (length(newPosition) > 0.01f)
        {
            newPosition = glm::normalize(newPosition) * 0.01f;
        }

        m_speed += (newPosition) * 0.01f;
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
        if (length(newVelocity) > 0.01f)
        {
            newVelocity = glm::normalize(newVelocity);
            m_speed     = newVelocity * speedMax;
        }
    }
}

// Séparation
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
        if (length(newDisplacement) > 0.01f)
        {
            newDisplacement = glm::normalize(newDisplacement) * 0.01f;
        }
        m_speed = newDisplacement;
    }
}

// SETTER
void Boids::set_position(const std::vector<Boids>& existingBoids)
{
    m_position.x = p6::random::number(-0.975f, 0.975f);
    m_position.y = p6::random::number(-0.975f, 0.975f);
    // bool positionFound = false;
    // while (!positionFound)
    // {
    //     // Générer une nouvelle position aléatoire

    //     // Vérifier s'il y a une collision avec une position existante
    //     bool collision = false;
    //     for (const auto& boid : existingBoids)
    //     {
    //         if (&boid != this && glm::distance(m_position, boid.get_position()) < 0.1f)
    //         {
    //             collision = true;
    //             break;
    //         }
    //     }

    //     // Si aucune collision n'est détectée, la position est valide
    //     if (!collision)
    //     {
    //         positionFound = true;
    //     }
    // }
}

void Boids::set_speed()
{
    m_speed.x = p6::random::number(-0.01f, 0.01f);
    m_speed.y = p6::random::number(-0.01f, 0.01f);
}
