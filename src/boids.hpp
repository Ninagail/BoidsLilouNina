#pragma once

#include <vector>
#include "glm/vec2.hpp"
#include "p6/p6.h"

class Boids {
private:
    glm::vec2 m_position;
    glm::vec2 m_speed;
    glm::vec2 m_direction;

    // methodes

public:
<<<<<<< Updated upstream
    // attributs
    static float distance_max;
    static float alignment_magnitude;
    static float cohesion_magnitude;
    static float separation_magnitude;
=======
    // Static boids attributes
    static float alignment_force;
    static float cohesion_force;
>>>>>>> Stashed changes

    // Constructeurs
    Boids()
<<<<<<< Updated upstream
        : m_position(0), m_speed(0), m_direction(p6::random::direction()){}; // Fix: Initialize position and speed separately
=======
        : m_position(0), m_speed(0.01), m_direction(p6::random::direction()) {}
    Boids(const glm::vec2& position, const glm::vec2& speed)
        : m_position(position), m_speed(speed), m_direction(p6::random::direction()) {}
>>>>>>> Stashed changes

    // Destructeur
    ~Boids() = default;

<<<<<<< Updated upstream
    // methodes

    void update_pos();
    void update_direction(const std::vector<Boids>& boids);
=======
    // Copy constructeur
    Boids(const Boids& other) = default;

    // Update methods
    void update_pos();
    void update_direction(std::vector<Boids>& boids, float distance_alignment, float distance_cohesion, float distance_separation);
>>>>>>> Stashed changes

    // Boids behavior

<<<<<<< Updated upstream
    glm::vec2 cohesion(const std::vector<Boids>& boids);
    glm::vec2 alignment(const std::vector<Boids>& boids);
    glm::vec2 separation(const std::vector<Boids>& boids);
=======
    void alignment(const std::vector<Boids>& boids, float distance_alignment);
    void cohesion(const std::vector<Boids>& boids, float distance_cohesion);
    void separation(const std::vector<Boids>& boids, float distance_separation);
>>>>>>> Stashed changes

    // Getters
    glm::vec2 get_position() const { return m_position; }
    glm::vec2 get_speed() const { return m_speed; }
    glm::vec2 get_direction() const { return m_direction; }

<<<<<<< Updated upstream
    void set_position();
=======
    // Setters
    void set_position(const std::vector<Boids>& existingBoids);
>>>>>>> Stashed changes
    void set_speed();
};
