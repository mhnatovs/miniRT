/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:01:05 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/18 17:32:17 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// converts normalized color (0–1)
// to 32-bit RGBA format and
// limits values to the range 0–255
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

// applies ambient lighting: multiplies the color
// of the object by the color and intensity
// of the ambient light
t_color	apply_ambient(t_color obj_color, t_ambient ambient)
{
	t_color	result;

	result.r = ambient.ratio * ambient.color.r * obj_color.r;
	result.g = ambient.ratio * ambient.color.g * obj_color.g;
	result.b = ambient.ratio * ambient.color.b * obj_color.b;
	return (result);
}

// calculates diffuse lighting (Lambert model)
// based on the angle between the normal
// and the direction to the light source
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

// calculates the final color at the intersection
// point: ambient + diffuse lighting (including shadows)
t_color	calc_color(t_hit hit, t_scene scene)
{
	t_color	ambient;
	t_color	diffuse;
	t_color	final;

	ambient = apply_ambient(hit.obj->color, scene.ambient);
	if (in_shadow(hit, scene))
		return (ambient);
	diffuse = apply_diffuse(hit, scene.light);
	final.r = ambient.r + diffuse.r;
	final.g = ambient.g + diffuse.g;
	final.b = ambient.b + diffuse.b;
	return (final);
}
