#include "boids.hpp"
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <vector>
#include "doctest/doctest.h"
#include "glm/common.hpp"
#include "glm/geometric.hpp"
#include "p6/p6.h"

<<<<<<< Updated upstream
// METHODS
=======
// Initialisation des attributs statiques
float                      Boids::alignment_force = 0.01f;
float                      Boids::cohesion_force  = 0.02f;
static constexpr glm::vec2 speedMax               = glm::vec2(0.02f, 0.02f);

// Méthodes de mise à jour
>>>>>>> Stashed changes

void Boids::update_pos()
{
    m_position += m_speed;

    // Wrap-around du bord de l'écran
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

/*void Boids::update_direction(const std::vector<Boids>& boids)
{
<<<<<<< Updated upstream
    m_direction += glm::vec2(alignment_magnitude) * this->alignment(boids) + glm::vec2(cohesion_magnitude) * this->cohesion(boids) + glm::vec2(separation_magnitude) * this->separation(boids);

    m_direction = glm::normalize(m_direction);
}*/

void Boids::update_direction(const std::vector<Boids>& boids)
{
    // Calculate alignment, cohesion, and separation vectors
    glm::vec2 alignment  = this->alignment(boids);
    glm::vec2 cohesion   = this->cohesion(boids);
    glm::vec2 separation = this->separation(boids); // This is where the separation vector is calculated

    // Update the direction by adding weighted vectors
    m_direction += alignment * alignment_magnitude + cohesion * cohesion_magnitude + separation * separation_magnitude;

    // Normalize the direction vector
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
=======
    for (auto& elem : boids)
    {
        elem.alignment(boids, distance_alignment);
        elem.cohesion(boids, distance_cohesion);
        elem.separation(boids, distance_separation);
    }

    this->update_pos();
}

/* LOI DES BOIDS */
>>>>>>> Stashed changes

glm::vec2 Boids::alignment(const std::vector<Boids>& boids)
{
    // Find the neighbors
    std::vector<Boids> neighbors = get_neighbors(boids, distance_max);

<<<<<<< Updated upstream
    // Initialize variables
    float xvel_avg          = 0.f;
    float yvel_avg          = 0.f;
    int   neighboring_boids = 0;

    // Loop through all neighbors
    for (auto& other : neighbors)
    {
        if (&other != this) // Exclude the current boid from alignment calculation
=======
    for (const auto& elem : boids)
    {
        const float distance = glm::length(elem.m_position - m_position);
        if (distance < distance_alignment)
>>>>>>> Stashed changes
        {
            // Accumulate velocities and count neighboring boids
            xvel_avg += other.get_speed().x;
            yvel_avg += other.get_speed().y;
            neighboring_boids++;
        }
    }

    // Update velocity based on neighboring boids
    if (neighboring_boids > 0)
    {
<<<<<<< Updated upstream
        // Average velocities
        xvel_avg /= neighboring_boids;
        yvel_avg /= neighboring_boids;

        // Update velocity according to matching factor
        float matchingfactor = 0.1f; // You can adjust this value as needed
        m_speed.x += (xvel_avg - m_speed.x) * matchingfactor;
        m_speed.y += (yvel_avg - m_speed.y) * matchingfactor;
=======
        newVelocity /= count;
        if (glm::length(newVelocity) > alignment_force)
        {
            newVelocity = glm::normalize(newVelocity);
            m_speed     = newVelocity * speedMax;
        }
>>>>>>> Stashed changes
    }

    // Return current velocity without normalizing
    return glm::vec2(m_speed.x, m_speed.y);
}

<<<<<<< Updated upstream
glm::vec2 Boids::separation(const std::vector<Boids>& boids)
{
    // find the neighbors
    std::vector<Boids> neighbors = get_neighbors(boids, distance_max);

    // initialize our separation vector
    glm::vec2 sep(0.f, 0.f);

    // verify if the boid has neighbors
    if (neighbors.empty())
=======
// Cohésion
void Boids::cohesion(const std::vector<Boids>& boids, float distance_cohesion)
{
    glm::vec2 newPosition{0.0f, 0.0f};
    int       count = 0;

    for (const auto& elem : boids)
    {
        if (&elem == this)
            continue;
        float distance = glm::length(elem.m_position - m_position);
        if (distance < distance_cohesion)
        {
            newPosition += (elem.m_position - m_position) * cohesion_force;
            count++;
        }
    }

    if (count > 0)
    {
        newPosition /= count;

        if (glm::length(newPosition) > alignment_force)
        {
            newPosition = glm::normalize(newPosition) * alignment_force;
        }

        m_speed += (newPosition)*alignment_force;
    }
}

// Séparation
void Boids::separation(const std::vector<Boids>& boids, float distance_separation)
{
    glm::vec2 newDisplacement{0.0f, 0.0f};
    int       count = 0;

    for (const auto& elem : boids)
>>>>>>> Stashed changes
    {
        return sep;
    }

<<<<<<< Updated upstream
    for (auto other : neighbors)
    {
        glm::vec2 towardsMe;
        towardsMe = this->get_position() - other.get_position();
=======
        float distance = glm::length(elem.m_position - m_position);
>>>>>>> Stashed changes

        float dist = glm::length(towardsMe);
        if (dist > 0)
        {
<<<<<<< Updated upstream
            // Calculate the separation vector with magnitude inversely proportional to the distance
            sep += glm::normalize(towardsMe) / dist;
        }
    }
    return glm::normalize(sep);
}

// SETTER
void Boids::set_position()
=======
            glm::vec2 difference = glm::normalize(m_position - elem.m_position);
            difference /= distance;
            newDisplacement += difference;
            count++;
        }
    }

    if (count > 0)
    {
        newDisplacement /= count;
        if (glm::length(newDisplacement) > alignment_force)
        {
            newDisplacement = glm::normalize(newDisplacement) * alignment_force;
        }
        m_speed = newDisplacement;
    }
}

// Setter
void Boids::set_position(const std::vector<Boids>& existingBoids)
>>>>>>> Stashed changes
{
    m_position.x = p6::random::number(-0.975f, 0.975f);
    m_position.y = p6::random::number(-0.975f, 0.975f);
}

void Boids::set_speed()
{
    m_speed.x = p6::random::number(-0.01f, 0.01f);
    m_speed.y = p6::random::number(-0.01f, 0.01f);
}
