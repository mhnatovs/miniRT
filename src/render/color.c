/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:12:03 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/04/14 11:38:03 by mhnatovs         ###   ########.fr       */
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
	t_vector	l_dir;
	float		brightness;

	l_dir = vector_normalize(vector_substract(light.pos, hit.point));
	brightness = fmax(0.0f, vector_dot(hit.normal, l_dir)) * light.ratio;
	diffuse.r = hit.obj->color.r * light.color.r * brightness;
	diffuse.g = hit.obj->color.g * light.color.g * brightness;
	diffuse.b = hit.obj->color.b * light.color.b * brightness;
	return (diffuse);
}

// Phong specular model -> specular = (R*V)n
// n — shininess exponent, this is number 50 in following formula
// spec = pow(fmax(0.0f, vector_dot(view_dir, reflect_dir)), 50);
// Value of n		Appearance of glare
// low (5–20)		wide, soft glare (matt material)
// medium (30–80)	normal glare (plastic, paint)
// high (100–500)	small, bright glare (polished metal)
// very high (1000+) almost mirror-like glare
// line 96
// ks - mirror reflection coefficient (determines
// how strong the shine on the surface will be)
t_color	apply_specular(t_hit hit, t_light light, t_vector view_dir)
{
	t_vector	l_dir;
	t_vector	reflect_dir;
	float		spec;
	float		ks;
	float		n_dot_l;

	ks = 0.5f;
	l_dir = vector_normalize(vector_substract(light.pos, hit.point));
	n_dot_l = vector_dot(hit.normal, l_dir);
	if (n_dot_l <= 0)
		return ((t_color){0, 0, 0});
	reflect_dir = vector_substract(vector_scale(hit.normal,
				2.0f * n_dot_l), l_dir);
	spec = pow(fmax(0.0f, vector_dot(view_dir, reflect_dir)), 50);
	return ((t_color){
		light.color.r * light.ratio * ks * spec,
		light.color.g * light.ratio * ks * spec,
		light.color.b * light.ratio * ks * spec
	});
}

// calculates the final color at the intersection
// point: ambient + diffuse lighting (including shadows)
t_color	calc_color(t_hit hit, t_scene scene, t_vector view_dir)
{
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	t_color	final;

	ambient = apply_ambient(hit.obj->color, scene.ambient);
	if (in_shadow(hit, scene))
		return (ambient);
	diffuse = apply_diffuse(hit, scene.light);
	specular = apply_specular(hit, scene.light,
			vector_scale(view_dir, -1.0f));
	final.r = ambient.r + diffuse.r + specular.r;
	final.g = ambient.g + diffuse.g + specular.g;
	final.b = ambient.b + diffuse.b + specular.b;
	return (final);
}
