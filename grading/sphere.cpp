#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    double a = 1;
    double b = 2 * dot(ray.direction, ray.endpoint - center);
    double c = dot(ray.endpoint - center, ray.endpoint - center) - (radius * radius);
    double discriminant = (b * b) - (4 * a * c);
    double t = 0;
    double t1 = 0;
    double t2 = 0;

    if (discriminant == 0) {
    	t = 0.5 * -b / a;
    }

    else if (discriminant > 0) {
    	t1 = 0.5 * (-b + sqrt(discriminant)) / a;
    	t2 = 0.5 * (-b - sqrt(discriminant)) / a;
    	t = (t1 >= t2) ? t1 : t2;
    }

    if (t >= small_t) {
    	return {this, t, part};
    }

    return {0,0,0};
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    //TODO; // compute the normal direction
    normal = (point - center).normalized();

    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
