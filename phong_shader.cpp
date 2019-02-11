#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

//using namespace std;

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
	//TODO;
    vec3 color;
    vec3 ambient = color_ambient * world.ambient_intensity * world.ambient_color;
    vec3 diffuse = {0, 0, 0};
    vec3 specular = {0, 0, 0};
    //vec3 lightvec;
    vec3 shadowray;
    vec3 viewray;
    vec3 reflectray;

    //Ray shadowray;
    Light *current;
    Ray shadowray_ray;
    Hit intersection{};
    //Hit intersection{};
    //vec3 shadowrayvec;

    
    for (unsigned i = 0; i < world.lights.size(); i++) {
    	current = world.lights.at(i);
    	shadowray = current->position - intersection_point;
    	shadowray_ray.endpoint = intersection_point;
    	shadowray_ray.direction = (current->position - intersection_point).normalized();
    	viewray = ray.endpoint - intersection_point;
    	reflectray = 2 * dot(shadowray, normal) * normal - shadowray;
    	intersection = world.Closest_Intersection(shadowray_ray);

    	if (!world.enable_shadows || (world.enable_shadows && (!intersection.object || intersection.dist >= shadowray.magnitude()))) {
    		double diff_max = std::max(dot(normal.normalized(), -(intersection_point - (current->position)).normalized()), 0.0);

    		vec3 l = current->position - intersection_point;

    		double spec_max = pow(std::max(dot((intersection_point - ray.endpoint).normalized(), (l - 2 * dot(l, normal) * normal).normalized() ), 0.0), specular_power);

    		diffuse = diffuse + color_diffuse * current->Emitted_Light(intersection_point - current->position) * diff_max;
    		specular = specular + color_specular * current->Emitted_Light(intersection_point - current->position) * spec_max;
    	}
    }

    color = ambient + diffuse + specular;
    
    return color;
}
