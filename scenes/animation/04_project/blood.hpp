#pragma once

#include "main/scene_base/base.hpp"

#ifdef SCENE_PROJECT

struct particle{
    vcl::vec3 p;
    vcl::vec3 v;
    vcl::vec3 f;

    float r;
};

class Blood{

    public:
        Blood(){};
        void setup_data(std::map<std::string, GLuint>& shaders);
        void spawn(vcl::vec3 p, const float t);
        void create_particles(vcl::vec3 p,int max_particles);
        void display(scene_structure& scene);
    private:
        vcl::mesh_drawable sphere;
        vcl::timer_event timer;

        std::vector<particle> particles;
};

#endif
