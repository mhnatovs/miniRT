/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 17:34:21 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/20 17:57:00 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static void	yaw_rotation(float angle, t_context *cont)
// {
// 	float		cos_a;
// 	float		sin_a;
// 	t_vector	new_dir;

// 	cos_a = cos(angle);
// 	sin_a = sin(angle);
// 	new_dir.x = cont->scene.camera.dir.x * cos_a
// 		+ cont->scene.camera.dir.z * sin_a;
// 	new_dir.y = cont->scene.camera.dir.y;
// 	new_dir.z = -cont->scene.camera.dir.x * sin_a
// 		+ cont->scene.camera.dir.z * cos_a;
// 	cont->scene.camera.dir = vector_normalize(new_dir);
// 	re_render(cont);
// }

// void	rotate_camera(t_context *cont, mlx_key_data_t key)
// {
// 	float		angle;

// 	if (cont->selected_obj)
// 		return ;
// 	angle = 0.05;
// 	if (key.key == MLX_KEY_Z && (key.action == MLX_PRESS
// 			|| key.action == MLX_REPEAT))
// 		yaw_rotation(angle, cont);
// 	else if (key.key == MLX_KEY_X && (key.action == MLX_PRESS
// 			|| key.action == MLX_REPEAT))
// 		yaw_rotation(-angle, cont);
// }

void	rotate_camera(t_context *cont, mlx_key_data_t key)
{
	float		angle;
	t_vector	new_dir;
	float		cos_a;
	float		sin_a;

	if (cont->selected_obj)
		return ;
	angle = 0.5;
	if (key.key == MLX_KEY_Z && (key.action == MLX_PRESS
			|| key.action == MLX_REPEAT))
	{
		cos_a = cos(angle);
		sin_a = sin(angle);
		new_dir.x = cont->scene.camera.dir.x * cos_a
			+ cont->scene.camera.dir.z * sin_a;
		new_dir.y = cont->scene.camera.dir.y;
		new_dir.z = -cont->scene.camera.dir.x * sin_a
			+ cont->scene.camera.dir.z * cos_a;
		cont->scene.camera.dir = vector_normalize(new_dir);
		re_render(cont);
	}
	else if (key.key == MLX_KEY_X && (key.action == MLX_PRESS
			|| key.action == MLX_REPEAT))
	{
		angle = -angle;
		cos_a = cos(angle);
		sin_a = sin(angle);
		new_dir.x = cont->scene.camera.dir.x * cos_a
			+ cont->scene.camera.dir.z * sin_a;
		new_dir.y = cont->scene.camera.dir.y;
		new_dir.z = -cont->scene.camera.dir.x * sin_a
			+ cont->scene.camera.dir.z * cos_a;
		cont->scene.camera.dir = vector_normalize(new_dir);
		re_render(cont);
	}
}