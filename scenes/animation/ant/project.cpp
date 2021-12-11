#include "project.hpp"

#ifdef SCENE_ANT


using namespace vcl;



void scene_model::setup_data(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& )
{

    float ground_height = -0.3f;
    float ground_size = 10.0f;
    auto texture_wood = create_texture_gpu(image_load_png("../scenes/animation/02_simulation/assets/wood.png"));
    ground = mesh_drawable(mesh_primitive_quad({-1*ground_size,ground_height-1e-3f,-1*ground_size}, {1*ground_size,ground_height-1e-3f,-1*ground_size}, {1*ground_size,ground_height-1e-3f,1*ground_size}, {-1*ground_size,ground_height-1e-3f,1*ground_size}));
    ground.shader = shaders["mesh_bf"];
    ground.texture_id = texture_wood;


    scene.camera.translation = {0,-25,0};
    scene.camera.orientation = {1,0,0, 0,0,1, 0,1,0};

    create_ants(shaders);
    timer.scale = 0.5f;
}

void scene_model::create_ants(std::map<std::string,GLuint>& shaders)
{
    my_ants.clear();
    for (size_t i = 0; i < nb_ants; i++)
    {
        auto my_ant = Ant();
        my_ant.setup_data(shaders);
        my_ants.push_back(my_ant);
    }
}

void scene_model::frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure&)
{
    timer.update();
    set_gui();

    // Current time
    const float t = timer.t;

    /** *************************************************************  **/
    /** Compute the (animated) transformations applied to the elements **/
    /** *************************************************************  **/
    if (gui_scene.restart)
    {
        create_ants(shaders);
        gui_scene.restart = false;
    }

    for (size_t i = 0; i < nb_ants; i++)
        my_ants[i].update(t);

    /** ********************* **/
    /** Display the hierarchy **/
    /** ********************* **/

    for (size_t i = 0; i < nb_ants; i++)
        my_ants[i].display(gui_scene, scene, shaders);

    // draw ground
    draw(ground, scene.camera);
    glBindTexture(GL_TEXTURE_2D, scene.texture_white);
}

void scene_model::mouse_click(scene_structure& scene, GLFWwindow* window, int button, int action, int mods)
{

    for (size_t i = 0; i < nb_ants; i++)
    {
        if (my_ants[i].isStrucked(scene, window, button, action, mods))
            my_ants[i].die();
    }
}

void scene_model::set_gui()
{
    ImGui::Text("Display: "); ImGui::SameLine();
    ImGui::Checkbox("Restart", &gui_scene.restart);   ImGui::SameLine();

    ImGui::Spacing();
    ImGui::SliderFloat("Time", &timer.t, timer.t_min, timer.t_max);
    ImGui::SliderFloat("Time scale", &timer.scale, 0.1f, 3.0f);

}





#endif

