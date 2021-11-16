#pragma once
#include "main/scene_base/base.hpp"

#include "blood.hpp"
#include "utils.hpp"

#ifdef SCENE_PROJECT

class Ant{
    public:
        Ant();
        void setup_data(std::map<std::string, GLuint>& shaders);
        void update(const float t);
        void display(gui_scene_structure gui_scene, scene_structure& scene, std::map<std::string, GLuint>& shaders);
        bool isStrucked(scene_structure& scene, GLFWwindow* window, int button, int action, int mods);
        void die();

    private:
        float random;

        Blood ant_blood;
        vcl::hierarchy_mesh_drawable hierarchy;
        vcl::hierarchy_mesh_drawable_display_skeleton hierarchy_visual_debug;
        bool isDead = false;
        void update_dead();
};
#endif
