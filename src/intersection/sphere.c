/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:35:30 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/04/14 12:15:20 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t[0] - entry hit
// t[1] - exit hit
// tca - distance along the ray to the point closest to the sphere center
// thc - half chord length
float	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_vector	ray_to_sphere;
	float		tca;
	float		dist2;
	float		thc;
	float		t[2];

	ray_to_sphere = vector_substract(sphere.center, ray.origin);
	tca = vector_dot(ray_to_sphere, ray.direction);
	dist2 = vector_dot(ray_to_sphere, ray_to_sphere) - tca * tca;
	if (dist2 > sphere.radius * sphere.radius)
		return (-1.0);
	thc = sqrt(sphere.radius * sphere.radius - dist2);
	t[0] = tca - thc;
	t[1] = tca + thc;
	if (t[0] > 0.001f)
		return (t[0]);
	if (t[1] > 0.001f)
		return (t[1]);
	return (-1.0);
}

t_vector	get_normal_sphere(t_vector hit_point, t_sphere sphere)
{
	t_vector	normal;

	normal = vector_substract(hit_point, sphere.center);
	normal = vector_normalize(normal);
	return (normal);
}
