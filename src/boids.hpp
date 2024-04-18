
#include <vector>
#include "p6/p6.h"

// #include "glm/fwd.hpp"
#include "glm/vec2.hpp"

class Boids {
private:
    // Attributs

    glm::vec2  m_position;
    glm::vec2  m_speed;
    glm ::vec2 m_direction;

public:
    // Static attributs
    static float cohesion_force;
    static float separation_force;

    // Constructors
    Boids()
        : m_position(0), m_speed(0.01), m_direction(p6::random::direction()){};
    Boids(const glm::vec2& position, const glm::vec2& speed)
        : m_position(position), m_speed(speed){};

    // Destructor
    ~Boids() = default;

    // copy constructor
    Boids(const Boids& other) = default;

    // Methods

    void update_pos();
    void update_direction(std::vector<Boids>& boids, float distance_aligment, float distance_cohesion, float distance_separation);

    void cohesion(const std::vector<Boids>& boids, float distance_cohesion);
    void alignment(const std::vector<Boids>& boids, float distance_alignment);
    void separation(const std::vector<Boids>& boids, float distance_separation);

    // Getters
    glm::vec2 get_position() const { return m_position; };
    glm::vec2 get_speed() const { return m_speed; };
    glm::vec2 get_direction() const { return m_direction; };

    // Setters
    void set_position();
    void set_speed();
};
