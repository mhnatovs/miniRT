/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 19:07:50 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/12 19:09:25 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_viewport	init_viewport(t_camera cam)
{
	t_viewport	vp;
	t_vector	world_up;

	vp.aspect_ratio = (float)WIDTH / (float)HEIGHT;
	vp.fov_scale = tan(cam.fov * 0.5 * M_PI / 180.0);
	vp.forward = vector_normalize(cam.dir);
	world_up = (t_vector){0, 1, 0};
	vp.right = vector_normalize(vector_cross(vp.forward, world_up));
	vp.up = vector_normalize(vector_cross(vp.right, vp.forward));
	return (vp);
}
