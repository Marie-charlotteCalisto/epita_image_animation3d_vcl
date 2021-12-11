#include "fluid.hpp"


#ifdef SCENE_STABLE_FLUID

// Add vcl namespace within the current one - Allows to use function from vcl library without explicitely preceeding their name with vcl::
using namespace vcl;

void scene_model::set_grid_visual(size_t N)
{

    std::vector<vec3> edges;
    float const e = 1e-4f;
    float const dx = 2.0f/(N-1.0f);
    for(int kx=0; kx<=N; ++kx) {
        float const x  = kx*dx-1;
        edges.push_back( vec3(x-dx/2, -dx/2-1, e) );
        edges.push_back( vec3(x-dx/2, 1+dx/2, e) );
    }
    for(int ky=0; ky<=N; ++ky) {
        float const y  = ky*dx-1;
        edges.push_back( vec3(-dx/2-1, y-dx/2, e) );
        edges.push_back( vec3(1+dx/2, y-dx/2, e) );
    }

    grid_visual = segments_drawable(edges);
}

void scene_model::setup_data(std::map<std::string, GLuint>& shaders, scene_structure&, gui_structure& gui)
{
    size_t const N = 60;
    set_grid_visual(N);
    grid_visual.shader = shaders["mesh"];
}



/** This function is called at each frame of the animation loop.
    It is used to compute time-varying argument and perform data data drawing */
void scene_model::frame_draw(std::map<std::string, GLuint>& shaders, scene_structure& scene, gui_structure&)
{

    set_gui();

    timer.update();
    const float time = timer.t;

    if(gui_scene.display_grid)
        draw(grid_visual, scene.camera);

}
void scene_model::mouse_click(scene_structure& scene, GLFWwindow* window, int button, int action, int mods)
{
    ImGui::SetWindowFocus(nullptr);
}


/** Update the visual GUI */
void scene_model::set_gui()
{

    ImGui::SliderFloat("Timer scale", &timer.scale, 0.01f, 4.0f, "%0.2f");
    ImGui::SliderFloat("Time", &timer.t, timer.t_min, timer.t_max);

    ImGui::SliderFloat("Diffusion Density", &gui_scene.diffusion_density, 0.001f, 0.2f, "%0.3f",2.0f);
    ImGui::SliderFloat("Diffusion Velocity", &gui_scene.diffusion_velocity, 0.001f, 0.2f, "%0.3f",2.0f);
    ImGui::Checkbox("Grid", &gui_scene.display_grid); ImGui::SameLine();
    ImGui::Checkbox("Velocity", &gui_scene.display_velocity);
    ImGui::SliderFloat("Velocity scale", &gui_scene.velocity_scaling, 0.1f, 10.0f, "0.2f");

    // Stop/Start time
    bool const stop = ImGui::Button("Stop"); ImGui::SameLine();
    bool const start = ImGui::Button("Start");
    if (stop)  timer.stop();
    if (start) timer.start();


}

#endif

