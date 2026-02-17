/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 19:07:50 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/17 14:56:52 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_viewport	init_viewport(t_camera cam)
{
	t_viewport	vp;
	t_vector	world_up;
	t_vector	forward;

	vp.aspect_ratio = (float)WIDTH / (float)HEIGHT;
	vp.fov_scale = tan(cam.fov * 0.5 * M_PI / 180.0);
	forward = vector_normalize(cam.dir);
	vp.forward = forward;
	if (fabs(forward.y) > 0.999)
		world_up = (t_vector){0, 0, 1};
	else
		world_up = (t_vector){0, 1, 0};
	vp.right = vector_normalize(vector_cross(forward, world_up));
	vp.up = vector_normalize(vector_cross(vp.right, forward));
	return (vp);
}
