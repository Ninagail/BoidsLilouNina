// #include "p6/p6.h"
#include <vector>
// #include "glm/fwd.hpp"
#include "glm/vec2.hpp"

class Boids {
private:
    // attributs

    glm::vec2 m_position;
    glm::vec2 m_speed;

    // methodes

public:
    // constructeur
    Boids()
        : m_position(0), m_speed(0){}; // Fix: Initialize position and speed separately

    // destructeur
    ~Boids() = default;

    // methodes

    void update_pos();
    // std ::vector<float> cohesion(std ::vector<Boids> boids);

    // getters
    glm::vec2 get_position() const { return m_position; };
    glm::vec2 get_speed() const { return m_speed; };

    // setters

    void set_position();
    void set_speed();
};
