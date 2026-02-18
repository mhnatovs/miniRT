/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:53:21 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/18 17:38:11 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

// virtual camera viewport parameters: FOV scale, aspect ratio,
// and orientation vectors (forward/right/up) for ray construction
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
	t_vector	point;
	t_vector	normal;
}				t_hit;

// coef: coefficients of the quadratic equation (a, b, c)
// for the intersection of the ray with the side surface
// of the cylinder
typedef struct s_cyl_tmp
{
	t_vector	oc;
	t_vector	proj_oc;
	t_vector	proj_dir;
	float		coef[3];
}				t_cyl_tmp;

t_ray		make_ray(t_vector source, t_vector direction);
t_ray		generate_ray(t_camera cam, t_viewport v, int x, int y);
t_hit		trace_ray(t_ray ray, t_scene scene);
t_viewport	init_viewport(t_camera cam);
void		render_pixel(mlx_image_t *img,
				t_scene scene, t_viewport vp, t_point p);
void		render_scene(mlx_image_t *img, t_scene scene);
uint32_t	color_to_int(t_color color);
t_color		apply_ambient(t_color obj_color, t_ambient ambient);
t_color		apply_diffuse(t_hit hit, t_light light);
int			in_shadow(t_hit hit, t_scene scene);
t_color		calc_color(t_hit hit, t_scene scene);

#endif