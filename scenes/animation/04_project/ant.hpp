#pragma once
#include "main/scene_base/base.hpp"

#include "utils.hpp"

#ifdef SCENE_PROJECT
class Ant{
    public:
        Ant();
        void make_hierarchy(std::map<std::string, GLuint>& shaders);
        void update(const float t);
        void display(gui_scene_structure gui_scene, scene_structure& scene, std::map<std::string, GLuint>& shaders);

    private:
        vcl::hierarchy_mesh_drawable hierarchy;
        vcl::hierarchy_mesh_drawable_display_skeleton hierarchy_visual_debug;
};
#endif
