#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT
#include <random>
#include <vector>
#include "boids.hpp"
#include "doctest/doctest.h"
#include "p6/p6.h"

int main()
{
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // Actual application code
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();

    // Boids             boid;
    std::vector<Boids> boids(50);
    for (auto& boid : boids)
    {
        boid.set_pos();
    }

    // Declare your infinite update loop.
    ctx.update = [&]() {
        // setup background
        ctx.background({0.3f, 0.9f, 0.6f, 0.9f});
        ctx.fill = {0.3f, 0.9f, 0.6f, 0.9f};
        ctx.square(
            p6::Center{0.0f, 0.0f},
            p6::Radius{1.0f}
        );

        // setup boids
        ctx.fill   = {0.3f, 0.5f, 0.9f, 1.0f};
        ctx.stroke = {0.3f, 0.5f, 0.9f, 1.0f};

        for (auto& boid : boids)
        {
            boid.update_pos();
        }

        for (auto& boid : boids)
        {
            ctx.circle(
                p6::Center{boid.get_x_pos(), boid.get_y_pos()},
                p6::Radius{0.025f}
            );
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}
