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

// METHODS

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

void Boids::update_direction(const std::vector<Boids>& boids)
{
    m_direction += glm::vec2(alignment_magnitude) * this->alignment(boids) + glm::vec2(cohesion_magnitude) * this->cohesion(boids) + glm::vec2(separation_magnitude) * this->separation(boids);

    m_direction = glm::normalize(m_direction);
}

std::vector<Boids> Boids::get_neighbors(const std::vector<Boids>& boids, const float& distance_max)
{
    std::vector<Boids> neighbors{};
    for (auto& other_boid : boids)
    {
        if (&other_boid != this)
        {
            if (glm::distance(other_boid.get_position(), m_position) <= distance_max)
            {
                neighbors.push_back(other_boid);
            }
        }
    }

    return neighbors;
}

glm::vec2 Boids::cohesion(const std::vector<Boids>& boids)
{
    // find the neighbors
    std::vector<Boids> neighbors = get_neighbors(boids, distance_max);

    // initialise our cohesion vector
    glm::vec2 coh(0.f, 0.f);

    // verify if the boid have neighbors
    if (neighbors.empty())
    {
        return coh;
    }
    // apply cohesion to all neighbors
    for (auto other : neighbors)
    {
        coh += other.get_position();
    }

    // divise by the number of neighbors
    coh /= (float)neighbors.size();

    // obtain a final vector
    coh -= m_position;

    return glm::normalize(coh);
}

glm::vec2 Boids::alignment(const std::vector<Boids>& boids)
{
    // find the neighbors
    std::vector<Boids> neighbors = get_neighbors(boids, distance_max);

    // initialise our alignment vector
    glm::vec2 ali(0.f, 0.f);

    // verify if the boid have neighbors
    if (neighbors.empty())
    {
        return ali;
    }
    // apply cohesion to all neighbors
    for (auto other : neighbors)
    {
        ali += other.get_direction();
    }

    // // divise by the number of neighbors
    // ali.x = ali.x / (float)neighbors.size();
    // ali.y = ali.y / (float)neighbors.size();

    return glm::normalize(ali);
}

glm::vec2 Boids::separation(const std::vector<Boids>& boids)
{
    // find the neighbors
    std::vector<Boids> neighbors = get_neighbors(boids, distance_max);

    // initialise our separation vector
    glm::vec2 sep(0.f, 0.f);

    // verify if the boid have neighbors
    if (neighbors.empty())
    {
        return sep;
    }

    for (auto other : neighbors)
    {
        glm::vec2 towardsMe;
        towardsMe = this->get_position() - other.get_position();

        if (length(towardsMe) > 0)
        {
            sep += glm::normalize(towardsMe) / length(towardsMe);
        }
    }
    return glm::normalize(sep);
}

// SETTER
void Boids::set_position()
{
    m_position.x = p6::random::number(-0.975f, 0.975f);
    m_position.y = p6::random::number(-0.975f, 0.975f);
}

void Boids::set_speed()
{
    m_speed.x = p6::random::number(-0.01f, 0.01f);
    m_speed.y = p6::random::number(-0.01f, 0.01f);
}
