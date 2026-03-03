#include "bvh.h"
#include "minirt.h"

t_aabb	get_sphere_aabb(t_sphere *sphere)
{
	t_aabb		box;
	t_vector	r_vec;

	r_vec = (t_vector){sphere->radius, sphere->radius, sphere->radius};
	box.min = vector_substract(sphere->center, r_vec);
	box.max = vector_add(sphere->center, r_vec);
	return (box);
}

t_aabb	get_plane_aabb(t_plane *plane)
{
	t_aabb	box;
	float	infinity;
	(void)plane;
	infinity = 1e30f;
	box.min = (t_vector){-infinity, -infinity, -infinity};
	box.max = (t_vector){infinity, infinity, infinity};
	return (box);
}

t_aabb	get_cylinder_aabb(t_cylinder *cyl)
{
	t_aabb		box;
	t_vector	top_center;
	t_vector	bottom_center;
	t_vector	axis_min;
	t_vector	axis_max;
	t_vector	radius_vec;

	bottom_center = cyl->base;
	top_center = vector_add(cyl->base, vector_scale(cyl->dir, cyl->height));
	axis_min.x = fmin(bottom_center.x, top_center.x);
	axis_min.y = fmin(bottom_center.y, top_center.y);
	axis_min.z = fmin(bottom_center.z, top_center.z);
	axis_max.x = fmax(bottom_center.x, top_center.x);
	axis_max.y = fmax(bottom_center.y, top_center.y);
	axis_max.z = fmax(bottom_center.z, top_center.z);
	radius_vec = (t_vector){cyl->radius, cyl->radius, cyl->radius};
	box.min = vector_substract(axis_min, radius_vec);
	box.max = vector_add(axis_max, radius_vec);
	return (box);
}

t_aabb	get_object_aabb(t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (get_sphere_aabb(&obj->data.sphere));
	else if (obj->type == OBJ_PLANE)
		return (get_plane_aabb(&obj->data.plane));
	else if (obj->type == OBJ_CYLINDER)
		return (get_cylinder_aabb(&obj->data.cylinder));
	return ((t_aabb){{0, 0, 0}, {0, 0, 0}});
}

t_aabb	combine_aabbs(t_aabb box1, t_aabb box2)
{
	t_aabb	box;

	box.min.x = fmin(box1.min.x, box2.min.x);
	box.min.y = fmin(box1.min.y, box2.min.y);
	box.min.z = fmin(box1.min.z, box2.min.z);
	box.max.x = fmax(box1.max.x, box2.max.x);
	box.max.y = fmax(box1.max.y, box2.max.y);
	box.max.z = fmax(box1.max.z, box2.max.z);
	return (box);
}

t_vector	get_aabb_center(t_aabb box)
{
	t_vector	center;

	center.x = (box.min.x + box.max.x) * 0.5f;
	center.y = (box.min.y + box.max.y) * 0.5f;
	center.z = (box.min.z + box.max.z) * 0.5f;
	return (center);
}
