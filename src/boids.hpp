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

    // methodes

public:
    // attributs
    static float distance_max;
    static float alignment_magnitude;
    static float cohesion_magnitude;
    static float separation_magnitude;

    // constructeur
    Boids()
        : m_position(0), m_speed(0), m_direction(p6::random::direction()){}; // Fix: Initialize position and speed separately

    // destructeur
    ~Boids() = default;

    // methodes

    void update_pos();
    void update_direction(const std::vector<Boids>& boids);

    std::vector<Boids> get_neighbors(const std::vector<Boids>& boids, const float& distance_max);

    glm::vec2 cohesion(const std::vector<Boids>& boids);
    glm::vec2 alignment(const std::vector<Boids>& boids);
    glm::vec2 separation(const std::vector<Boids>& boids);

    // getters
    glm::vec2 get_position() const { return m_position; };
    glm::vec2 get_speed() const { return m_speed; };
    glm::vec2 get_direction() const { return m_direction; };

    // setters

    void set_position();
    void set_speed();
};
