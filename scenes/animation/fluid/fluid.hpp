#pragma once

#include "main/scene_base/base.hpp"
#include "utils.hpp"

#ifdef SCENE_STABLE_FLUID


struct scene_model : scene_base
{
    void setup_data(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);
    void frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);

    void set_grid_visual(size_t N);

    void mouse_click(scene_structure& scene, GLFWwindow* window, int button, int action, int mods);
    void set_gui();

    gui_parameter gui_scene;
    vcl::timer_interval timer;
    vcl::segments_drawable grid_visual;




};

#endif
