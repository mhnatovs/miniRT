/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:40:32 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/04/13 16:21:19 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	intersect_object(t_ray ray, t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (intersect_sphere(ray, obj->data.sphere));
	if (obj->type == OBJ_PLANE)
		return (intersect_plane(ray, obj->data.plane));
	if (obj->type == OBJ_CYLINDER)
		return (intersect_cylinder(ray, obj->data.cylinder));
	return (-1);
}

void	hit_normal(t_object *obj, t_hit *hit, t_ray ray)
{
	if (obj->type == OBJ_SPHERE)
		hit->normal = get_normal_sphere(hit->point, obj->data.sphere);
	if (obj->type == OBJ_PLANE)
		hit->normal = get_normal_plane(obj->data.plane, ray);
	if (obj->type == OBJ_CYLINDER)
		hit->normal = get_normal_cylinder(hit->point, obj->data.cylinder);
}

t_hit	trace_ray(t_ray ray, t_scene scene)
{
	return (intersect_primitives(ray, scene.objects));
}

t_hit	intersect_primitives(t_ray ray, t_list *primitives)
{
	t_hit		hit;
	double		t;
	t_list		*curr;
	t_object	*obj;

	hit.t = -1.0;
	hit.obj = NULL;
	curr = primitives;
	while (curr)
	{
		obj = (t_object *)curr->content;
		t = intersect_object(ray, obj);
		if (t > 0.001f && (hit.t < 0 || t < hit.t))
		{
			hit.t = t;
			hit.obj = obj;
			hit.point = vector_add(ray.origin, vector_scale(ray.direction, t));
			hit_normal(obj, &hit, ray);
		}
		curr = curr->next;
	}
	return (hit);
}
