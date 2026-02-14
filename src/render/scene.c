/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:27:40 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/14 18:31:10 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	intersect_object(t_ray ray, t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (intersect_sphere(ray, obj->data.sphere));
	// if (obj->type == OBJ_PLANE)
	// 	return (intersect_plane(ray, obj->data.plane));
	// if (obj->type == OBJ_CYLINDER)
	// 	return (intersect_cylinder(ray, obj->data.cylinder));
	return (-1);
}

t_hit	trace_ray(t_ray ray, t_scene scene)
{
	t_hit		hit;
	t_list		*node;
	t_object	*obj;
	float		t;

	node = scene.objects;
	hit.t = -1.0;
	hit.obj = NULL;
	while (node)
	{
		obj = node->content;
		t = intersect_object(ray, obj);
		if (t > 0 && (hit.t < 0 || t < hit.t))
		{
			hit.t = t;
			hit.obj = obj;
		}
		node = node->next;
	}
	return (hit);
}

void	render_pixel(mlx_image_t *img, t_scene scene, t_viewport vp, t_point p)
{
	t_ray		ray;
	t_hit		hit;
	uint32_t	color;
	t_color		lighted_color;

	ray = generate_ray(scene.camera, vp, p.x, p.y);
	hit = trace_ray(ray, scene);
	if (hit.t > 0)
	{
		lighted_color = apply_ambient(hit.obj->color, scene.ambient);
		color = color_to_int(lighted_color);
	}
	else
		color = 0x000000FF;
	mlx_put_pixel(img, p.x, p.y, color);
}

void	render_scene(mlx_image_t *img, t_scene scene)
{
	t_viewport	vp;
	t_point		p;

	p.y = 0;
	vp = init_viewport(scene.camera);
	while (p.y < HEIGHT)
	{
		p.x = 0;
		while (p.x < WIDTH)
		{
			render_pixel(img, scene, vp, p);
			p.x++;
		}
		p.y++;
	}
}
