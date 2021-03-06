#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"
#include <iterator>

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    //TODO;
    double min_t = std::numeric_limits<double>::max();
    Hit little_hit{};
    for (unsigned i = 0; i < objects.size(); i++) {
        Hit h2 = objects[i]->Intersection(ray, -1);
        if ((h2.object != NULL) && (h2.dist < min_t) && (h2.dist >= small_t)) {
            min_t = h2.dist;
            little_hit = h2;
        }
    }
    return little_hit;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    //TODO; // set up the initial view ray here
    Ray ray(camera.position, (camera.World_Position(pixel_index) - camera.position).normalized());

    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    Hit h2 = Closest_Intersection(ray);
    vec3 color;
    if (h2.object != NULL) {
        //vec3 int_ptr = ray.Point(h2.dist);
        color = h2.object->material_shader->Shade_Surface(ray, ray.Point(h2.dist), h2.object->Normal(ray.Point(h2.dist), -1), recursion_depth);
    }

    else {
        //Ray temp;
        vec3 tempvector = vec3(0, 0, 0);
        color = background_shader->Shade_Surface(ray, tempvector, tempvector, recursion_depth);
    }

    //TODO; // determine the color here
    //unfinished & get help
    return color;
}

void Render_World::Initialize_Hierarchy()
{
    TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
