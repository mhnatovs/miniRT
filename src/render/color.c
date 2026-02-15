/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:01:05 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/15 11:25:25 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint32_t	color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(color.r * 255);
	g = (int)(color.g * 255);
	b = (int)(color.b * 255);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

t_color	apply_ambient(t_color obj_color, t_ambient ambient)
{
	t_color	result;

	result.r = ambient.ratio * ambient.color.r * obj_color.r;
	result.g = ambient.ratio * ambient.color.g * obj_color.g;
	result.b = ambient.ratio * ambient.color.b * obj_color.b;
	return (result);
}

t_color	apply_diffuse(t_hit hit, t_light light)
{
	t_color		diffuse;
	t_vector	light_dir;
	float		brightness;

	light_dir = vector_substract(light.pos, hit.point);
	light_dir = vector_normalize(light_dir);
	brightness = vector_dot(hit.normal, light_dir);
	if (brightness < 0)
		brightness = 0;
	brightness *= light.ratio;
	diffuse.r = hit.obj->color.r * light.color.r * brightness;
	diffuse.g = hit.obj->color.g * light.color.g * brightness;
	diffuse.b = hit.obj->color.b * light.color.b * brightness;
	return (diffuse);
}
