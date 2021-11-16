#include "ant.hpp"

#ifdef SCENE_PROJECT

using namespace vcl;

Ant::Ant(){
    ant_blood = Blood();
}

void Ant::setup_data(std::map<std::string, GLuint>& shaders)
{

    ant_blood.setup_data(shaders);

    const float radius_head = 0.20f;
    const float radius_neck = 0.15f;
    const float radius_body = 0.25f;
    const float radius_leg = 0.02f;
    const float length_leg = 0.3f;


    //head
    mesh_drawable head = mesh_drawable( mesh_primitive_sphere(radius_head, {0,0,0}, 40, 40));
    head.uniform.transform.scaling_axis = {1, 0.7f, 1.0f};
    head.uniform.color = {0.7f,0.2f,0.2f};

    //neck
    mesh_drawable neck = mesh_drawable( mesh_primitive_sphere(radius_neck, {0,0,0}, 20, 20));
    neck.uniform.transform.scaling_axis = {0.6f, 0.5f, 1.0f};
    mat3 const r_neck = rotation_from_axis_angle_mat3({1,0,0},-0.5f);
    neck.uniform.transform.rotation = r_neck;
    neck.uniform.color = {0.7f,0.2f,0.2f};


    //body
    mesh_drawable body = mesh_drawable( mesh_primitive_sphere(radius_body, {0,0,0}, 40, 40));
    body.uniform.transform.scaling_axis = {0.7f, 0.7f, 1};
    body.uniform.color = {0.7f,0.2f,0.2f};
    //body_join
    mesh_drawable body_join = mesh_drawable( mesh_primitive_sphere(radius_neck, {0,0,0}, 20, 20));
    body_join.uniform.transform.scaling_axis = {0.6f, 0.6f, 1.0f};
    body_join.uniform.color = {0.7f,0.2f,0.2f};


    //bottom
    mesh_drawable butt = mesh_drawable( mesh_primitive_sphere(radius_body, {0,0,0}, 40, 40));
    butt.uniform.transform.scaling_axis = {1, 1, 1.5f};
    mat3 const r_butt = rotation_from_axis_angle_mat3({1,0,0},0.1f);// std::sin(2*3.14f*(t-0.4f)) );
    butt.uniform.transform.rotation = r_butt;
    butt.uniform.color = {0.7f,0.2f,0.2f};


    //antenna
    mesh_drawable antenna = mesh_primitive_cylinder(0.01f, {0,0,0}, {-0.4,0,0});
    mat3 const r_antenna = rotation_from_axis_angle_mat3({0,-0.4f,1},-0.9f);// std::sin(2*3.14f*(t-0.4f)) );
    antenna.uniform.transform.rotation = r_antenna;
    antenna.uniform.color = {0.7f,0.2f,0.2f};
    //antenna_join
    mesh_drawable antenna_join = mesh_primitive_sphere(0.015f);
    antenna_join.uniform.color = {0.7f,0.2f,0.2f};



    //mouth
    mesh_drawable mandible = mesh_drawable(mesh_primitive_cone(0.05f, {0,0,0},{0.05f,0,0.2f}));
    mandible.uniform.transform.scaling_axis = {1, 0.7, 1};
    mandible.uniform.color = {0.7f,0.25f,0.2f};


    //eyes
    mesh_drawable eye = mesh_drawable(mesh_primitive_sphere(0.05f, {0,0,0}, 20, 20));
    eye.uniform.color = {0,0,0};
    //white in eyes
    mesh_drawable eye_white = mesh_drawable(mesh_primitive_sphere(0.01f, {0,0,0}, 20, 20));
    eye_white.uniform.color = {1,1,1};



    //shoulder
    mesh_drawable shoulder = mesh_primitive_cylinder(radius_leg, {0,0,0}, {-length_leg,0,0});
    mat3 const r_shoulder = rotation_from_axis_angle_mat3({0,0,1},-0.9f);
    shoulder.uniform.transform.rotation = r_shoulder;
    shoulder.uniform.color = {0.7f,0.2f,0.2f};

    //leg
    mesh_drawable leg = mesh_primitive_cylinder(radius_leg, {0,0,0}, {-(length_leg+0.1)/1.5f,-(length_leg+0.1)/1.0f,0});
    leg.uniform.color = {0.7f,0.2f,0.2f};
    //back_leg
    mesh_drawable back_leg = mesh_primitive_cylinder(radius_leg, {0,0,0}, {-(length_leg+0.15)/1.5f,-(length_leg+0.15)/1.0f,0});
    back_leg.uniform.color = {0.75f,0.2f,0.2f};

    //elbow
    mesh_drawable elbow = mesh_primitive_sphere(0.03f);
    elbow.uniform.color = {0.7f,0.2f,0.2f};


    // Build the hierarchy:
        //body
    hierarchy.add(body, "body");

    hierarchy.add(body_join, "body_join1", "body" , vec3( 0, 0, -0.2f));
    hierarchy.add(body_join, "body_join2", "body_join1" , vec3( 0, 0, -0.1f));
    hierarchy.add(body_join, "body_join3", "body_join2" , vec3( 0, 0, -0.1f));

        //bottom
    hierarchy.add(butt, "butt", "body_join3" , vec3( 0, 0.1f, -0.3f));

        //neck
    hierarchy.add(neck, "neck", "body" , radius_body * vec3( 0, 0.4f, 1.0f));

        //head
    hierarchy.add(head, "head", "neck" , radius_neck * vec3( 0, 0.6f, 1.0f));

        //antenna
    hierarchy.add(antenna, "antenna_left", "head" , radius_head * vec3( 0.2f, -0.2f, 1/1.5f));
    hierarchy.add(antenna, "antenna_right", "head" , {{radius_head * vec3( -0.2f, -0.2f, 1/1.5f)}, {-1,0,0, 0,1,0, 0,0,1}/*Symmetry*/ });
    hierarchy.add(antenna_join, "antenna_join_left", "antenna_left" , {-0.255,0.3,0.12});
    hierarchy.add(antenna_join, "antenna_join_right", "antenna_right" , {-0.255,0.3,0.12});
    hierarchy.add(antenna, "antenna_bottom_left", "antenna_join_left", {{0,0,0}, {1,0,0, 0,-1,0, 0,0,1}});
    hierarchy.add(antenna, "antenna_bottom_right", "antenna_join_right", {{0,0,0}, {1,0,0, 0,-1,0, 0,0,1}});

        //mouth
    hierarchy.add(mandible, "mandible_left", "head" , radius_head * vec3(-0.4f, -0.2f, 1/1.5f));
    hierarchy.add(mandible, "mandible_right", "head" , {{radius_head * vec3(0.4f, -0.2f, 1/1.5f)}, {-1,0,0, 0,1,0, 0,0,1}/*Symmetry*/ });

        //eyes
    hierarchy.add(eye, "eye_left", "head" , radius_head * vec3( 0.5f, 0.3f, 0.4f));
    hierarchy.add(eye, "eye_right", "head", radius_head * vec3(-0.5f, 0.3f, 0.4f));
    hierarchy.add(eye_white, "eye_white_left", "eye_left" , 0.05f * vec3( 0.5f, 0.4f, 0.5f));
    hierarchy.add(eye_white, "eye_white_right", "eye_right", 0.05f * vec3(-0.5f, 0.4f, 0.5f));



    // Set the left part of the body leg: shoulder-elbow-leg
        //leg_left 1
    hierarchy.add(elbow, "shoulder11_left", "body", {-radius_body+0.13f,-0.1f,0.1f});
    hierarchy.add(shoulder, "shoulder1_left", "shoulder11_left", {0,0,0});
    hierarchy.add(elbow, "elbow1_left", "shoulder1_left", {-length_leg+0.12f,0.22f,0});
    hierarchy.add(leg, "leg_bottom1_left", "elbow1_left");

        //leg_left 2
    hierarchy.add(elbow, "shoulder21_left", "body", {-radius_body+0.13f,-0.1f,-0.1});
    hierarchy.add(shoulder, "shoulder2_left", "shoulder21_left", {0,0,0});
    hierarchy.add(elbow, "elbow2_left", "shoulder2_left", {-length_leg+0.12f,0.22f,0});
    hierarchy.add(leg, "leg_bottom2_left", "elbow2_left");

        //leg_left 3
    hierarchy.add(elbow, "shoulder31_left", "body_join2", {-0.08f,-0.05f,0});
    hierarchy.add(shoulder, "shoulder3_left", "shoulder31_left", {0,0,0});
    hierarchy.add(elbow, "elbow3_left", "shoulder3_left", {-length_leg+0.12f,0.22f,0});
    hierarchy.add(back_leg, "leg_bottom3_left", "elbow3_left");



    // Set the right part of the body leg: similar to the left part excepted a symmetry is applied along x direction for the shoulder
        //leg_right 1
    hierarchy.add(elbow, "shoulder11_right", "body", {{radius_body-0.13f,0-0.1f,0.1f}, {-1,0,0, 0,1,0, 0,0,1}/*Symmetry*/ } );
    hierarchy.add(shoulder, "shoulder1_right", "shoulder11_right", {0,0,0});
    hierarchy.add(elbow, "elbow1_right", "shoulder1_right", {-length_leg+0.12,0.22,0});
    hierarchy.add(leg, "leg_bottom1_right", "elbow1_right");

        //leg_right 2
    hierarchy.add(elbow, "shoulder21_right", "body", {{radius_body-0.13f,0-0.1f,-0.1}, {-1,0,0, 0,1,0, 0,0,1}/*Symmetry*/ } );
    hierarchy.add(shoulder, "shoulder2_right", "shoulder21_right", {0,0,0});
    hierarchy.add(elbow, "elbow2_right", "shoulder2_right", {-length_leg+0.12,0.22,0});
    hierarchy.add(leg, "leg_bottom2_right", "elbow2_right");

        //leg_right 3
    hierarchy.add(elbow, "shoulder31_right", "body_join2", {0.08f,-0.05f,0});
    hierarchy.add(shoulder, "shoulder3_right", "shoulder31_right", {0,0,0});
    hierarchy.add(elbow, "elbow3_right", "shoulder3_right", {-length_leg+0.12,0.22,0});
    hierarchy.add(back_leg, "leg_bottom3_right", "elbow3_right");



    // Set the same shader for all the elements
    hierarchy.set_shader_for_all_elements(shaders["mesh"]);

    random = -9.5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(9.5+9.5)));

    // Initialize helper structure to display the hierarchy skeleton
    hierarchy_visual_debug.init(shaders["segment_im"], shaders["mesh"]);

}

