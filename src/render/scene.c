/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 13:29:52 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/03/03 13:36:43 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	intersect_object(t_ray ray, t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (intersect_sphere(ray, obj->data.sphere));
	if (obj->type == OBJ_PLANE)
		return (intersect_plane(ray, obj->data.plane));
	if (obj->type == OBJ_CYLINDER)
		return (intersect_cylinder(ray, obj->data.cylinder));
	return (-1);
}

void	hit_normal(t_object *obj, t_hit *hit)
{
	if (obj->type == OBJ_SPHERE)
		hit->normal = get_normal_sphere(hit->point, obj->data.sphere);
	if (obj->type == OBJ_PLANE)
		hit->normal = get_normal_plane(obj->data.plane);
	if (obj->type == OBJ_CYLINDER)
		hit->normal = get_normal_cylinder(hit->point, obj->data.cylinder);
}

t_hit	trace_ray(t_ray ray, t_scene scene)
{
	return (traverse_bvh(ray, scene.objects));
}

uint32_t	get_pixel_color(t_scene scene, t_viewport vp, t_point p)
{
	t_ray		ray;
	t_hit		hit;
	uint32_t	color;

	ray = generate_ray(scene.camera, vp, p.x, p.y);
	hit = trace_ray(ray, scene);
	if (hit.t > 0)
		color = color_to_int(calc_color(hit, scene));
	else
		color = 0x000000FF;
	return (color);
}

void	render_scene(mlx_image_t *img, t_scene scene, int step)
{
	t_viewport	vp;
	t_point		p;
	uint32_t	color;
	int			i;
	int			j;

	p.y = 0;
	vp = init_viewport(scene.camera);
	while (p.y < HEIGHT)
	{
		p.x = 0;
		while (p.x < WIDTH)
		{
			color = get_pixel_color(scene, vp, p);
			i = 0;
			while (i < step && (p.y + i) < HEIGHT)
			{
				j = 0;
				while (j < step && (p.x + j) < WIDTH)
				{
					if (step > 1)
						mlx_put_pixel(img, p.x + j, p.y + i, color);
					else
						mlx_put_pixel(img, p.x, p.y, color);
					j++;
				}
				i++;
			}
			p.x += step;
		}
		p.y += step;
	}
}
