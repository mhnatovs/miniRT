/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:48:56 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/17 15:52:10 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	in_shadow(t_hit hit, t_scene scene)
{
	t_ray		shadow_ray;
	t_vector	to_light;
	float		distance_to_light;
	t_hit		shadow_hit;
	t_vector	offset;

	to_light = vector_substract(scene.light.pos, hit.point);
	distance_to_light = vector_length(to_light);
	shadow_ray.direction = vector_normalize(to_light);
	offset = vector_scale(hit.normal, 0.001);
	shadow_ray.origin = vector_add(hit.point, offset);
	shadow_hit = trace_ray(shadow_ray, scene);
	if (shadow_hit.t > 0 && shadow_hit.t < distance_to_light)
		return (1);
	return (0);
}
