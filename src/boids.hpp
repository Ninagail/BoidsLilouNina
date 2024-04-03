#include <vector>
#include "p6/p6.h"

// #include "glm/fwd.hpp"
#include "glm/vec2.hpp"

class Boids {
private:
    // attributs

    glm::vec2  m_position;
    glm::vec2  m_speed;
    glm ::vec2 m_direction;

public:
    // attributs
    // static float distance_separation;
    // static float distance_cohesion;
    // static float distance_aligment;
    static float alignment_magnitude;
    static float cohesion_magnitude;
    static float separation_magnitude;

    // constructeur
    Boids()
        : m_position(0), m_speed(0.01), m_direction(p6::random::direction()){}; // Fix: Initialize position and speed separately
    Boids(const glm::vec2& position, const glm::vec2& speed)                    // Fix: Swap the positions of 'position' and 'speed'
        : m_position(position), m_speed(speed){};                               // Fix: Initialize position and speed separately

    // destructeur
    ~Boids() = default;

    // copy constructor
    Boids(const Boids& other) = default;

    // methodes

    void update_pos();
    void update_direction(std::vector<Boids>& boids, float distance_aligment, float distance_cohesion, float distance_separation);

    std::vector<Boids> get_neighbors(const std::vector<Boids>& boids, const float& distance_max);

    // lois boids
    void cohesion(const std::vector<Boids>& boids, float distance_cohesion);
    void alignment(const std::vector<Boids>& boids, float distance_alignment);
    void separation(const std::vector<Boids>& boids, float distance_separation);

    // getters
    glm::vec2 get_position() const { return m_position; };
    glm::vec2 get_speed() const { return m_speed; };
    glm::vec2 get_direction() const { return m_direction; };

    // setters

    void set_position(const std::vector<Boids>& existingBoids);
    void set_speed();
};
