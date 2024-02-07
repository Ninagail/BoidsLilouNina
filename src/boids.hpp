// #include "p6/p6.h"

class Boids {
private:
    // attributs
    float x_pos;
    float y_pos;
    float x_speed;
    float y_speed;

    // methodes

public:
    // constructeur
    Boids()
        : x_pos(), y_pos(), x_speed(), y_speed(){};

    // destructeur
    ~Boids() = default;

    // methodes
    void set_pos();
    void update_pos();

    // getters
    float get_x_pos() const;
    float get_y_pos() const;
};
