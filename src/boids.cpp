#include "boids.hpp"
#include <stdlib.h>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <vector>
#include "doctest/doctest.h"
#include "glm/common.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "p6/p6.h"

// METHODS

void Boids ::update_pos()
{
    m_position.x += m_speed.x;
    m_position.y += m_speed.y;
    if (m_position.x <= -0.975f)
    {
        m_position.x += 1.95;
    }
    if (m_position.x >= 0.975f)
    {
        m_position.x -= 1.95;
    }
    if (m_position.y <= -0.975f)
    {
        m_position.y += 1.95;
    }
    if (m_position.y >= 0.975f)
    {
        m_position.y -= 1.95;
    }
}

// std ::vector<float> Boids ::cohesion(std ::vector<Boids> boids)
// {
// }

// GETTER

// SETTER
void Boids::set_position()
{
    m_position.x = p6::random::number(-0.975f, 0.975f);
    m_position.y = p6::random::number(-0.975f, 0.975f);
}

void Boids::set_speed()
{
    m_speed.x = p6::random::number(-0.01f, 0.01f);
    m_speed.y = p6::random::number(-0.01f, 0.01f);
}
