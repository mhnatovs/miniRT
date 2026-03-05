/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyan <jiyan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:13:57 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/03/04 20:50:33 by jiyan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// coef[0] = length of the ray direction (usually 1 if normalized)
// coef[1] = how much the ray is pointing toward the sphere (oc · direction * 2)
// coef[2] = distance from ray origin to sphere center minus radius squared
float	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_vector	l;
	float		tca;
	float		d2;
	float		thc;
	float		t[2];

	l = vector_substract(sphere.center, ray.origin);
	tca = vector_dot(l, ray.direction);
	d2 = vector_dot(l, l) - tca * tca;
	if (d2 > sphere.radius * sphere.radius)
		return (-1.0);
	thc = sqrt(sphere.radius * sphere.radius - d2);
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
