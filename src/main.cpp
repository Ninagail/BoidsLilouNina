#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT
#include <glm/vec2.hpp>
#include <random>
#include <vector>
#include "boids.hpp"
#include "doctest/doctest.h"
#include "glm/fwd.hpp"
#include "imgui.h"
#include "p6/p6.h"

float distance_aligment       = 0.1f;
float distance_separation     = 0.05f;
float distance_cohesion       = 0.2f;
float Boids::separation_force = 0.01f;
float Boids::cohesion_force   = 0.2f;

void renderImGui()
{
    ImGui::Begin("Slider");
    ImGui::SliderFloat("CohesionForce", &Boids::cohesion_force, 0.f, 1.f);
    ImGui::SliderFloat("SeparationForce", &Boids::separation_force, 0.f, 1.f);
    ImGui::SliderFloat("Distance to unite", &distance_cohesion, 0.f, 1.f);
    ImGui::SliderFloat("Distance to escape", &distance_separation, 0.f, 1.f);
    ImGui::SliderFloat("Distance to align", &distance_aligment, 0.f, 1.f);

    ImGui::End();
}

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
        boid.set_speed();
        boid.set_position();
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

        renderImGui();

        for (auto& boid : boids)
        {
            ctx.circle(
                p6::Center{boid.get_position().x, boid.get_position().y},
                p6::Radius{0.025f}
            );
            boid.update_pos();
            boid.update_direction(boids, distance_aligment, distance_cohesion, distance_separation);
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}
