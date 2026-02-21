/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:13:15 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/21 11:24:34 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	make_ray(t_vector source, t_vector dir)
{
	t_ray	ray;

	ray.origin = source;
	ray.direction = vector_normalize(dir);
	return (ray);
}

t_ray	generate_ray(t_camera cam, t_viewport v, int x, int y)
{
	t_ray		ray;
	float		screen_x;
	float		screen_y;

	screen_x = (2.0 * x / WIDTH) - 1.0;
	screen_y = 1.0 - (2.0 * y / HEIGHT);
	screen_x *= v.aspect_ratio * v.fov_scale;
	screen_y *= v.fov_scale;
	ray.direction = v.forward;
	ray.direction = vector_add(ray.direction, vector_scale(v.right, screen_x));
	ray.direction = vector_add(ray.direction, vector_scale(v.up, screen_y));
	ray.direction = vector_normalize(ray.direction);
	ray.origin = cam.pos;
	return (ray);
}

static void	update_hit(t_hit *h, t_object *obj, t_ray ray, double t)
{
	if (h->obj == NULL || t < h->t)
	{
		h->t = t;
		h->obj = obj;
		h->point = vector_add(ray.origin, vector_scale(ray.direction, t));
		hit_normal(obj, h);
	}
}

t_hit	trace_ray_selection(t_ray ray, t_scene scene)
{
	t_list	*node;
	double	t;
	t_hit	hit[2];

	node = scene.objects;
	hit[0].t = -1.0;
	hit[0].obj = NULL;
	hit[1].t = -1.0;
	hit[1].obj = NULL;
	while (node)
	{
		t = intersect_object(ray, node->content);
		if (t > 0)
		{
			if (((t_object *)node->content)->type == OBJ_PLANE)
				update_hit(&hit[1], node->content, ray, t);
			else
				update_hit(&hit[0], node->content, ray, t);
		}
		node = node->next;
	}
	if (hit[0].obj)
		return (hit[0]);
	return (hit[1]);
}
