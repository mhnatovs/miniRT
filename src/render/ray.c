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

t_ray	make_ray(t_vector source, t_vector direction)
{
	t_ray	ray;
	double	inv_x, inv_y, inv_z;

	ray.origin = source;
	ray.direction = vector_normalize(direction);
	inv_x = (fabs(ray.direction.x) < 1e-6) ? 1e30 : 1.0f / ray.direction.x;
	inv_y = (fabs(ray.direction.y) < 1e-6) ? 1e30 : 1.0f / ray.direction.y;
	inv_z = (fabs(ray.direction.z) < 1e-6) ? 1e30 : 1.0f / ray.direction.z;
	ray.inv_direction = (t_vector){inv_x, inv_y, inv_z};
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
	ray.inv_direction.x = (fabs(ray.direction.x) < 1e-6) ? 1e30 : 1.0f / ray.direction.x;
	ray.inv_direction.y = (fabs(ray.direction.y) < 1e-6) ? 1e30 : 1.0f / ray.direction.y;
	ray.inv_direction.z = (fabs(ray.direction.z) < 1e-6) ? 1e30 : 1.0f / ray.direction.z;
	ray.origin = cam.pos;
	return (ray);
}

t_hit	trace_ray_selection(t_ray ray, t_scene scene)
{
	return (trace_ray(ray, scene));
}
