#include "blood.hpp"

#ifdef SCENE_PROJECT

void Blood::setup_data(std::map<std::string, GLuint>& shaders)
{
    sphere = vcl::mesh_drawable(vcl::mesh_primitive_sphere(0.05f));
    sphere.shader = shaders["mesh"];
    sphere.uniform.color = {1, 0, 0};
}


void Blood::create_particles(vcl::vec3 p, int max_particles)
{

    // Emission of new particle if needed
    timer.periodic_event_time_step = 0.01f;
    const bool is_new_particle = timer.event;

    if(is_new_particle && particles.size() < max_particles)
    {
        particle new_particle;

        new_particle.r = 0.05f;
        // Initial position
        new_particle.p = p;

        // Initial speed
        const float theta = vcl::rand_interval(0, 2*3.14f);
        new_particle.v = vcl::vec3( 2*std::cos(theta), 5.0f, 2*std::sin(theta));

        particles.push_back(new_particle);

    }
}


void Blood::spawn(vcl::vec3 p, const float t)
{
    float dt = 0.05f * timer.scale;
    timer.update();
    int max_particles = 100;

    create_particles(p, max_particles);

    for(int i = 0; i < particles.size(); i++)
    {
        particles[i].f = vcl::vec3(0, -9.81f, 0);
    }

    for(int i = 0; i < particles.size(); i++)
    {
        particles[i].v = (1-0.9f*dt) * particles[i].v + dt * particles[i].f;
        particles[i].p = particles[i].p + dt * particles[i].v;
    }

    // collision between spheres
    for (size_t i = 0; i < particles.size(); ++i) {
        particle& part1 = particles[i];
        for (size_t j = 0; j < particles.size(); ++j) {
            if (j == i)
                continue;

            particle& part2 = particles[j];

            auto detection = norm(part1.p - part2.p);
            if (detection < part1.r + part2.r)
            {
                auto u = (part1.p - part2.p) / detection;

                part1.v = part1.v + dot((part2.v - part1.v), u)*u;
                part2.v = part2.v - dot((part2.v - part1.v), u)*u;
            }
        }
    }

    //collition with ground
    for (size_t i = 0; i < particles.size(); ++i) {
        particle& part = particles[i];  // Current particle
        vcl::vec3 normal = {0,1,0};
        float ground_size = 10.0f;
        float ground_height = -0.3f;
        vcl::vec3 ground_point = {-1*ground_size,ground_height-1e-3f,-1*ground_size};

        float detection = dot(part.p - ground_point, normal);
        if (detection <= part.r) {
            // Reset velocity
            float alpha = 0.8f;
            float beta = 0.1f;

            vcl::vec3 v_perp = dot(part.v, normal) * normal;
            vcl::vec3 v_pp = part.v - v_perp;
            part.v = alpha * v_pp - beta * v_perp;


            // Reset position
            auto d = part.r - (part.p - ground_point)* normal;
            part.p = part.p + d*normal;

        }
    }
}

void Blood::display(scene_structure& scene)
{
    for(size_t k=0; k< particles.size(); ++k)
    {
        const particle& part = particles[k];

        sphere.uniform.transform.translation = part.p;
        draw(sphere, scene.camera);
    }
}

#endif
