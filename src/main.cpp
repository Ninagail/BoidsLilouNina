#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT
#include <random>
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

    float x_pos   = p6::random::number(-1.0f, 1.0f);
    float y_pos   = p6::random::number(-1.0f, 1.0f);
    float x_speed = p6::random::number(-0.01f, 0.01f);
    float y_speed = p6::random::number(-0.01f, 0.01f);
    // Declare your infinite update loop.
    ctx.update = [&]() {
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

        ctx.background(p6::NamedColor::BabyBlue);
        // ctx.translate(x, y);
        ctx.circle(
            p6::Center{x_pos, y_pos},
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