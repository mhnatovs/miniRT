/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:13:57 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/13 14:04:25 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// vec_oc - vector origin center; t - distance
float	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_vector	vec_oc;
	float	a,b,c;
	float	discriminant;
	float	t;

	vec_oc = vector_substract(ray.origin, sphere.center);
	a = vector_dot(ray.direction, ray.direction);
	b = 2.0 * vector_dot(vec_oc, ray.direction);
	c = vector_dot(vec_oc, vec_oc) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	return (t);
}