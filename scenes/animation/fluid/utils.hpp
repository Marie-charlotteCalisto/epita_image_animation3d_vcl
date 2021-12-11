#pragma once

#ifdef SCENE_STABLE_FLUID

struct gui_parameter {
    bool display_grid = true;
    bool display_velocity = true;
    float diffusion_velocity = 0.001f;
    float diffusion_density = 0.005f;
    float velocity_scaling = 1.0f;
   // density_type_structure density_type = density_color;
};

#endif
