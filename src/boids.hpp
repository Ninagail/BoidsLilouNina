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
    static float cohesion_force;
    static float separation_force;

    static float distance_cohesion;
    static float distance_alignment;
    static float distance_separation;

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
    void drawBoids(p6::Context& ctx) const;

    void update_pos();
    void update_direction(std::vector<Boids>& boids);

    // lois boids
    void cohesion(const std::vector<Boids>& boids);
    void alignment(const std::vector<Boids>& boids);
    void separation(const std::vector<Boids>& boids);

    // getters
    glm::vec2 get_position() const { return m_position; };
    glm::vec2 get_speed() const { return m_speed; };
    glm::vec2 get_direction() const { return m_direction; };

    // setters
    void set_position();
    void set_speed();
};
