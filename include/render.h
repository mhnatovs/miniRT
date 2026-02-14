/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:53:21 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/14 18:32:46 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

typedef struct s_viewport
{
	float		fov_scale;
	float		aspect_ratio;
	t_vector	forward;
	t_vector	right;
	t_vector	up;
}				t_viewport;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_hit
{
	float		t;
	t_object	*obj;
}				t_hit;

t_ray		make_ray(t_vector origin, t_vector direction);
t_ray		generate_ray(t_camera cam, t_viewport v, int x, int y);
t_hit		trace_ray(t_ray ray, t_scene scene);
t_viewport	init_viewport(t_camera cam);
void		render_pixel(mlx_image_t *img,
				t_scene scene, t_viewport vp, t_point p);
void		render_scene(mlx_image_t *img, t_scene scene);
uint32_t	color_to_int(t_color color);
t_color		apply_ambient(t_color obj_color, t_ambient ambient);

#endif