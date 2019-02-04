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

    Ray shadowray;
    Light *current;
    //Hit intersection{};
    //vec3 shadowrayvec;

    for (unsigned i = 0; i < world.lights.size(); i++) {
    	current = world.lights.at(i);

    	double diff_max = std::max(dot(normal.normalized(), -(intersection_point - (current->position)).normalized()), 0.0);

    	vec3 l = current->position - intersection_point;

    	double spec_max = pow(std::max(dot((intersection_point - ray.endpoint).normalized(), (l - 2 * dot(l, normal) * normal).normalized() ), 0.0), specular_power);

    	diffuse = diffuse + color_diffuse * current->Emitted_Light(intersection_point - current->position) * diff_max;
    	specular = specular + color_specular * current->Emitted_Light(intersection_point - current->position) * spec_max;
    	/*shadowray.endpoint = intersection_point;
    	shadowray.direction = (current->position - intersection_point).normalized();
    	vec3 lightvec = current->position - intersection_point;*/

    	/*if (world.Closest_Intersection(shadowray).object == NULL || (current->position - intersection_point).magnitude() < world.Closest_Intersection(shadowray).dist) {
    		diffuse += color_diffuse * current->Emitted_Light(lightvec) * max(dot(shadowray.direction, normal), 0.0);
    		vec3 view = -(ray.direction);
    		vec3 reflect = ray.direction - 2 * (dot(ray.direction, normal)) * normal;
    		specular += color_specular * current->Emitted_Light(lightvec) * pow(max(dot(view, reflect), 0.0), specular_power);
    	}*/
    }

    color = ambient + diffuse + specular;
    
    return color;
}
