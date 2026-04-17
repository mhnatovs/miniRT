/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:09:34 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/04/14 13:50:15 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	make_ray(t_vector source, t_vector direction)
{
	t_ray	ray;

	ray.origin = source;
	ray.direction = vector_normalize(direction);
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
