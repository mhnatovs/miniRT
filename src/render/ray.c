/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:09:34 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/03/05 12:09:36 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	safe_inv(float d)
{
	if (fabs(d) < 1e-6)
		return (1e30);
	return (1.0f / d);
}

static void	set_inv_direction(t_ray *ray)
{
	ray->inv_direction.x = safe_inv(ray->direction.x);
	ray->inv_direction.y = safe_inv(ray->direction.y);
	ray->inv_direction.z = safe_inv(ray->direction.z);
}

t_ray	make_ray(t_vector source, t_vector direction)
{
	t_ray	ray;

	ray.origin = source;
	ray.direction = vector_normalize(direction);
	set_inv_direction(&ray);
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
	set_inv_direction(&ray);
	ray.origin = cam.pos;
	return (ray);
}

t_hit	trace_ray_selection(t_ray ray, t_scene scene)
{
	return (trace_ray(ray, scene));
}
