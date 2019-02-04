#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;

    double a = dot(ray.direction,ray.direction);
    double b = 2 * dot(ray.direction, ray.endpoint - this->center);
    double c = dot(ray.endpoint - this->center, ray.endpoint - this->center) - (this->radius * this->radius);

    double discriminant = (b * b) - (4 * a * c);
    double t = 0;
    double t1 = 0;
    double t2 = 0;

    if (discriminant == 0) {
    	t = (-1 * b) / (2 * a);
    }

    else if (discriminant > 0) {
    	t1 = ((-1 * b) + sqrt(discriminant)) / (2 * a);
    	t2 = ((-1 * b) - sqrt(discriminant)) / (2 * a);
    	t = (t1 < t2) ? t1 : t2;
    }

    if (t >= small_t) {
    	return {this, t, part};
    }

    return {NULL,0,part};
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
