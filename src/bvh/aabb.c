/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 20:12:27 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/04 10:38:40 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_aabb	get_cylinder_aabb(t_cylinder *cyl)
{
	t_aabb		box;
	t_vector	top;
	t_vector	rad;

	top = vector_add(cyl->base, vector_scale(cyl->dir, cyl->height));
	box.min.x = fmin(cyl->base.x, top.x);
	box.min.y = fmin(cyl->base.y, top.y);
	box.min.z = fmin(cyl->base.z, top.z);
	box.max.x = fmax(cyl->base.x, top.x);
	box.max.y = fmax(cyl->base.y, top.y);
	box.max.z = fmax(cyl->base.z, top.z);
	rad = (t_vector){cyl->radius, cyl->radius, cyl->radius};
	box.min = vector_substract(box.min, rad);
	box.max = vector_add(box.max, rad);
	return (box);
}

t_aabb	get_object_aabb(t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (get_sphere_aabb(&obj->data.sphere));
	if (obj->type == OBJ_CYLINDER)
		return (get_cylinder_aabb(&obj->data.cylinder));
	if (obj->type == OBJ_PLANE)
	{
		return ((t_aabb){(t_vector){-1e30, -1e30, -1e30},
			(t_vector){1e30, 1e30, 1e30}});
	}
	return ((t_aabb){(t_vector){0, 0, 0}, (t_vector){0, 0, 0}});
}
