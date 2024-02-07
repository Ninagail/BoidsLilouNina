#include "boids.hpp"
#include "doctest/doctest.h"
#include "p6/p6.h"

void Boids ::set_pos()
{
    x_pos   = p6::random::number(-1.0f, 1.0f);
    y_pos   = p6::random::number(-1.0f, 1.0f);
    x_speed = p6::random::number(-0.01f, 0.01f);
    y_speed = p6::random::number(-0.01f, 0.01f);
}

void Boids ::update_pos()
{
    x_pos += x_speed;
    y_pos += y_speed;
    if (x_pos <= -0.95f)
    {
        x_pos += 2;
    }
    if (x_pos >= 0.95f)
    {
        x_pos -= 2;
    }
    if (y_pos <= -0.95f)
    {
        y_pos += 2;
    }
    if (y_pos >= 0.95f)
    {
        y_pos -= 2;
    }
}

std ::vector<float> Boids ::cohesion(std ::vector<Boids> boids)
{
    std ::vector<float> cohesion = {0.0f, 0.0f};
    for (auto& boid : boids)
    {
        cohesion[0] += boid.get_x_pos();
        cohesion[1] += boid.get_y_pos();
    }
    cohesion[0] /= boids.size();
    cohesion[1] /= boids.size();
    return cohesion;
}

// GETTER
float Boids ::get_x_pos() const
{
    return x_pos;
}

float Boids ::get_y_pos() const
{
    return y_pos;
}