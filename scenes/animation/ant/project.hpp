#pragma once

#include "main/scene_base/base.hpp"
#include "ant.hpp"
#include "utils.hpp"

#ifdef SCENE_ANT


struct scene_model : scene_base
{

    void setup_data(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);
    void frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);
    void mouse_click(scene_structure& scene, GLFWwindow* window, int button, int action, int mods);

    void set_gui();

    void create_ants(std::map<std::string,GLuint>& shaders);
    std::vector<Ant> my_ants;
    size_t nb_ants = 20;

    vcl::mesh_drawable ground;
    gui_scene_structure gui_scene;
    vcl::timer_interval timer;
};

#endif


