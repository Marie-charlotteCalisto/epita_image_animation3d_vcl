#include "project.hpp"

#ifdef SCENE_PROJECT


using namespace vcl;



void scene_model::setup_data(std::map<std::string,GLuint>& shaders, scene_structure& , gui_structure& )
{

    float ground_height = -0.3f;
    float ground_size = 10.0f;
    auto texture_wood = create_texture_gpu(image_load_png("../scenes/animation/02_simulation/assets/wood.png"));
    ground = mesh_drawable(mesh_primitive_quad({-1*ground_size,ground_height-1e-3f,-1*ground_size}, {1*ground_size,ground_height-1e-3f,-1*ground_size}, {1*ground_size,ground_height-1e-3f,1*ground_size}, {-1*ground_size,ground_height-1e-3f,1*ground_size}));
    ground.shader = shaders["mesh_bf"];
    ground.texture_id = texture_wood;


    my_ant = Ant();
    my_ant.setup_data(shaders);
    timer.scale = 0.5f;
}



void scene_model::frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& )
{
    timer.update();
    set_gui();

    // Current time
    const float t = timer.t;

    /** *************************************************************  **/
    /** Compute the (animated) transformations applied to the elements **/
    /** *************************************************************  **/
    my_ant.update(t);

    /** ********************* **/
    /** Display the hierarchy **/
    /** ********************* **/
    my_ant.display(gui_scene, scene, shaders);


    // draw ground
    draw(ground, scene.camera);
    glBindTexture(GL_TEXTURE_2D, scene.texture_white);
}

void scene_model::mouse_click(scene_structure& scene, GLFWwindow* window, int button, int action, int mods)
{
    if (my_ant.isStrucked(scene, window, button, action, mods))
        my_ant.die();
}

void scene_model::set_gui()
{
    ImGui::Text("Display: "); ImGui::SameLine();
    ImGui::Checkbox("Wireframe", &gui_scene.wireframe); ImGui::SameLine();
    ImGui::Checkbox("Surface", &gui_scene.surface);     ImGui::SameLine();
    ImGui::Checkbox("Skeleton", &gui_scene.skeleton);   ImGui::SameLine();

    ImGui::Spacing();
    ImGui::SliderFloat("Time", &timer.t, timer.t_min, timer.t_max);
    ImGui::SliderFloat("Time scale", &timer.scale, 0.1f, 3.0f);

}





#endif

