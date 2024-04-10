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

<<<<<<< Updated upstream
float Boids::distance_max         = 0.5f; // Modifie la distance de séparartion entre les boids
float Boids::alignment_magnitude  = 0.5f;
float Boids::cohesion_magnitude   = 0.5f;
float Boids::separation_magnitude = 0.5f;

void renderImGui()
{
    ImGui::Begin("Slider");
    ImGui::SliderFloat("Cohesion", &Boids::cohesion_magnitude, 0.f, 1.f);
    ImGui::SliderFloat("Aligment", &Boids::alignment_magnitude, 0.f, 1.f);
    ImGui::SliderFloat("Separation", &Boids::separation_magnitude, 0.f, 1.f);
    ImGui::SliderFloat("Distance with neighbors", &Boids::distance_max, 0.f, 1.f);
    ImGui::End();
}

=======
>>>>>>> Stashed changes
int main()
{
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // Actual application code
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();

    // Paramètres des comportements de boids
    float distance_aligment   = 0.1f;
    float distance_cohesion   = 0.2f;
    float distance_separation = 0.05f;

    // Génération des boids
    std::vector<Boids> boids(50);
    for (auto& boid : boids)
    {
        boid.set_speed();
        boid.set_position();
    }

    // Déclaration de la boucle de mise à jour infinie
    ctx.update = [&]() {
        // Mise en place de l'arrière-plan
        ctx.background({0.3f, 0.9f, 0.6f, 0.9f});
        ctx.fill = {0.3f, 0.9f, 0.6f, 0.9f};
        ctx.square(
            p6::Center{0.0f, 0.0f},
            p6::Radius{1.0f}
        );

        // Mise en place des boids
        ctx.fill   = {0.3f, 0.5f, 0.9f, 1.0f};
        ctx.stroke = {0.3f, 0.5f, 0.9f, 1.0f};

        ImGui::Begin("Slider");
        ImGui::SliderFloat("Distance to align", &distance_aligment, 0.f, 1.f);
        ImGui::SliderFloat("Distance to unite", &distance_cohesion, 0.f, 1.f);
        ImGui::SliderFloat("Distance to escape", &distance_separation, 0.f, 1.f);
        ImGui::SliderFloat("Alignment Force", &Boids ::alignment_force, 0.f, 1.f);
        ImGui::SliderFloat("Cohesion Force", &Boids ::cohesion_force, 0.f, 1.f);

        ImGui::End();

        for (auto& boid : boids)
        {
            boid.update_pos();
            boid.alignment(boids); 
            boid.update_direction(boids);
            ctx.circle(
                p6::Center{boid.get_position().x, boid.get_position().y},
                p6::Radius{0.025f}
            );
        }
    };

    // Doit être fait en dernier. Cela démarre la boucle infinie.
    ctx.start();
}
