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
    if (x_pos <= -0.95f || x_pos >= 0.95f)
    {
        x_speed = -x_speed;
    }
    if (y_pos <= -0.95f || y_pos >= 0.95f)
    {
        y_speed = -y_speed;
    }
}

float Boids ::get_x_pos() const
{
    return x_pos;
}

float Boids ::get_y_pos() const
{
    return y_pos;
}