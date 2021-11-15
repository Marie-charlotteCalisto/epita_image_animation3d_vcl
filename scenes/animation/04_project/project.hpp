#pragma once

#include "main/scene_base/base.hpp"
#include "ant.hpp"
#include "utils.hpp"

#ifdef SCENE_PROJECT


struct scene_model : scene_base
{

    void setup_data(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);
    void frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);

    void set_gui();

    vcl::mesh_drawable ground;

    Ant my_ant;

    gui_scene_structure gui_scene;
    vcl::timer_interval timer;



};

#endif


