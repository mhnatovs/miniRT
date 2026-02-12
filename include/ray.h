/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:10:07 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/12 21:06:08 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct s_viewport
{
	float		fov_scale;
	float		aspect_ratio;
	t_vector	forward;
	t_vector	right;
	t_vector	up;
}				t_viewport;

t_ray		make_ray(t_vector origin, t_vector direction);
t_ray		generate_ray(t_camera cam, t_viewport v, int x, int y);
t_viewport	init_viewport(t_camera cam);

#endif