bool Ant::isStrucked(scene_structure& scene, GLFWwindow* window, int button, int action, int mods)
{
    // Cursor coordinates
    const vec2 cursor = glfw_cursor_coordinates_window(window);

    // Check that the mouse is clicked (drag and drop)
    const bool mouse_click_left  = glfw_mouse_pressed_left(window);

    // Check if shift key is pressed
    if(mouse_click_left)
    {
        // Create the 3D ray passing by the selected point on the screen
        const ray r = picking_ray(scene.camera, cursor);

        // Check if this ray intersects a position (represented by a sphere)
        const vec3 c = hierarchy["body"].transform.translation;
        const picking_info info = ray_intersect_sphere(r, c, 1);

        if( info.picking_valid ) // the ray intersects a sphere
        {
            return true;
        }
    }
    return false;
}



void Ant::die()
{
    isDead = true;
}

void Ant::update_dead()
{
    const size_t N = hierarchy.elements.size();
    for(size_t k=0; k<N; ++k)
        hierarchy.elements[k].element.uniform.transform.scaling_axis = {1, 0.1, 1};
   for(size_t k=0; k<N; ++k)
        hierarchy.elements[k].element.uniform.transform.scaling_axis = {1, 1, 1};

}


void Ant::update(const float t)
{
    if (isDead)
    {
        update_dead();
        ant_blood.spawn(hierarchy["body"].transform.translation, t);
        return;
    }


    auto t_rand = fmod(t+fabs(random), 1.0);
    auto move = vcl::vec3(0,0,(t_rand*20 - 10));
    hierarchy["body"].transform.translation = vcl::vec3(random, 0, 0) + move;

    //neck rotate on the y axis
    mat3 const R_head = rotation_from_axis_angle_mat3({0,1,0}, std::sin(2*3.14f*(t-0.4f))/5 );
    hierarchy["neck"].transform.rotation = R_head;

    mat3 const R_antenna_l = rotation_from_axis_angle_mat3({0,1,0}, std::sin(2*3.14f*(t-0.4f))/5 );
    mat3 const R_antenna_bot_l = rotation_from_axis_angle_mat3({0,1,0}, -std::sin(2*3.14f*(t-0.6f)) );

    mat3 const R_antenna_r = rotation_from_axis_angle_mat3({0,1,0}, std::cos(2*3.14f*(t-0.4f))/5 );
    mat3 const R_antenna_bot_r = rotation_from_axis_angle_mat3({0,1,0}, -std::cos(2*3.14f*(t-0.6f)) );



    mat3 const Symmetry = {-1,0,0, 0,1,0, 0,0,1};
    //symetrie for antennas
    mat3 const sym = {1,0,0, 0,-1,0, 0,0,1};

    // Set the rotation to the elements in the hierarchy
    hierarchy["antenna_left"].transform.rotation = R_antenna_l;
    hierarchy["antenna_bottom_left"].transform.rotation = sym*R_antenna_bot_l;

    hierarchy["antenna_right"].transform.rotation = Symmetry*R_antenna_r;
    hierarchy["antenna_bottom_right"].transform.rotation = sym*R_antenna_bot_r;



    //move the legs
    auto rotation_sin = 0.3*std::sin(2*3.14f*(2*t+0.1));
    auto rotation_sin_shift = 0.3f*-std::sin(2*3.14f*(2*t));
    auto rotation_cos = 0.3f*std::cos(2*3.14f*(2*t+0.1));
    auto rotation_cos_shift = -0.3f*std::cos(2*3.14f*(2*t));


    //rotation for left
    mat3 const R_shoulder_l = rotation_from_axis_angle_mat3({0,1,0},rotation_sin );
    mat3 const R_leg_l = rotation_from_axis_angle_mat3({0,1,0}, rotation_sin_shift );

    hierarchy["shoulder11_left"].transform.rotation = R_shoulder_l;
    hierarchy["leg_bottom1_left"].transform.rotation = R_leg_l;

    hierarchy["shoulder21_left"].transform.rotation = Symmetry*sym*(-R_shoulder_l);
    hierarchy["leg_bottom2_left"].transform.rotation = R_leg_l;

    hierarchy["shoulder31_left"].transform.rotation = R_shoulder_l;
    hierarchy["leg_bottom3_left"].transform.rotation = R_leg_l;


    //rotation for right
    mat3 const R_shoulder2_l = rotation_from_axis_angle_mat3({0,1,0}, rotation_cos);
    mat3 const R_leg2_l = rotation_from_axis_angle_mat3({0,1,0}, rotation_cos_shift);

    hierarchy["shoulder11_right"].transform.rotation = Symmetry*R_shoulder2_l;
    hierarchy["leg_bottom1_right"].transform.rotation = R_leg2_l;

    hierarchy["shoulder21_right"].transform.rotation = sym*(-R_shoulder2_l);
    hierarchy["leg_bottom2_right"].transform.rotation = R_leg2_l;

    hierarchy["shoulder31_right"].transform.rotation = Symmetry*R_shoulder2_l;
    hierarchy["leg_bottom3_right"].transform.rotation = R_leg2_l;



    hierarchy.update_local_to_global_coordinates();


}

void Ant::display(gui_scene_structure gui_scene, scene_structure& scene, std::map<std::string, GLuint>& shaders)
{

    draw(hierarchy, scene.camera);
    if (isDead)
        ant_blood.display(scene);

}
#endif

