/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 19:07:50 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/04/13 16:19:32 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// aspect_ratio - so that the image isn't stretched
t_viewport	init_viewport(t_camera cam)
{
	t_viewport	vp;
	t_vector	world_up;
	t_vector	forward;
	t_vector	up;
	t_vector	right;

	vp.aspect_ratio = (float)WIDTH / (float)HEIGHT;
	vp.height = HEIGHT;
	vp.width = WIDTH;
	vp.fov_scale = tan(cam.fov * 0.5 * M_PI / 180.0);
	forward = vector_normalize(cam.dir);
	vp.forward = forward;
	world_up = (t_vector){0, 1, 0};
	if (fabs(forward.y) > 0.999f)
		world_up = (t_vector){1, 0, 0};
	right = vector_normalize(vector_cross(forward, world_up));
	up = vector_cross(right, forward);
	vp.forward = forward;
	vp.right = right;
	vp.up = up;
	return (vp);
}
