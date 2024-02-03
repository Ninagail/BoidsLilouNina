#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT
#include <random>
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

    Boids boid;
    boid.set_pos();

    // Declare your infinite update loop.
    ctx.update = [&]() {
        boid.update_pos();
        ctx.background(p6::NamedColor::BabyBlue);
        ctx.circle(
            p6::Center{boid.get_x_pos(), boid.get_y_pos()},
            p6::Radius{0.05f}
        );

        ctx.square(
            p6::Center{0.0f, 0.0f},
            p6::Radius{1.0f}
        );
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}