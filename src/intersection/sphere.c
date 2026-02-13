/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:13:57 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/13 15:52:18 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// vec_oc - origin center;
// coef[0] = length of the ray direction (usually 1 if normalized)
// coef[1] = how much the ray is pointing toward the sphere (oc · direction * 2)
// coef[2] = distance from ray origin to sphere center minus radius squared

float	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_vector	oc;
	float		coef[3];
	float		t;

	oc = vector_substract(ray.origin, sphere.center);
	coef[0] = vector_dot(ray.direction, ray.direction);
	coef[1] = 2.0 * vector_dot(oc, ray.direction);
	coef[2] = vector_dot(oc, oc) - sphere.radius * sphere.radius;
	t = coef[1] * coef[1] - 4 * coef[0] * coef[2];
	if (t < 0)
		return (-1.0);
	t = (-coef[1] - sqrt(t)) / (2.0 * coef[0]);
	if (t < 0)
		t = (-coef[1] + sqrt(t)) / (2.0 * coef[0]);
	if (t >= 0)
		return (t);
	return (-1.0);
}
